// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "MyEngineSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class LEARN_UE_CPP_101_API UMyEngineSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()

	// Initializes the subsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	// Shuts down the subsystem
	virtual void Deinitialize() override;
};
