// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEngineSubsystem.h"

void UMyEngineSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UE_LOG(LogTemp, Warning, TEXT("My Engine Subsystem has Initialized!!!"));

	UE_LOG(LogTemp, Warning, TEXT("Subsystem Name: %s"), *Collection.GetReferencerName());
	
}

void UMyEngineSubsystem::Deinitialize()
{
	Super::Deinitialize();
}
