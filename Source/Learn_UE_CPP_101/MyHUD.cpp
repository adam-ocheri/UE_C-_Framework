// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "MyMyPlayerController.h"

#include "MasterUserWidget.h"
#include "MyUserWidget.h" //MainMenu.h
#include "SettingsMenu.h"
#include "ScreenWidgetHUD.h"




//#include "Blueprint/WidgetBlueprintLibrary.h"





AMyHUD::AMyHUD()
{
	//If we want to instantiate a BPWidget derived class, we'll need to use ConstructorHelpers to get the directory of the desired BlueprintWidget class.

	static ConstructorHelpers::FClassFinder<UMyUserWidget> WidgetBPClass (TEXT("/Game/Blueprints/MyUserWidget_BP"));
	MainMenuWidget = WidgetBPClass.Class;

	static ConstructorHelpers::FClassFinder<USettingsMenu> SettingsMenuBPClass(TEXT("/Game/Blueprints/BP_SettingsMenu"));
	SettingsMenu = SettingsMenuBPClass.Class;
	
}

void AMyHUD::BeginPlay()
{
	ScreenResolution = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	MasterWidget = CreateWidget<UMasterUserWidget>(GetOwningPlayerController(), UMasterUserWidget::StaticClass());
	//MasterWidget->AddToViewport(); if we want the widget to tick, we will need to add it to the viewport - eventhough it doesn't have any visual elements in it
	SpawnMainMenu();
}

void AMyHUD::DrawHUD()
{
	Super::DrawHUD();
	//DrawRect(FLinearColor::Gray, ScreenResolution.X / 2.0f - 64.0f, ScreenResolution.Y / 2.0f - 64.0f, 128.0f, 128.0f);
}

void AMyHUD::SpawnScreenHUDWidget_StartGame()
{
	ScreenHUD = CreateWidget<UScreenWidgetHUD>(GetOwningPlayerController(), UScreenWidgetHUD::StaticClass());

	if (ScreenHUD)
	{
		FInputModeGameOnly InputMode;
		GetOwningPlayerController()->SetInputMode(InputMode);
		GetOwningPlayerController()->bShowMouseCursor = false;
		ScreenHUD->AddToViewport();
	}
}

void AMyHUD::SpawnMainMenu()
{
	if (MainMenuWidget)
	{
		if (!MainMenu)
		{
			MainMenu = CreateWidget<UMyUserWidget>(GetOwningPlayerController(), MainMenuWidget);
			MainMenu->ShowWidget();
			MainMenu->AddToViewport();
		}
		else
		{
			MainMenu->ShowWidget();
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, TEXT("MAIN MENU IS NOT WORKING!"));
	}

	
	
	

}


void AMyHUD::SpawnSettingsMenu()
{
	
	if (SettingsMenu)
	{	
		if (!MenuSettings)
		{
			MenuSettings = CreateWidget<USettingsMenu>(GetOwningPlayerController(), SettingsMenu);
			MenuSettings->AddToViewport();
			MenuSettings->ShowWidget();
		}
		else
		{
			MenuSettings->ShowWidget();
		}

		
	}
	
	

	
}




//htmk - is the framework
//css - the stlying
//javaS - the vehaviour