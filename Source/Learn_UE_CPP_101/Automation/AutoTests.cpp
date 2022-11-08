// Fill out your copyright notice in the Description page of Project Settings.


#include "../Automation/AutoTests.h"

//Includes needed for unit tests
#include "Misc/AutomationTest.h"
#include "Tests/AutomationEditorCommon.h"

//
#include "../Learn_UE_CPP_101Character.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSpawnPlayerTest, "RegimeChange_API.Player.Status.Player Spawns Succesfully On Init", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::CriticalPriority);

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FPlayerHealthTest, "RegimeChange_API.Player.Status.Player Can Take Damage",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::CriticalPriority);

bool FSpawnPlayerTest::RunTest(const FString& Parameters)
{
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();

	ALearn_UE_CPP_101Character* MyCharacter = World->SpawnActor<ALearn_UE_CPP_101Character>();
	if (MyCharacter)
	{
		bool bHealthOK = TestEqual(FString("Initial Health is Maxed"), MyCharacter->Health, 100.0f);
		if (bHealthOK)
		{
			AddInfo(FString("Health is maxed to 100 when the player spawns"));
		}
		else
		{
			AddError(FString(" !ERROR! : For some reason, the player's initial Health is not maxed!"));
		}
		
		MyCharacter->Destroy();
		return true;
	}
	else
	{
		return false;
	}

}

bool FPlayerHealthTest::RunTest(const FString& Parameters)
{
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();

	ALearn_UE_CPP_101Character* MyCharacter = World->SpawnActor<ALearn_UE_CPP_101Character>();

	if (MyCharacter)
	{
		MyCharacter->Health -= 15.0f;

		if (MyCharacter->Health == 85.0f)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
	
}


