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

	UWorld* world = GetWorld();
	//Light the fuses
	world->GetTimerManager().SetTimer(fuseTimerHandle, this, &ABMBomb::OnExplode, fuseTime, false);

	//Call the on fuse lit event so that the blueprint part of the actor can be handled
	OnFuseLit();
}

// Called when the game starts or when spawned
void ABMBomb::BeginPlay()
{
	Super::BeginPlay();
}

AActor* ABMBomb::CalculateBlastHit(FVector direction, FVector & target)
{
	//Calculate hit raytrace
	FHitResult hit;

	//Starting point for the raycast
	FVector startLocation = GetActorLocation();

	//To get the final point of the raycast, we have to multiply the direction of the ray to the travel distance (tileSize), and add it to the start location
	FVector endLocation = startLocation + (direction * blastRange * tileSize);

	//Setup collision parameters to ignore pawn which is casting the ray
	FCollisionQueryParams collisionParameters;
	//collisionParameters.AddIgnoredActor(this);

	//Actual line trace
	GetWorld()->LineTraceSingleByChannel(hit, startLocation, endLocation, ECollisionChannel::ECC_MAX, collisionParameters);

	//Get the location either from the ray trace or if nothing is hit, then use the max raytrace range
	if(hit.GetActor() == NULL)
	{
		target = startLocation + (direction * blastRange * tileSize);
	}
	else
	{
		target = hit.GetActor()->GetActorLocation();
	}	
	return hit.GetActor();
}

// Called every frame
void ABMBomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

