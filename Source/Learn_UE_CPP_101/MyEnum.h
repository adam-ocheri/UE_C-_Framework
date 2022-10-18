// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
// Starting out with an empty class

// MUST delete the cpp file

//then include the .generated header
#include "MyEnum.generated.h"

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	1. Enum Class

UENUM(BlueprintType)				// Very important macro - We use UENUM classes in the engine ( With the specifier 'BlueprintType' to have this UENUM available across the entire project )
enum class EWillState : uint8		// enum class is a special UE syntax - and it must inherit from 'uint8'
{
	Relax_State		UMETA(DisplayName = "Relaxed"),			// The UMETA tags allow us to define a DisplayName that would be used in Blueprints
	Focus_State		UMETA(DisplayName = "Focused"),
	Alarm_State		UMETA(DisplayName = "Alarmed")
};

// once the members are added to the enumartors list, we need to close the engine and build for Development Editor

/*

 next, we will need to include this header file where we would want to use it, and create an object out of it :
		EWillState WillState;

 we may instead choose to initialize the enum with some default value:
		EWillState WillState = EWillState::Relax_State;

 and to make this fully accessible for blueprints, we simply declare it as a UProperty:
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EWillState WillState = EWillState::Alarm_State;
*/


// Can create multiple enumarations within 1 header file!!!
UENUM(BlueprintType)
enum class EAgressionMode : uint8
{
	Mild		UMETA(DisplayName = "Mild Agression"),
	Furious		UMETA(DisplayName = "Furious Agression"),
	FullBerserk	UMETA(DisplayName = "Fully Berserk Agression")

};

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------








//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	2.Bitmask Class Enums (BitFlags)

UENUM(BlueprintType, Meta = (Bitflag))
enum class EAnimationThreads : uint8
{
	None = 0 UMETA(Hidden),
	Idle = 1 UMETA(DisplayName = "Idle"),
	Walk = 2 UMETA(DisplayName = "Walking"),
	Run = 4 UMETA(DisplayName = "Running"),
	Crouch = 8 UMETA(DisplayName = "Croching"),
	Punch = 16 UMETA(DisplayName = "Punching"),
	Shoot = 32 UMETA(DisplayName = "Shooting"),
	Fall = 64 UMETA(DisplayName = "Fall")

};


//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------




//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	3.Standard Enums

UENUM(BlueprintType)
enum EAnimThreads
{
	EAT_Idle	UMETA(DisplayName = "Idle"),
	EAT_Walk	UMETA(DisplayName = "Walk")
};

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	4. Namespace Enums

UENUM(BlueprintType)
namespace EWeaponState
{
	enum FireState
	{
		Single,
		Semi,
		Auto
	};
	
}