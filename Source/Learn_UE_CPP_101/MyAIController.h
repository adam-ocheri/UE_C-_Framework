// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "MyAIController.generated.h"

//forward declarations
class UBehaviorTreeComponent;


/**
 * 
 */
UCLASS()
class LEARN_UE_CPP_101_API AMyAIController : public AAIController
{
	GENERATED_BODY()

		AMyAIController();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void OnPossess(APawn* InPawn) override;
	
	virtual void ActorsPerceptionUpdated(const TArray<AActor*> &UpdatedActors);
	class UAIPerceptionComponent* MyPerceptionComponent;
	class UAISenseConfig_Sight* SightConfig;
	class UAISenseConfig_Hearing* HearingConfig;
	class UAISenseConfig_Damage* DamageConfig;
	class UAISenseConfig_Prediction* PredictionConfig;
	
	bool bEnemyOnSight;
	class AMyEnemy* SelfEntity;
	AActor* CurrentlyPerceivedActor;
	
	
public:
	FVector GetRandomLocationAroundTarget(FVector StimulusLocation);
	FAIStimulus* StimulusSource = nullptr;
	//FActorPerceptionBlueprintInfo* PerceptionInfo = nullptr;
	bool bShouldUpdateActors = true;
	void PredictEnemyLocation(AActor* PercievedActor);
	

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBehaviorTree> MyBehaviorTree;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBlackboardData> MyBlackboard;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBehaviorTreeComponent> MyBehaviorTreeComponent;

	//AActor* PerceivedActor;
	class ALearn_UE_CPP_101Character* HumanEnemy;
};

