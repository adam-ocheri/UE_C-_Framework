// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
// Create empty class
// //And don't forget to include the generated header
//Nuke the cpp file
//change decleration from class to struct - remove API call - and prefix name with an F, denoting this as a struct
//Add USTRUCT(BPTYPE) and GENERATED_BODY()

#include "NumStruct.generated.h"

USTRUCT(BlueprintType)
struct FNumStruct
{
	GENERATED_BODY()

	FORCEINLINE FNumStruct();
	explicit FORCEINLINE FNumStruct(const float InX);
	explicit FORCEINLINE FNumStruct(const float InX, const float InY);
	explicit FORCEINLINE FNumStruct(const float InX, const float InY, const float InZ);
	explicit FORCEINLINE FNumStruct(const FVector InCoordinates);

	bool operator==(const FNumStruct& QueriedObject) const;
	bool operator!=(const FNumStruct& QueriedObject) const;

	void IncreaseAll(float Amount);

	UPROPERTY(BlueprintReadWrite)
		float X;

	UPROPERTY(BlueprintReadWrite)
		float Y;

	UPROPERTY(BlueprintReadWrite)
		float Z = 0.0f;

	UPROPERTY(BlueprintReadWrite)
		FVector Coordinates {
		X, Y, Z
	};

	
};

FORCEINLINE FNumStruct::FNumStruct()
	:X(0.0f), Y(0.0) {}

FORCEINLINE FNumStruct::FNumStruct(const float InX)
	: X(InX) {}

FORCEINLINE FNumStruct::FNumStruct(const float InX, const float InY)
	: X(InX), Y(InY) {}

FORCEINLINE FNumStruct::FNumStruct(const float InX, const float InY, const float InZ)
	: X(InX), Y(InY), Z(InZ)
{}

FORCEINLINE FNumStruct::FNumStruct(const FVector InCoordinates)
	: Coordinates(InCoordinates)
{}

FORCEINLINE bool FNumStruct::operator==(const FNumStruct& QueriedObject) const
{
	return X == QueriedObject.X && Y == QueriedObject.Y && Z == QueriedObject.Z;
}

FORCEINLINE bool FNumStruct::operator!=(const FNumStruct& QueriedObject) const
{
	return X != QueriedObject.X || Y != QueriedObject.Y || Z != QueriedObject.Z;
}

FORCEINLINE void FNumStruct::IncreaseAll(float Amount)
{
	X *= Amount;
	Y *= Amount;
	Z *= Amount;
	Coordinates = FVector(X, Y, Z);
}



/*

USTRUCT(BlueprintType)
struct FNumStruct
{
	GENERATED_BODY()

	FORCEINLINE FNumStruct();
	explicit FORCEINLINE FNumStruct(const float InX);
	explicit FORCEINLINE FNumStruct(const float InX, const float InY);
	explicit FORCEINLINE FNumStruct(const float InX, const float InY, const float InZ);
	explicit FORCEINLINE FNumStruct(const FVector InCoordinates);

	UPROPERTY(BlueprintReadWrite)
	float X = 0.0f;

	UPROPERTY(BlueprintReadWrite)
	float Y = 0.0f;

	UPROPERTY(BlueprintReadWrite)
	float Z = 0.0f;

	UPROPERTY(BlueprintReadWrite)
	FVector Coordinates {X, Y, Z};

	bool operator==(const FNumStruct& QueriedObject) const;
	bool operator!=(const FNumStruct& QueriedObject) const;

	void IncreaseAll(float Amount);
};

FORCEINLINE FNumStruct::FNumStruct()
{}

FORCEINLINE FNumStruct::FNumStruct(const float InX)
	: X(InX)
{}

FORCEINLINE FNumStruct::FNumStruct(const float InX, const float InY)
	: X(InX), Y(InY)
{}

FORCEINLINE FNumStruct::FNumStruct(const float InX, const float InY, const float InZ)
	: X(InX), Y(InY), Z(InZ)
{}

FORCEINLINE FNumStruct::FNumStruct(const FVector InCoordinates)
	: Coordinates(InCoordinates)
{}

FORCEINLINE bool FNumStruct::operator==(const FNumStruct& QueriedObject) const
{
	return X == QueriedObject.X && Y == QueriedObject.Y && Z == QueriedObject.Z;
}

FORCEINLINE bool FNumStruct::operator!=(const FNumStruct& QueriedObject) const
{
	return X != QueriedObject.X || Y != QueriedObject.Y || Z != QueriedObject.Z;
}

FORCEINLINE void FNumStruct::IncreaseAll(float Amount)
{
	X *= Amount;
	Y *= Amount;
	Z *= Amount;
	Coordinates = FVector(X, Y, Z);
}

*/