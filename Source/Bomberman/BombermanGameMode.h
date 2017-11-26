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
		//Empty the rows array as soon as it is made
		rows.Empty();
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

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Tiling)
	FVector mapCenter;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Tiling)
	int32 levelWidth;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Tiling)
	int32 levelHeight;

protected:
	//Function to read tile data from file
	UFUNCTION(BlueprintCallable, Category = Tiling)
	void ReadTileDataFromFile(int32 levelNumber);

	//Function to spawn blocks in their correct location
	UFUNCTION(BlueprintCallable, Category = Tiling)
	void SpawnBlocks();

private:
	//2D array for tiles
	TArray<FTileColumns> columns;
};



