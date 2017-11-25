// Fill out your copyright notice in the Description page of Project Settings.

#include "BMBlock.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ABMBlock::ABMBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Setup mesh component
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh"));
	mesh->SetupAttachment(RootComponent);
	mesh->RelativeScale3D = FVector(1.0f, 1.0f, 2.0f);
}

// Called when the game starts or when spawned
void ABMBlock::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABMBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

