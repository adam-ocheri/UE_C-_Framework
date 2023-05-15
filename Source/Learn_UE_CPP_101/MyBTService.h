// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "MyBTService.generated.h"

/**
 * 
 */
UCLASS()
class LEARN_UE_CPP_101_API UMyBTService : public UBTService
{
	GENERATED_BODY()

	UMyBTService(const FObjectInitializer &ObjectInitializer);

	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

	virtual void OnInstanceCreated(UBehaviorTreeComponent& OwnerComp);
};
