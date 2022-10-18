// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Learn_UE_CPP_101Character.h"		// The Player class to be referenced by GetPlayerCharacter()
#include "Kismet/GameplayStatics.h"			// UGameplayStatics
#include "Kismet/KismetMathLibrary.h"		// UKismetMathLibrary

#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"


UCLASS()
class LEARN_UE_CPP_101_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

	UPROPERTY(EditAnywhere)
		FVector PlatformVelocity {100, 0, 0};

	FVector InitialLocation;

	UPROPERTY(EditAnywhere)
		float DistanceThreshold  =  500;

	UPROPERTY(EditAnywhere)
		FRotator RotationVelocity;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
