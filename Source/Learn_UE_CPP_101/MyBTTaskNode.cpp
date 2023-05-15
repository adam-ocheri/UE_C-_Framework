// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTaskNode.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UMyBTTaskNode::UMyBTTaskNode()
{
	NodeName = TEXT("Find Random Location");
}

EBTNodeResult::Type UMyBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FNavLocation ResultLocation;

	// Get AI Pawn
	AAIController* AIController = OwnerComp.GetAIOwner();
	const APawn* AIPawn = AIController->GetPawn();

	//Get Pawn Location
	const FVector StartLocation = AIPawn->GetActorLocation();

	FBlackboardKeySelector Key;

	//Get NavSystem and a reachable vector point in radius
	const UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
	if (IsValid(NavSys) && NavSys->GetRandomPointInNavigableRadius(StartLocation, SearchRadius, ResultLocation))
	{
		AIController->GetBlackboardComponent()->SetValueAsVector(FName("TargetLocation"), ResultLocation.Location);
	}

	//Notify BehaviorTree the task is finished executing
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}

FString UMyBTTaskNode::GetStaticDescription() const
{
	return FString::Printf(TEXT("Vector: Target"));
}
