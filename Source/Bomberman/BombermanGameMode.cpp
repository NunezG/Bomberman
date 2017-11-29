// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "BombermanGameMode.h"
#include "BombermanPlayerController.h"
#include "BombermanCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Gameplay/BMBlock.h"

ABombermanGameMode::ABombermanGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ABombermanPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ABombermanGameMode::BeginPlay()
{
	//Call parents begin play so that all events are propogated
	Super::BeginPlay();
}

void ABombermanGameMode::ReadTileDataFromFile(int32 levelNumber)
{
	//We are going to use the plugins folder for this because all contents of it are packaged in every build by default
	//Get path to plugins folder and combine it with the int we get to make a level text file
	FString levelName = FString::FromInt(levelNumber) + ".txt";
	FString filePath = FPaths::ProjectContentDir() + "Maps/LevelData/" + levelName;

	TArray<FString> fileData;
	//Only go forward with this if level files exist, log result
	if(FPaths::FileExists(filePath))
	{
		FFileHelper::LoadFileToStringArray(fileData, *filePath);
	}
	else
	{
		UE_LOG(LogLoad, Error, TEXT("File in LevelData not found"));
		return;
	}

	//Assign camera height to be used for the aspect ratio later
	levelHeight = fileData.Num() + 1;

	//Empty columns array, and start assigning values
	columns.Empty();

	//Add number of columns as per fileData height
	columns.AddDefaulted(fileData.Num());

	//Add correct number of row elements to each column by getting it from the text string
	for(int i = 0; i < columns.Num(); i++)
	{
		TArray<FString> blockNumbers;
		//Split string using a comma as a divider to get int in string form
		fileData[i].ParseIntoArrayWS(blockNumbers);

		//Assign level width. Check with previous value, if it is more
		if(blockNumbers.Num() + 1 > levelWidth)
		{
			levelWidth = blockNumbers.Num() + 1;
		}

		//Initialize the rows array inside current column with the correct number of elements
		columns[i].rows.AddDefaulted(blockNumbers.Num());

		//In the second loop, we will convert all values from the string to a number, and assign it to each row
		for(int j = 0; j < columns[i].rows.Num(); j++)
		{
			columns[i].rows[j] = FCString::Atoi(*blockNumbers[j]);
		}
	}
}

void ABombermanGameMode::SpawnBlocks()
{
	//Take tile data and start spawning blocks
	//NOTE: We are going into negative in Y, but positive in X, to maintain the left to right reading order of tiles
	for(int i = 0; i < columns.Num(); i++)
	{
		for(int j = 0; j < columns[i].rows.Num(); j++)
		{
			//Calculate spawn point in X and Y using the starting point
			//Going lower in x by each a factor of the tile size to go top to bottom
			float x = tilingStartPoint.X - (i * tileSize);

			//For y, we are going to add to go left to right similarly
			float y = tilingStartPoint.Y + (j * tileSize);
			
			UWorld *world = AActor::GetWorld();
			//Use vector using the x and y calculated earlier as location and spawn blocks
			if(columns[i].rows[j] == 1) //Wall
			{				
				world->SpawnActor<ABMBlock>(wall, FVector(x, y, tilingStartPoint.Z), FRotator(0, 0, 0));
				continue;
			}
			else if(columns[i].rows[j] == 2) //Destructible
			{
				world->SpawnActor<ABMBlock>(destructibleBlock, FVector(x, y, tilingStartPoint.Z), FRotator(0, 0, 0));
				continue;
			}
			else if(columns[i].rows[j] == 3) //PlayerSpawn
			{
				world->SpawnActor<ABMBlock>(playerSpawnBlock, FVector(x, y, tilingStartPoint.Z), FRotator(0, 0, 0));
				continue;
			}
			else if(columns[i].rows[j] == 4) //Centrepoint
			{
				//Set this location to be a map center, and spawn a normal wall
				mapCenter = FVector(x, y, 0);
				world->SpawnActor<ABMBlock>(wall, FVector(x, y, tilingStartPoint.Z), FRotator(0, 0, 0));
				continue;
			}			
		}
	}
}
