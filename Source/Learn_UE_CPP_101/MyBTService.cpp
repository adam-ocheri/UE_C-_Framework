// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTService.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UMyBTService::UMyBTService(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = TEXT("Service Demo");
	bNotifyBecomeRelevant = true;	 //
	bNotifyCeaseRelevant = true;	//===> For these things, we should really consider the parent of all of the BehaviorTree nodes - the UBTNode class
	//bCreateNodeInstance = true;  // If node is instanced, it means that it will be synced across any working Behavior Tree graphs.
	

}

void UMyBTService::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, FString("SERVICE: Became Relevant"));
	
}

void UMyBTService::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnCeaseRelevant(OwnerComp, NodeMemory);
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString("SERVICE: No Longer Relevant"));
}

void UMyBTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	if(IsInstanced())
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, FString("SERVICE: Is Instanced"));
	FVector NewTargetLocation = OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();
	OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsVector(FName("TargetLocation"), NewTargetLocation);
}

void UMyBTService::OnInstanceCreated(UBehaviorTreeComponent& OwnerComp)
{
	Super::OnInstanceCreated(OwnerComp);
	GEngine->AddOnScreenDebugMessage(-1, 150.0f, FColor::Orange, FString("SERVICE: InstanceCreated!!!!!"));
}
