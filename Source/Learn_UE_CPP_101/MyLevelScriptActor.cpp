// Fill out your copyright notice in the Description page of Project Settings.


#include "MyLevelScriptActor.h"
#include "MyWorldSettings.h"
#include "UObject/ConstructorHelpers.h"

AMyLevelScriptActor::AMyLevelScriptActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<AMyWorldSettings> CustomWorldSettings(TEXT("/Game/BP_MyWorldSettings"));
	MyWorldSettings = CustomWorldSettings.Class;
	
}

void AMyLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, FString("LEVEL IS LOADED!!"));
	
	//MyWorldSettings = AMyWorldSettings::StaticClass();
	if (MyWorldSettings != nullptr)
	{
		
		GEngine->WorldSettingsClass = MyWorldSettings;
		//MyWorldSettings->KillZ = -5000;
		//MyWorldSettings->WorldGravityZ = 0;
		UE_LOG(LogTemp, Warning, TEXT("WorldSettings SUCCESS!!!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("WorldSettings FAIL!!!!!!!!!!!!!!!!!!!!!!"));
	}
}

void AMyLevelScriptActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, FString("LEVEL IS RUNNING!!"));
}



AActor* AMyLevelScriptActor::DoSomethingToSomeActor(AActor* SomeActor)
{
	return SomeActor;
}


