// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameUserSettings.h"

void UMyGameUserSettings::SetScreenResolution(FIntPoint Resolution)
{
	Super::SetScreenResolution(Resolution);
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, TEXT("Resolution was MODIFIED!!!!!"));
	
}
