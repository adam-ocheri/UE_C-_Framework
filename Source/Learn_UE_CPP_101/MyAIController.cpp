// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include "MyEnemy.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
//#include "BehaviorTree/BlackboardData.h"
#include "UObject/ConstructorHelpers.h"
#include "Learn_UE_CPP_101Character.h"
#include "Kismet/GameplayStatics.h"

//#include "BehaviorTree/BlackboardComponent.h"
//#include "Perception/AISenseConfig.h"

#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AISenseConfig_Prediction.h"
#include "Perception/AISense_Prediction.h"

#include "NavigationSystem.h"





AMyAIController::AMyAIController() 
{
	
	//MyBlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
	StimulusSource = new FAIStimulus{};
	//PerceptionInfo = new FActorPerceptionBlueprintInfo{};

	static ConstructorHelpers::FObjectFinder <UBehaviorTree> BTAsset (TEXT("/Game/AI/MyBehaviorTree.MyBehaviorTree"));
	static ConstructorHelpers::FObjectFinder <UBlackboardData> BBAsset (TEXT("/Game/AI/MyBlackboard.MyBlackboard"));

	MyBehaviorTree = BTAsset.Object;
	MyBlackboard = BBAsset.Object;
	MyBehaviorTree.Get()->BlackboardAsset = MyBlackboard;

	MyBehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	//MyBlackboard.Get()->
	// 
	//AI Perception
	MyPerceptionComponent = GetAIPerceptionComponent();
	//	// Sight Perception
	MyPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SightConfig->SetMaxAge(1.0f);
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	MyPerceptionComponent->ConfigureSense(*SightConfig);
	//	// Hearing Perception
	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Hearing Config"));
	HearingConfig->SetMaxAge(1.0f);
	HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;
	HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;
	MyPerceptionComponent->ConfigureSense(*HearingConfig);

	//	// Damage Perception
	DamageConfig = CreateDefaultSubobject<UAISenseConfig_Damage>(TEXT("Damage Config"));
	DamageConfig->SetMaxAge(1.0f);
	MyPerceptionComponent->ConfigureSense(*DamageConfig);

	//	// Prediction Perception
	PredictionConfig = CreateDefaultSubobject<UAISenseConfig_Prediction>(TEXT("Prediction Config"));
	PredictionConfig->SetMaxAge(1.0f);
	MyPerceptionComponent->ConfigureSense(*PredictionConfig);

}

void AMyAIController::BeginPlay()
{
	Super::BeginPlay();
	
	//PerceptionInfo = new FActorPerceptionBlueprintInfo{};
	if (IsValid(MyBehaviorTree.Get()))
	{
		RunBehaviorTree(MyBehaviorTree.Get());
		MyBehaviorTreeComponent->StartTree(*MyBehaviorTree.Get());
		
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, FString("Behaviour Tree Is VALID"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString("Behaviour Tree Is NOT VALID"));
	}

	HumanEnemy = Cast<ALearn_UE_CPP_101Character>(UGameplayStatics::GetPlayerCharacter(this, 0));
	//AI Perception?
	//UMyAISense_Sight* SightSense = Cast <UMyAISense_Sight>(UMyAISense_Sight::StaticClass());

	//TSubclassOf<UAISense_Sight> SightSense = UMyAISense_Sight::StaticClass();

	

	if(SightConfig)
	{
		
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, FString("AI Sight Sense Is VALID"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString("AI Sight Sense Is NOT VALID"));

		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString("And Base Sense Is NOT VALID!!!!!!!!!!"));
		
	}

	
}

void AMyAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	
	FActorPerceptionBlueprintInfo PerceptionInfo;
	bool bPerceptionInfoExists = MyPerceptionComponent->GetActorsPerception(CurrentlyPerceivedActor, PerceptionInfo);


	
	for (FAIStimulus Stimulus : PerceptionInfo.LastSensedStimuli)
	{
		/*
		if (Stimulus.Type == SightConfig->GetSenseID() && Stimulus.GetAge() >= SightConfig->GetMaxAge())
		{
			Blackboard->SetValueAsBool(FName("HasLineOfSight"), false);
			GEngine->AddOnScreenDebugMessage(-1, DeltaSeconds, FColor::Green, FString::Printf(TEXT("Stimulus Age is Increasing: %f"), Stimulus.GetAge()));

		}
		else if (Stimulus.Type == SightConfig->GetSenseID() && Stimulus.GetAge() < SightConfig->GetMaxAge())
		{
			Blackboard->SetValueAsBool(FName("HasLineOfSight"), true);
			GEngine->AddOnScreenDebugMessage(-1, DeltaSeconds, FColor::Green, FString::Printf(TEXT("Stimulus Age is ok????:: -> %f"), Stimulus.GetAge()));
		}
		*/
		if (Stimulus.Type == SightConfig->GetSenseID())
		{
			*StimulusSource = Stimulus;
			if (Stimulus.IsActive())//(Stimulus.GetAge() >= SightConfig->GetMaxAge())
			{
				Blackboard->SetValueAsBool(FName("HasLineOfSight"), true);
				
				GEngine->AddOnScreenDebugMessage(-1, DeltaSeconds, FColor::Green, FString::Printf(TEXT("SIGHT - Stimulus Age is Valid: %f"), StimulusSource->GetAge()));
			}
			else if (Stimulus.IsExpired())//(Stimulus.GetAge() < SightConfig->GetMaxAge())
			{
				Blackboard->SetValueAsBool(FName("HasLineOfSight"), false);
				PredictEnemyLocation(HumanEnemy);
				//GEngine->AddOnScreenDebugMessage(-1, DeltaSeconds, FColor::Green, FString::Printf(TEXT("Stimulus Age has EXPIRED: %f"), StimulusSource->GetAge()));
			}

		}
		else if (Stimulus.Type == HearingConfig->GetSenseID())
		{
			*StimulusSource = Stimulus;
			if (Stimulus.IsActive())
			{
				GEngine->AddOnScreenDebugMessage(-1, DeltaSeconds, FColor::Yellow, FString::Printf(TEXT("HEARING - Stimulus Age is Valid: %f"), StimulusSource->GetAge()));
			}
		}
		else if (Stimulus.Type == DamageConfig->GetSenseID())
		{
			*StimulusSource = Stimulus;
			if (Stimulus.IsActive())
			{
				GEngine->AddOnScreenDebugMessage(-1, DeltaSeconds, FColor::Red, FString::Printf(TEXT("DAMAGE - Stimulus Age is Valid: %f"), StimulusSource->GetAge()));
			}
			//Damage sense setup requires a number of things.
			/*
				1. Add the UAISenseConfig_Damage into the AIC constuctor, as with all other senses - 
				   to enable the sense
				2. The class of the Damaging actor will need to call TakeDamage() on the actor that should be damaged, and report a Damage Event - 
				   to send the damage data to the hit entity and register it for the Damage perception
				3. The class of the Damaged actor will need to implement a damage delegate such as 'OnTakeAnyDamage.AddUniqueDynamic()' -
				   to recieve the data coming from the Damaging actor to finally apply the damage to the Damaged actor.

			*/
		}
		else if (Stimulus.Type == PredictionConfig->GetSenseID())
		{
			*StimulusSource = Stimulus;
			if (Stimulus.IsActive())
			{
				FCollisionQueryParams CollisionQuery;
				FHitResult HitResults;
				AMyEnemy* Self = Cast<AMyEnemy>(UGameplayStatics::GetActorOfClass(GetWorld(), AMyEnemy::StaticClass()));
				CollisionQuery.AddIgnoredActor(Self);
				bool bHit = GetWorld()->LineTraceSingleByChannel(
					HitResults, Self->GetActorLocation(), Stimulus.StimulusLocation, ECollisionChannel::ECC_Camera, CollisionQuery);

				DrawDebugLine(GetWorld(), HitResults.TraceStart, HitResults.TraceEnd, FColor::Orange);

				GEngine->AddOnScreenDebugMessage(-1, DeltaSeconds, FColor::Red, FString::Printf(TEXT("DAMAGE - Stimulus Age is Valid: %f"), StimulusSource->GetAge()));
			}
		}
		
	}
	

	/*
	if (StimulusSource && StimulusSource->Type == SightConfig->GetSenseID() && StimulusSource->GetAge() >= SightConfig->GetMaxAge())
	{
		Blackboard->SetValueAsBool(FName("HasLineOfSight"), false);
		GEngine->AddOnScreenDebugMessage(-1, DeltaSeconds, FColor::Green, FString::Printf(TEXT("Stimulus Age is Increasing: %f"), StimulusSource->GetAge()));

	}
	else if (StimulusSource && StimulusSource->Type == SightConfig->GetSenseID() && StimulusSource->GetAge() < SightConfig->GetMaxAge())
	{
		Blackboard->SetValueAsBool(FName("HasLineOfSight"), true);
		GEngine->AddOnScreenDebugMessage(-1, DeltaSeconds, FColor::Green, FString::Printf(TEXT("Stimulus Age is ok????:: -> %f"), StimulusSource->GetAge()));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, DeltaSeconds, FColor::Red, FString("FUCK A YOU"));
	}
	*/

	/*
	if (bShouldUpdateActors)
	{
		TArray <AActor*, FDefaultAllocator> PerceivedActors;
		MyPerceptionComponent->RequestStimuliListenerUpdate();
		MyPerceptionComponent->GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PerceivedActors);
		GEngine->AddOnScreenDebugMessage(-1, DeltaSeconds, FColor::Orange, FString("Attempt Update............"));
		//bShouldUpdateActors = false;

		if (PerceivedActors.Num() > 0)
		{
			for (AActor* Actor : PerceivedActors)
			{
				
				bool bPerceptionInfoExists = MyPerceptionComponent->GetActorsPerception(Actor, PerceptionInfo);
				if (bPerceptionInfoExists)
				{
					CurrentlyPerceivedActor = PerceptionInfo.Target;

					GEngine->AddOnScreenDebugMessage(-1, DeltaSeconds, FColor::Green, FString("Percieved Actors are Valid"));
					GEngine->AddOnScreenDebugMessage(-1, DeltaSeconds, FColor::Green, FString::Printf(TEXT("Number of Actors in Array: %i"), PerceivedActors.Num()));

					for (FAIStimulus Stimulus : PerceptionInfo.LastSensedStimuli)
					{
						GEngine->AddOnScreenDebugMessage(-1, DeltaSeconds, FColor::Purple, FString("Stimulus is being SENSED"));
						*StimulusSource = FAIStimulus{ Stimulus };

						if (StimulusSource->Type == SightConfig->GetSenseID())
						{
							if (StimulusSource->GetAge() >= SightConfig->GetMaxAge())
							{
								GEngine->AddOnScreenDebugMessage(-1, DeltaSeconds, FColor::Green, FString::Printf(TEXT("Stimulus Age is Increasing: %f"), StimulusSource->GetAge()));
								Blackboard->SetValueAsBool(FName("HasLineOfSight"), false);

							}
							else if (StimulusSource->GetAge() < SightConfig->GetMaxAge())
							{
								Blackboard->SetValueAsBool(FName("HasLineOfSight"), true);
								GEngine->AddOnScreenDebugMessage(-1, DeltaSeconds, FColor::Green, FString::Printf(TEXT("Stimulus Age is OK: %f"), StimulusSource->GetAge()));
							}
						}
						else
						{
							//bShouldUpdateActors = true;
							GEngine->AddOnScreenDebugMessage(-1, DeltaSeconds, FColor::Red, FString("Should UPDATE"));
						}
					}
					 
				}

			}
		}
	}
	*/

}

void AMyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	SelfEntity = Cast<AMyEnemy>(InPawn);

	if (IsValid(Blackboard.Get()) && IsValid(MyBehaviorTree.Get()))
	{
		Blackboard->InitializeBlackboard(*MyBehaviorTree.Get()->BlackboardAsset);
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, FString("Posses: Blackboard Is VALID"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString("Posses: Blackboard Is NOT VALID"));
	}
}

void AMyAIController::ActorsPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	
	for (AActor* Actor : UpdatedActors)
	{
		//FActorPerceptionBlueprintInfo PerceptionInfo;
		//bool bPerceptionInfoExists = MyPerceptionComponent->GetActorsPerception(Actor, *PerceptionInfo);

		
		CurrentlyPerceivedActor = Actor;
		/*
		for (FAIStimulus Stimulus : PerceptionInfo->LastSensedStimuli)
		{
			
			FAISenseID SightID = SightConfig->GetSenseID();
			FAISenseID HearingID = HearingConfig->GetSenseID();
			
			if (Stimulus.Type == SightID)
			{
				PerceptionComponent->RequestStimuliListenerUpdate();
				//*StimulusSource = Stimulus;
				StimulusSource = &Stimulus;
				
				Blackboard->SetValueAsBool(FName("HasLineOfSight"), true);
				Blackboard->SetValueAsVector(FName("TargetLocation"), GetRandomLocationAroundTarget(Stimulus.StimulusLocation));
				GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("I SEE YOU!!!!!!!!!!!!!!!!!!!!!!!! - Stimulus Age: %f"), Stimulus.GetAge()));
								
			}
			else if (Stimulus.Type == HearingID)
			{

			}
			
		}
		*/
	}
	
}

FVector AMyAIController::GetRandomLocationAroundTarget(FVector StimulusLocation)
{
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	FNavLocation NavLocation;
	bool bLocationFound = NavSystem->GetRandomPointInNavigableRadius(StimulusLocation, 50.0f, NavLocation);

	if (NavSystem && bLocationFound)
	{
		return NavLocation.Location;
	}
	return FVector(0.0f, 0.0f, 0.0f);
}

void AMyAIController::PredictEnemyLocation(AActor* PercievedActor)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Turquoise, FString("PREDICTION EVENT FIRED"));
	if (PercievedActor->GetVelocity().Length() > 0)
	{
		UAISense_Prediction::RequestControllerPredictionEvent(this, PercievedActor, 1.0f);
	}
	
}