// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MasterUserWidget.h"
#include "SettingsMenu.generated.h"


/**
 * 
 */
UCLASS()
class LEARN_UE_CPP_101_API USettingsMenu : public UMasterUserWidget
{
	GENERATED_BODY()

public:

	/*
		
		The settings menu, similarly to the MainMenu, should also be derived from a MenuMaster widget class  (again, not demonstrated in this example).

		This is a very simple example for a settings menu, containing a checkbox and a slider for a demonstration of how interactive UI elements that the user interacts with
		can be used to modify data somewhere else, outside of the widget itself.
		In our example, this data passed from the widget will be saved in the GameInstance class - in order for this data to remain persistant across levels.
	
	
	*/
	USettingsMenu(const FObjectInitializer& ObjectInitializer);

	virtual void NativeOnInitialized();

	virtual void NativeConstruct();

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	UFUNCTION()
		void OnCheckStateChanged(bool bIsChecked);

	UFUNCTION()
		void OnValueChanged(float InValue);

	UFUNCTION()
		void OnBackPressed();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UOverlay* Overlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UVerticalBox* VBox_Container;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UVerticalBox* VBox_Container_2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UCheckBox* OptionA_CheckBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class USlider* OptionB_Slider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_Back;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Text_Option_A;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Text_Option_B;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Text_Back;

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* TextureObject;
	
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* SpinnerAnimation;

	

	

	


	
};
