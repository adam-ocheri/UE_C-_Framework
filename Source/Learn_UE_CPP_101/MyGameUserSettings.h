// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "MyGameUserSettings.generated.h"

/**
 * 
 */
UCLASS()
class LEARN_UE_CPP_101_API UMyGameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()

public:
	void SetScreenResolution(FIntPoint Resolution);
	
};
