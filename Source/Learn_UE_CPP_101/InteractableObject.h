// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interact.h"

#include "InteractableObject.generated.h"

UCLASS()
class LEARN_UE_CPP_101_API AInteractableObject : public AActor, public IInteract
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableObject();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* SM;

	void InteractWithObject_Implementation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
