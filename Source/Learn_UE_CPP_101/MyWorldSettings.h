// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/WorldSettings.h"
#include "MyWorldSettings.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, config = game, notplaceable)
class LEARN_UE_CPP_101_API AMyWorldSettings : public AWorldSettings
{
	GENERATED_BODY()

	AMyWorldSettings(const FObjectInitializer& ObjectInitializer);

	void BeginPlay();
};
