// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BMStageCameraActor.generated.h"

UCLASS()
class BOMBERMAN_API ABMStageCameraActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABMStageCameraActor();

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* StageCamera;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Debug mesh **/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* mesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;	
};
