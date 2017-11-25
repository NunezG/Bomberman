// Fill out your copyright notice in the Description page of Project Settings.

#include "BMStageCameraActor.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ABMStageCameraActor::ABMStageCameraActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Setup static mesh component
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DebugMesh"));
	mesh->SetupAttachment(RootComponent);

	//Setup camera boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(mesh);
	CameraBoom->bAbsoluteRotation = false;
	CameraBoom->TargetArmLength = 1530.f;
	CameraBoom->RelativeRotation = FRotator(0.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; 

	//Setup camera component
	StageCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("StageCamera"));
	StageCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	StageCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

// Called when the game starts or when spawned
void ABMStageCameraActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABMStageCameraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

