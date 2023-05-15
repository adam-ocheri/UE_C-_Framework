// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/NoExportTypes.h"
#include "MyObject.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class LEARN_UE_CPP_101_API UMyObject : public UObject
{
	GENERATED_BODY()

	//In order for the class attributes to be exposed to other classes that need to view or edit the CDO, the attributes must be public
public:

	UPROPERTY(EditAnywhere)
	float MyForce = 5.0f;

	UPROPERTY(EditAnywhere)
	TArray<int> WeaponClipSizes;

	UFUNCTION(BlueprintCallable)
	float Multiply(float X, float Y);
};
