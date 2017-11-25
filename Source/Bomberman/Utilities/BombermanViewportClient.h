// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Engine/GameViewportClient.h"
#include "BombermanViewportClient.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_API UBombermanViewportClient : public UGameViewportClient
{
	GENERATED_BODY()

	//Overriding the InputKey method so that keyboard events propogate to all player controllers
	virtual bool InputKey(FViewport* Viewport, int32 ControllerId, FKey Key, EInputEvent EventType, float AmountDepressed = 1.f, bool bGamepad = false) override;
};
