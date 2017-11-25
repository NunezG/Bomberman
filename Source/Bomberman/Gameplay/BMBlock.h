// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BMBlock.generated.h"

//Enum to hold values of block type
UENUM(BlueprintType)
enum class EBlockType: uint8
{
	BT_WALL=1				UMETA(DisplayName="Wall"),
	BT_DESTRUCTIBLE=2		UMETA(DisplayName="Destructible Block"),
	BT_SPAWN=3				UMETA(DisplayName="PlayerSpawn")
};

UCLASS()
class BOMBERMAN_API ABMBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABMBlock();

	// Type of block
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Block Properties")
	EBlockType type;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Static mesh component **/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Block Properties", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* mesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
