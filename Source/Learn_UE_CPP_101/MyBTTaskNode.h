// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MyBTTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class LEARN_UE_CPP_101_API UMyBTTaskNode : public UBTTaskNode
{
	GENERATED_BODY()

		UMyBTTaskNode();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual FString GetStaticDescription() const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search", meta = (AllowPrivateAccess = true))
		float SearchRadius = 1000.0f;
};
