// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Engine.h"
#include "GameFramework/PlayerController.h"
#include "BombermanPlayerController.generated.h"

UCLASS()
class ABombermanPlayerController: public APlayerController
{
	GENERATED_BODY()

public:
	ABombermanPlayerController();

protected:
	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	//Movement function
	void MoveForward(float axisValue);
	void MoveRight(float axisValue);

	//Action button function
	void Use();

private:
	int32 tileSize;

	class ABombermanCharacter *pawn;

	//Function to process raycast
	bool ProcessRaycast(FHitResult &outHit, FVector rayDirection);

	bool bIsMovingForward, bIsMovingRight;
};