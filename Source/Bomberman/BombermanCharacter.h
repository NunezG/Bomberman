// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BombermanCharacter.generated.h"

UCLASS(Blueprintable)
class ABombermanCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABombermanCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Tiling)
	int32 tileSize;

	UFUNCTION(BlueprintImplementableEvent, Category = Movement)
	void PlayerInputForward(float axisValue, int32 gridSize);

	UFUNCTION(BlueprintImplementableEvent, Category = Movement)
	void PlayerInputRight(float axisValue, int32 gridSize);

	//Function to be sent to blueprints if bomb is dropped (use button is pressed)
	UFUNCTION(BlueprintImplementableEvent, Category = Bomb)
	void BombDropped();

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	
};

