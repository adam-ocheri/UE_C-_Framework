// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObject.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AInteractableObject::AInteractableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	SM = CreateDefaultSubobject<UStaticMeshComponent>(FName("Static Mesh Comp"));
	SM->SetupAttachment(RootComponent);

}

void AInteractableObject::InteractWithObject_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, FString("Some Object has been Interacted With!"));
}

// Called when the game starts or when spawned
void AInteractableObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

