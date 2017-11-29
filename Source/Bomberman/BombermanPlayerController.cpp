// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "BombermanPlayerController.h"
#include "AI/Navigation/NavigationSystem.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "Gameplay/BMBlock.h"
#include "BombermanGameMode.h"
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

	//Get reference to the pawn being controlled by this player controller
	pawn = Cast<ABombermanCharacter>(GetPawn());

	//Get tile size number from the game mode
	ABombermanGameMode* const gameMode = GetWorld()->GetAuthGameMode<ABombermanGameMode>();
	tileSize = gameMode->tileSize;
}

void ABombermanPlayerController::MoveForward(float axisValue)
{
	//If stationary, return out safely
	if(axisValue == 0)
	{
		bIsMovingForward = false;
		return;
	}

	//Return if another direction is pressed
	if(bIsMovingRight)
	{
		bIsMovingForward = false;
		return;
	}
	else
	{
		bIsMovingForward = true;
	}

	//Before we decide to move, we need to check if there are any adjacent blocks which the player cannot move through
	//We are going to use a raycast for that, and will pass on the data to the player pawn after calculation

	//Check if pawn exists. If not, we can get it again
	if(pawn == NULL)
	{
		pawn = Cast<ABombermanCharacter>(GetPawn());
	}

	//Hit contains information about what the raycast hit.
	FHitResult hit;

	//Process hit in the correct direction, for forward or back, we are going to use the global Forward vector, and multiply it by the axis value for back
	FVector dir = FVector::ForwardVector * axisValue;

	//If a button is pressed, send the axis value and the current tile size to the pawn
	//Process the final hit raycast and check if a signal has to be passed on to the pawn
	if(ProcessRaycast(hit, dir) == false)
	{
		//Call the input function in the pawn so that we can pass this to the character blueprint
		pawn->PlayerInputForward(axisValue, tileSize);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(1, 0.3, FColor::Red, "Hit a WALL!");
		GEngine->AddOnScreenDebugMessage(1, 0.3, FColor::Purple, hit.GetActor()->GetName());
	}

	
}

void ABombermanPlayerController::MoveRight(float axisValue)
{
	//If stationary, return out safely
	if(axisValue == 0)
	{
		bIsMovingRight = false;
		return;
	}

	//Return if another direction is pressed
	if(bIsMovingForward)
	{
		bIsMovingRight = false;
		return;
	}
	else
	{
		bIsMovingRight = true;
	}

	//Before we decide to move, we need to check if there are any adjacent blocks which the player cannot move through
	//We are going to use a raycast for that, and will pass on the data to the player pawn after calculation

	//Check if pawn exists. If not, we can get it again
	if(pawn == NULL)
	{
		pawn = Cast<ABombermanCharacter>(GetPawn());
	}

	//Hit contains information about what the raycast hit.
	FHitResult hit;

	//Process hit in the correct direction, for right and left, we are going to use the global Right vector, and multiply it by the axis value for left
	FVector dir = FVector::RightVector * axisValue;

	//If a button is pressed, send the axis value and the current tile size to the pawn
	//Process the final hit raycast and check if a signal has to be passed on to the pawn
	if(ProcessRaycast(hit, dir) == false)
	{
		//Call the input function in the pawn so that we can pass this to the character blueprint
		pawn->PlayerInputRight(axisValue, tileSize);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(1, 0.3, FColor::Red, "Hit a WALL!");
		GEngine->AddOnScreenDebugMessage(1, 0.3, FColor::Purple, hit.GetActor()->GetName());
	}
}

void ABombermanPlayerController::Use()
{
	//When Use is called, we have to send a signal that bombs can be dropped to the controlled pawn
	if(pawn != NULL)
	{
		
	}
}

bool ABombermanPlayerController::ProcessRaycast(FHitResult & outHit, FVector rayDirection)
{
	//The length of the ray in units.
	float rayLength = tileSize;

	//Starting point for the raycast
	FVector startLocation = pawn->GetActorLocation();

	//To get the final point of the raycast, we have to multiply the direction of the ray to the travel distance (tileSize), and add it to the start location
	FVector endLocation = startLocation + (rayDirection * rayLength);

	//Setup collision parameters to ignore pawn which is casting the ray
	FCollisionQueryParams collisionParameters;
	collisionParameters.AddIgnoredActor(pawn);

	//Actual line trace
	GetWorld()->LineTraceSingleByChannel(outHit, startLocation, endLocation, ECollisionChannel::ECC_Visibility, collisionParameters);

	//Check if hit returned a wall character
	ABMBlock *tempBlock = Cast<ABMBlock>(outHit.GetActor());
	if(tempBlock != NULL)
	{
		//Check if it is one of the blocking walls (1 or 2), or one of the other types
		if(tempBlock->type == EBlockType::BT_WALL ||tempBlock->type == EBlockType::BT_DESTRUCTIBLE)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	return false;
}
