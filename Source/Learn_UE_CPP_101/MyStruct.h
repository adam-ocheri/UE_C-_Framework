// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
// Create empty class
//Nuke the cpp file
//change decleration from class to struct - remove API call - and prefix name with an F, denoting this as a struct
//Add USTRUCT(BPTYPE) and GENERATED_BODY()

#include "MyStruct.generated.h"

USTRUCT(BlueprintType)
struct FMyStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	float X = 0.0f;

	UPROPERTY(BlueprintReadWrite)
	float Y = 0.0f;

	UPROPERTY(BlueprintReadWrite)
	float Z = 0.0f;

	UPROPERTY(BlueprintReadWrite)
	FVector Coordinates {X, Y, Z};
};
