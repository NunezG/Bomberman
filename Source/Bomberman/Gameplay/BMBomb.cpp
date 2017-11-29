// Fill out your copyright notice in the Description page of Project Settings.

#include "BMBomb.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ABMBomb::ABMBomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Setup mesh component
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BombMesh"));
	mesh->SetupAttachment(RootComponent);
}

void ABMBomb::OnInit(int32 gridSize)
{
	//Set tile size as obtained from player character
	tileSize = gridSize;

	//Call the on fuse lit event so that the blueprint part of the actor can be handled
	OnFuseLit();
}

// Called when the game starts or when spawned
void ABMBomb::BeginPlay()
{
	Super::BeginPlay();
	
	UWorld* world = GetWorld();
	//Start the timer
	world->GetTimerManager().SetTimer(fuseTimerHandle, this, &ABMBomb::OnExplode, fuseTime, false);
}

// Called every frame
void ABMBomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

