// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyPlayerController.h"
#include "GameFramework/Controller.h"
#include "MyPlayerState.h"
#include "MyHUD.h"
#include "MyMyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class LEARN_UE_CPP_101_API AMyMyPlayerController : public AMyPlayerController
{
	GENERATED_BODY()

public:
	AMyMyPlayerController();
	virtual void BeginPlay();

	class ALearn_UE_CPP_101Character* MyPawn;

	virtual void SetupInputComponent() override;

	void LookUp(float Rate);

	void LookRight(float Rate);
	
	void JumpStart();

	void JumpEnd();

	
	
	AMyHUD* MyHUD;

	

	virtual void OnRep_PlayerState();

	AMyPlayerState* ThisPlayerState;

	virtual void InitPlayerState();

	

	virtual void Tick(float DeltaSeconds);

	

	void SetPlayerKills();

	int32 GetPlayerKills();

	

	void ExecuteConsoleCommand(FString Command);

	
	AMyPlayerState* GetThisPlayerState();
};
