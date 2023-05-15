// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTDecorator_BlackboardBase.h"
//#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Learn_UE_CPP_101Character.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AIController.h"


UMyBTDecorator_BlackboardBase::UMyBTDecorator_BlackboardBase()
{
	//BTDecorator_BlackboardBase has a 'BlackboardKey' attribute which we may define, filter, and use - if we need to define compound conditions based on the value of a Blackboard Key
	BlackboardKey.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(UMyBTDecorator_BlackboardBase, BlackboardKey));
	//bCreateNodeInstance
	//bNotifyTick
}

/*
EBlackboardNotificationResult UMyBTDecorator_BlackboardBase::OnBlackboardKeyValueChange(const UBlackboardComponent& Blackboard, FBlackboard::FKey ChangedKeyID)
{
	
	GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Green, FString("Decorator FIRED!"));
	bool bCondition = Blackboard.GetValueAsBool(*BlackboardKey.SelectedKeyName.ToString());
	if (bCondition)
	{
		GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Green, FString("Decorator Condition is TRUE!"));
		return EBlackboardNotificationResult::RemoveObserver;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Red, FString("Decorator Condition is FALSE"));
		return EBlackboardNotificationResult::ContinueObserving;
	}
	
}
*/

bool UMyBTDecorator_BlackboardBase::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{

	//bool bSuccess = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	/*
	if (!bSuccess)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, FString("Decorator is ALIVE"));
		return false;
	}
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString("Decorator Finished"));
	return true;
	*/

	//Decorators are executed when a Node in the BehaviorTree with the Decorator applied to it is about to execute - It is simply a check that runs before a node runs, 
	//and if the test is true/false, we can decide to abort the Node execution, lower priority nodes, or both.
	//By default (when using 'AbortSelf'), if the condition check returns true - the underlying BeahviorTree Node is allowed to execute - but if it returns false, the Node is aborted.
	
	ALearn_UE_CPP_101Character* Char = Cast<ALearn_UE_CPP_101Character>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (Char->GetMovementComponent()->IsFalling())
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




