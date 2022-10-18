// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacterMovementComponent.h"

UMyCharacterMovementComponent::UMyCharacterMovementComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;
	bTickInEditor = true;
	
}

void UMyCharacterMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FHitResult Hit;

	SafeMoveUpdatedComponent(FVector(0.1, 0.1, 0), GetLastUpdateRotation(), true, Hit);
	SafeMoveUpdatedComponent(FVector(-0.1, -0.1, 0), GetLastUpdateRotation(), true, Hit);
}