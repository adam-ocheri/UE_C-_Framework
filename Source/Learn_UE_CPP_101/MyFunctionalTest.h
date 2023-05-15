// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FunctionalTest.h"
#include "MyFunctionalTest.generated.h"

/**
 1. Create new level for test
 2. Create new "AFunctionalTest" derived class
 3. Add actors you want to test into the test level
 4. Add your FunctionalTest Actor to the test level, and add a camera to set as the ObservationPoint for the test Actor
 5. Preapare the test script:
	A) declare UPROPERTIES for any actor that should be included in the test
	B) declare overrides for Constructor/BeginPlay and Tick (if tick is needed by your test)
	C) Set default values in the constructor/Begin play and/or initialize any data that the test might require
	D) Set up the conditions for the test on Tick, and use FinishTest() to return the test result based on the set conditions

To run the test, open Session Frontend, and Navigate to the Automation Tab.
Then any functional tests we have in our project would be located under the Project/FunctionalTests directory.

BONUS: Assertions
 */
UCLASS()
class LEARN_UE_CPP_101_API AMyFunctionalTest : public AFunctionalTest
{
	GENERATED_BODY()

	//AMyFunctionalTest();

protected:
	virtual void BeginPlay();
	virtual void Tick(float DeltaSeconds);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class AMyEnemy* NPC;

	bool bSuccess;

	UFUNCTION()
	void TimerEnd();
	
};
