// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"



// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	InitialLocation = GetActorLocation();
	
	
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	

	SetActorLocation(GetActorLocation() + (PlatformVelocity * DeltaTime));

	float DistanceCrossed 
		= FVector::Dist(GetActorLocation(),InitialLocation) ;
	
	if (DistanceCrossed >= DistanceThreshold)
	{
		
		FVector NormalizedDirection = PlatformVelocity.GetSafeNormal();  
		FVector DistanceToMove = NormalizedDirection * DistanceThreshold;	
		InitialLocation += DistanceToMove;  
											
		SetActorLocation(InitialLocation);   
											

		PlatformVelocity *= -1;
	
	}

	SetActorRotation(UKismetMathLibrary::ComposeRotators((RotationVelocity * DeltaTime), GetActorRotation()) );

	

	



	//ACharacter *Target = UGameplayStatics::GetPlayerCharacter(this, 0);

	//FRotator Rot = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), Target->GetActorLocation());
	
	//SetActorRotation(Rot);


	
}

