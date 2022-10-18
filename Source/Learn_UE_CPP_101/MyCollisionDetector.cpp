// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCollisionDetector.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"


// Sets default values
AMyCollisionDetector::AMyCollisionDetector(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(FName("My Root"));
	

	Collider_Box = CreateDefaultSubobject<UBoxComponent>(FName("Collision Box"));
	

	Collider_Capsule = CreateDefaultSubobject<UCapsuleComponent>(FName("Collision Capsule"));
	
	RootComponent = Root;
	Collider_Box->SetupAttachment(RootComponent);
	Collider_Capsule->SetupAttachment(RootComponent);

	Collider_Box->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);


	//Collider_Box->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	//Collider_Box/Capsule->GetCollisionObjectType();	By default, the Collision Type of colliders is WorldDynamic

	
	
}

// Called when the game starts or when spawned
void AMyCollisionDetector::BeginPlay()
{
	Super::BeginPlay();

	
	//Collider_Box->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	Collider_Box->OnComponentHit.AddUniqueDynamic(this, &AMyCollisionDetector::OnHit);
	Collider_Capsule->OnComponentBeginOverlap.AddUniqueDynamic(this, &AMyCollisionDetector::OnCapsuleBeginOverlap);
	

    
	
}

// Called every frame
void AMyCollisionDetector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
}

/*
void AMyCollisionDetector::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{


	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("COLLIDED - the collided Actor is: %s, while the Overlapped component is: %s"), *OtherActor->GetName(), *OverlappedComp->GetName()));


}
*/

void AMyCollisionDetector::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("COLLIDED - the collided Actor is: %s, while the Overlapped component is: %s"), *OtherActor->GetName(), *OverlappedComp->GetName()));

	
}

void AMyCollisionDetector::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("COLLIDED - the collided Actor is: %s, while the Overlapped component is: %s"), *OtherActor->GetName(), *HitComponent->GetName()));
}
