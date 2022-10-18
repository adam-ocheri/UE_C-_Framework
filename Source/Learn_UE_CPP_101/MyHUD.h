// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class LEARN_UE_CPP_101_API AMyHUD : public AHUD
{
	GENERATED_BODY()

public:
	AMyHUD();

	virtual void DrawHUD();

	virtual void BeginPlay();
	
	void SpawnScreenHUDWidget_StartGame();

	void SpawnMainMenu();
	
	void SpawnSettingsMenu();
	
	FVector2D ScreenResolution;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> MainMenuWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> SettingsMenu;

private:
	class UMyUserWidget* MainMenu;
	class USettingsMenu* MenuSettings;
	class UScreenWidgetHUD* ScreenHUD;
	class UMasterUserWidget* MasterWidget;
};
