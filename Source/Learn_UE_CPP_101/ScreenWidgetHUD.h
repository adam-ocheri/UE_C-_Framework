// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MasterUserWidget.h"
#include "ScreenWidgetHUD.generated.h"


/**
 * 
 */
UCLASS()
class LEARN_UE_CPP_101_API UScreenWidgetHUD : public UMasterUserWidget
{
	GENERATED_BODY()
	
public:
	UScreenWidgetHUD(const FObjectInitializer& ObjectInitializer);
	virtual void NativeOnInitialized();
	virtual void NativeConstruct();

	class UOverlay* Overlayer;
	class UGridPanel* BackPanel;
	class UGridPanel* HealthPanel;
	class UProgressBar* HealthBar;
	class USizeBox* HealthBar_R;
	class UTextBlock* Health_Text;
	class UImage* Backdrop;

	UTexture2D* Background_TextureObject;
	UTexture2D* BarEmpty_TextureObject;
	UTexture2D* BarFull_TextureObject;
};



