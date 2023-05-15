// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnemy.h"
#include "MyAIController.h"
#include "Learn_UE_CPP_101Character.h"
#include "UObject/ConstructorHelpers.h"


// Sets default values
AMyEnemy::AMyEnemy(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//ConstructorHelpers::FClassFinder<AMyAIController> AIC (TEXT("Blueprint'/Game/MyBPAIController.MyBPAIController'"));
	//MyAIControllerClass = Cast<AMyAIController>(AMyAIController::StaticClass());
	AIControllerClass = AMyAIController::StaticClass();
	//SetCanBeDamaged(true);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SKMesh (TEXT("/Game/Characters/Mannequins/Meshes/SKM_Manny.SKM_Manny"));
	GetMesh()->SetSkeletalMesh(SKMesh.Object);
	GetMesh()->AddLocalRotation(FRotator(0, -90, 0));
	GetMesh()->AddLocalOffset(FVector(0, 0, -96));
	
}

// Called when the game starts or when spawned
void AMyEnemy::BeginPlay()
{
	Super::BeginPlay();
	if (AIControllerClass)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, FString::Printf(TEXT("AI Controller class name is: %s"), *AIControllerClass->GetName()));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, FString("AI Controller class is NOT VALID!!"));
	}
	OnTakeAnyDamage.AddUniqueDynamic(this, &AMyEnemy::SelfTakeDamage);
	//
}

void AMyEnemy::SelfTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	
	if (DamageCauser->IsA<ALearn_UE_CPP_101Character>())
	{
		GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Red, FString("DAMAGE DEALT TO ME!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"));
		
		//UE Reflection System and CDO
		ALearn_UE_CPP_101Character* Char = ALearn_UE_CPP_101Character::StaticClass()->GetDefaultObject<ALearn_UE_CPP_101Character>();
		//ALearn_UE_CPP_101Character* Char = GetMutableDefault<ALearn_UE_CPP_101Character>();
		Char->Health -= 1;
		//Char->SaveConfig();
	}
	
}

// Called every frame
void AMyEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

