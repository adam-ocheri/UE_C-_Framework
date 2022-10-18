// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MyPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class LEARN_UE_CPP_101_API AMyPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	int32 Kills;
	int32 Deaths;

	virtual void BeginPlay();

	
	
};
