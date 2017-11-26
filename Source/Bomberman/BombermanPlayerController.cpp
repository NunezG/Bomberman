// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "BombermanPlayerController.h"
#include "AI/Navigation/NavigationSystem.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "BombermanCharacter.h"

ABombermanPlayerController::ABombermanPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ABombermanPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}

void ABombermanPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	//Bind keyboard mappings based on playerID
	int32 pID =	GetLocalPlayer()->GetControllerId();

	//Using a FString -> FName conversion
	FString tempName = "MoveForward" + FString::FromInt(pID);
	InputComponent->BindAxis(FName(*tempName), this, &ABombermanPlayerController::MoveForward);

	tempName = "MoveRight" + FString::FromInt(pID);
	InputComponent->BindAxis(FName(*tempName), this, &ABombermanPlayerController::MoveRight);

	tempName = "Use" + FString::FromInt(pID);
	InputComponent->BindAction(FName(*tempName), EInputEvent::IE_Pressed, this, &ABombermanPlayerController::Use);
}

void ABombermanPlayerController::MoveForward(float axisValue)
{
}

void ABombermanPlayerController::MoveRight(float axisValue)
{
}

void ABombermanPlayerController::Use()
{
}
