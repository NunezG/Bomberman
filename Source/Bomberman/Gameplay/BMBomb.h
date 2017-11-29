// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BMBomb.generated.h"

UCLASS()
class BOMBERMAN_API ABMBomb : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABMBomb();

	/** Static mesh component **/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Bomb)
	class UStaticMeshComponent* mesh;

	//Fuse timer for the bomb
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Bomb)
	float fuseTime = 5.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Timer handle for fuse
	FTimerHandle fuseTimerHandle;

	UFUNCTION(BlueprintImplementableEvent, Category = Bomb)
	void OnExplode();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
