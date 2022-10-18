// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomMovementComponent.h"

UCustomMovementComponent::UCustomMovementComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;
	bTickInEditor = true;
}

void UCustomMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UE_LOG(LogTemp, Display, TEXT("Movement IS Ticking!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"));

}

