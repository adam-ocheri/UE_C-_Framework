// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "MyBTDecorator_BlackboardBase.generated.h"

/**
 * 
 */
UCLASS()
class LEARN_UE_CPP_101_API UMyBTDecorator_BlackboardBase : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()
		
		UMyBTDecorator_BlackboardBase();
	//virtual EBlackboardNotificationResult OnBlackboardKeyValueChange(const UBlackboardComponent& Blackboard, FBlackboard::FKey ChangedKeyID) override;

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
