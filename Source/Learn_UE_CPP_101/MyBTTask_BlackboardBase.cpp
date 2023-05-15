// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_BlackboardBase.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UMyBTTask_BlackboardBase::UMyBTTask_BlackboardBase()
{
	NodeName = TEXT("Find Random Location In Navigable Surrounding");

	//Accept only BB Keys of the desired type
	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UMyBTTask_BlackboardBase, BlackboardKey));
}

EBTNodeResult::Type UMyBTTask_BlackboardBase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
	EBTNodeResult::Type NodeResult;
	NodeResult = EBTNodeResult::Succeeded;
	FinishLatentTask(OwnerComp, NodeResult);
	GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Orange, FString("Post RETURn ABORT"));

	return NodeResult;
}

EBTNodeResult::Type UMyBTTask_BlackboardBase::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Red, FString("BT Task has ABORTED!"));
	
	return EBTNodeResult::Aborted;
}

FString UMyBTTask_BlackboardBase::GetStaticDescription() const
{
	return FString::Printf(TEXT("Vector: %s"), *BlackboardKey.SelectedKeyName.ToString());
}
