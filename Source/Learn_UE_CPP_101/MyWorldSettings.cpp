// Fill out your copyright notice in the Description page of Project Settings.


#include "MyWorldSettings.h"

AMyWorldSettings::AMyWorldSettings(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	KillZ = -200;
	bWorldGravitySet = true;
	WorldGravityZ = -300;
	//AWorldSettings is most easily changed in the default classes in the prject settings ?BUT HOW can i initialize a dedicated WorldSettings class for EACH world?
	//Can set values for settings in the constructor - but any change to a value will need a Development Editor rebuild in order for changes to take effect.
}

void AMyWorldSettings::BeginPlay()
{
	Super::BeginPlay();

	//GetWorld()->PersistentLevel->SetWorldSettings(this);
}