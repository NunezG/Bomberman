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
	//Populate columns and rows
	//We are adding defaulted here because it will change later anyway
	columns.AddDefaulted(5);

	//Read from file for the map data
	ReadTileDataFromFile(1);

	//Call parents begin play so that all events are propogated
	Super::BeginPlay();
}

void ABombermanGameMode::ReadTileDataFromFile(int32 levelNumber)
{
	//We are going to use the plugins folder for this because all contents of it are packaged in every build by default
	//Get path to plugins folder and combine it with the int we get to make a level text file
	FString levelName = FString::FromInt(levelNumber) + ".txt";
	FString filePath = FPaths::GameContentDir() + "Maps/LevelData/" + levelName;

	TArray<FString> fileData;
	//Only go forward with this if level files exist, log result
	if(FPaths::FileExists(filePath))
	{
		FFileHelper::LoadFileToStringArray(fileData, *filePath);
	}
	else
	{
		UE_LOG(LogLoad, Error, TEXT("File in LevelData not found"));
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

			//Use vector using the x and y calculated earlier as location and spawn blocks
			if(columns[i].rows[j] == 1) //Wall
			{				
				GetWorld()->SpawnActor<ABMBlock>(wall, FVector(x, y, tilingStartPoint.Z), FRotator());
				continue;
			}
			else if(columns[i].rows[j] == 2) //Destructible
			{
				GetWorld()->SpawnActor<ABMBlock>(destructibleBlock, FVector(x, y, tilingStartPoint.Z), FRotator());
				continue;
			}
			else if(columns[i].rows[j] == 3) //PlayerSpawn
			{
				GetWorld()->SpawnActor<ABMBlock>(playerSpawnBlock, FVector(x, y, tilingStartPoint.Z), FRotator());
				continue;
			}
			else if(columns[i].rows[j] == 4) //Centrepoint
			{
				//Set this location to be a map center, and spawn a normal wall
				mapCenter = FVector(x, y, 0);
				GetWorld()->SpawnActor<ABMBlock>(wall, FVector(x, y, tilingStartPoint.Z), FRotator());
				continue;
			}			
		}
	}
}
