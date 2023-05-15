// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBTDecorator_NewOne.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Learn_UE_CPP_101Character.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"


bool UMyBTDecorator_NewOne::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	ALearn_UE_CPP_101Character* Char = Cast<ALearn_UE_CPP_101Character>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (Char && Char->GetMovementComponent()->IsFalling())
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, FString("DECORATOR: Character JUMPED"));
		return false;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, FString("DECORATOR: Character is on ground"));
		return true;
	}
}
