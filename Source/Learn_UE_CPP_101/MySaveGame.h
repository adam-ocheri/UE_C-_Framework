// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"

/**
 * 
 */
UCLASS()
class LEARN_UE_CPP_101_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UMySaveGame();

	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	bool bAbility;
		
	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	float Threshold;

		
	
};
