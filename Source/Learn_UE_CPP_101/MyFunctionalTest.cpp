// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFunctionalTest.h"
#include "MyEnemy.h"
#include "MyAIController.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
//#include "Kismet/GameplayStatics.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"


void AMyFunctionalTest::BeginPlay()
{
	Super::BeginPlay();
	TimeLimit = 5.0f;
	TimesUpMessage = FText::FromString("YOU LOSE TEST FAILED!");
	TimesUpResult = EFunctionalTestResult::Failed;
	
	

	//FTimerHandle Handle;
	//GetWorld()->GetTimerManager().SetTimer(Handle, this, &AMyFunctionalTest::TimerEnd, 15.0f, false);
}

void AMyFunctionalTest::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//AssertTrue(IsReady(), FString("Asserting..."), this);
	if (AssertIsValid(NPC, "NPC should be Valid!!!", this))
	{
		//Approace 1 to get character controller
		//AController* Ctrl = NPC->GetController();
		//AMyAIController* AIC = Cast<AMyAIController>(Ctrl);
		
		//Approace 1.5 to get character controller
		//AMyAIController* AIC = NPC->GetController<AMyAIController>();

		//Approace 2 to get character controller
		AAIController* AIC = UAIBlueprintHelperLibrary::GetAIController(NPC);

		if (AssertIsValid(AIC, "AIC should be Valid", this)) {
			bool bCondition = AIC->GetBlackboardComponent()->GetValueAsBool(FName("HasLineOfSight"));
			
			if (bCondition)
			{
				FinishTest(EFunctionalTestResult::Succeeded, FString("Test finished - AI see player Succesfully."));
			}
		}
		else
		{
			FinishTest(EFunctionalTestResult::Failed, FString("AI Controller Failed to initialize!!!!!!"));
		}
		
	}
	else
	{
		FinishTest(EFunctionalTestResult::Failed, FString("AI NPC Failed to initialize!"));
	}
}

void AMyFunctionalTest::TimerEnd()
{
	FinishTest(EFunctionalTestResult::Failed, FString("AI Didn't see player!"));
}
