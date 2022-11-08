// Fill out your copyright notice in the Description page of Project Settings.


#include "../Automation/MyCharacter_specTest.h"

#include "Misc/AutomationTest.h"
#include "Tests/AutomationEditorCommon.h"
#include "../Learn_UE_CPP_101Character.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------


BEGIN_DEFINE_SPEC(AutomationSpec, "System.Automation.Spec", EAutomationTestFlags::SmokeFilter | EAutomationTestFlags::ApplicationContextMask)
FString RunOrder;
END_DEFINE_SPEC(AutomationSpec)
void AutomationSpec::Define()
{
	Describe("A spec using BeforeEach and AfterEach", [this]()
		{
			BeforeEach([this]()
				{
					RunOrder = TEXT("A");
				});

			It("will run code before each spec in the Describe and after each spec in the Describe", [this]()
				{
					TestEqual("RunOrder", RunOrder, TEXT("A"));
				});

			AfterEach([this]()
				{
					RunOrder += TEXT("Z");
					TestEqual("RunOrder", RunOrder, TEXT("AZ"));
				});
		});
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------


BEGIN_DEFINE_SPEC(InitTest, "MySystem.MyTests.This Is The Test?", EAutomationTestFlags::SmokeFilter | EAutomationTestFlags::ApplicationContextMask)
	FString TestString;
END_DEFINE_SPEC(InitTest)

void InitTest::Define()
{
	xDescribe("Acceptance Test", [this]()
	{
		BeforeEach([this]()
		{
			TestString = FString("Hello");
		});

		It("Should Pass", [this]()
		{
			TestEqual("Actual Test: ", TestString, TEXT("Hello"));
		});

		AfterEach([this]()
		{
			TestString += FString(" World");
			TestEqual("Post Test-test: ", TestString, FString("Hello World"));
		});
	});
}


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------



BEGIN_DEFINE_SPEC(PlayerTest, "MySystem.MyTests.Player Health Test", EAutomationTestFlags::SmokeFilter | EAutomationTestFlags::ApplicationContextMask)
	ALearn_UE_CPP_101Character* Player;
	UWorld* World;
END_DEFINE_SPEC(PlayerTest)

void PlayerTest::Define()
{
	xDescribe("Character Tests Suite", [this]()
	{
		BeforeEach([this]()
		{
			World = FAutomationEditorCommonUtils::CreateNewMap();
			Player = World->SpawnActor<ALearn_UE_CPP_101Character>();
		});

		It("Should Succesfully spawn the player", [this]()
		{
			if (Player) {
				TestNull("Player is Valid", Player);
				TestEqual("InitHealth Should be Maxed", Player->Health, 100.0f);
			}
			
		});

		AfterEach([this]()
		{
			if(Player)
			Player->Destroy();
		});
	});
}

