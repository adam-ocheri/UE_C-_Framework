// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "MyGameInstance.generated.h"

/*

GameInstance: high-level manager object for an instance of the running game. 
Spawned at game creation and not destroyed until game instance is shut down. Running as a standalone game, 
there will be one of these. Running in PIE (play-in-editor) will generate one of these per PIE instance.
 
Init()
Virtual function to allow custom GameInstances an opportunity to set up what it needs

StartGameInstance()
Starts the GameInstance state machine running

OnStart()
Called when the game instance is started either normally or through PIE.

Shutdown()
Virtual function to allow custom GameInstances an opportunity to do cleanup when shutting down

ReceiveInit()
Opportunity for blueprints to handle the game instance being initialized.

ReceiveShutdown()
Opportunity for blueprints to handle the game instance being shutdown.

OnWorldChanged
(
	UWorld* OldWorld,
	UWorld* NewWorld
)
Callback from the world context when the world changes
  

  -SaveGame
  -TimerManager
  -Subsystems
  -?GameUserSettings?

  //!! THERE IS a c++ 'level blueprint': ALevelScriptActor - LevelBP will need to be re-parented to our custom ALevelScriptActor - thus, you have no way of getting the refernces 
															 of the actors in the world through c++ - only in the LevelBP.
															 Though, you can create functionality in the c++ LevelScriptActor which would be inherited to the BP Level.

	!!
 */
UCLASS()
class LEARN_UE_CPP_101_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

	UMyGameInstance(const FObjectInitializer& ObjectInitializer); //?Might be a good place to initialize some GLOBALLY NEEDED assets here in the GI via Constructor helpers - making them persistantly loaded across the session
public:
	
	virtual void Init() override;

	virtual void Shutdown();

	void SaveStats();

	void LoadStats();

	FString SaveSlot;

	class UMySaveGame* SaveGameObject;

	bool bAbilities = true;

	float Thershold = 1.0f;

	void OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld);

	void DoSomething();

	UFUNCTION()
	void ActuallyDoSomething();

	UFUNCTION()
	void Manipulate();

	
};
