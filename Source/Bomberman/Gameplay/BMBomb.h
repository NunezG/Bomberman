// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "GameFramework/Actor.h"
#include "BMBomb.generated.h"

UCLASS()
class BOMBERMAN_API ABMBomb : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABMBomb();

	//Functions which are to be used instead of the BeginPlay to call all initializations so that its under our control
	UFUNCTION(BlueprintCallable, Category = Bomb)
	void OnInit(int32 gridSize);
	UFUNCTION(BlueprintImplementableEvent, Category = Bomb)
	void OnFuseLit();

	/** Static mesh component **/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Bomb)
	class UStaticMeshComponent* mesh;

	/** Particle system template for explosion **/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Bomb)
	UParticleSystem* explosion;

	/** TileSize **/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Bomb)
	int32 tileSize;

	/** Blast range in all 4 directions **/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Bomb)
	int32 blastRange = 3;

	/** Fuse timer for the bomb **/
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Bomb)
	float fuseTime = 5.0f;

	UFUNCTION(BlueprintImplementableEvent, Category = Bomb)
	void OnExplode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Timer handle for fuse
	FTimerHandle fuseTimerHandle;

	//Function to take the direction of the bomb, and then calculate the hits/distance of bomb blast radius for visual feedback
	UFUNCTION(BlueprintCallable, Category = Bomb)
	AActor* CalculateBlastHit(FVector direction, FVector &target);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
