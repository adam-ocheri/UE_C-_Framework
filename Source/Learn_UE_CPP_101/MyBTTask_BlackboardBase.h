// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MyBTTask_BlackboardBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class LEARN_UE_CPP_101_API UMyBTTask_BlackboardBase : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
	UMyBTTask_BlackboardBase();
	
private:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual FString GetStaticDescription() const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search", meta = (AllowPrivateAccess = true))
	float SearchRadius = 1000.0f;
};
