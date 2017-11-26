// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BombermanGameMode.generated.h"

// Only way to make columns for tiles is using a struct to store an additional array
USTRUCT()
struct FTileColumns
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY()
		TArray<int32> rows;

	FTileColumns()
	{
		for(int i = 0; i < 10; i++)
		{
			rows.Add(FMath::RandRange(0, 2));
		}
	}
};

UCLASS(minimalapi)
class ABombermanGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABombermanGameMode();

	virtual void BeginPlay() override;

	/** Blocks **/
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Block)
	TSubclassOf<class ABMBlock> wall;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Block)
	TSubclassOf<class ABMBlock> destructibleBlock; 

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Block)
	TSubclassOf<class ABMBlock> playerSpawnBlock; 

	/** Tiling variables **/
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Tiling)
	FVector tilingStartPoint;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Tiling)
	int32 tileSize;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Tiling)
	FVector mapCenter;

protected:
	//Function to read tile data from file
	void ReadTileDataFromFile(int32 levelNumber);

	//Function to spawn blocks in their correct location
	UFUNCTION(BlueprintCallable, Category = Tiling)
	void SpawnBlocks();

private:
	//2D array for tiles
	TArray<FTileColumns> columns;
};



