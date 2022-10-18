// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "MyLevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class LEARN_UE_CPP_101_API AMyLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()

	AMyLevelScriptActor(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay();

	virtual void Tick(float DeltaSeconds);

protected:
	UFUNCTION(BlueprintCallable)
	AActor* DoSomethingToSomeActor(AActor* SomeActor);
	
public:
	class TSubclassOf <AWorldSettings> MyWorldSettings;
	
};
