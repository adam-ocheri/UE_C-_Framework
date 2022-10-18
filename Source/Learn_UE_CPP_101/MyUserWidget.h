// Fill out your copyright notice in the Description page of Project Settings.

//-----------------------------------------------------------------This is the MAIN MENU UserWidget-----------------------------------------------------------------\\

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MasterUserWidget.h"

#include "MyUserWidget.generated.h"


/**
 * 
 */
UCLASS()
class LEARN_UE_CPP_101_API UMyUserWidget : public UMasterUserWidget //, public IMyInterface
{
	GENERATED_BODY()
	
		/*
			The main menu class could potentialy be derived under another parent Menu class. From this parent class both the MainMenu and 
			the Settings menu (or any other menu class we may need) could all be derived from - though this is not implemented in this example - despite the fact that this could be 
			very favorable, and add additional flexiblity to the design of our UI system.
			If we were to implment an additional parent class for all menu widgets to inherit from, it should also be a C++ only class that is not added to the viewport- and it's 
			children could be extended to more C++ and BP.

			For our example, we layout a very basic main menu widget, With some panel widgets, text and button elements, and even a texture and a material.
		*/

public:

	UMyUserWidget(const FObjectInitializer& ObjectInitializer);
	//virtual ~UMyUserWidget() = default;
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);


	


	UFUNCTION()
		void StartGame();

	UFUNCTION()
		void SettingsMenu();

	UFUNCTION()
		void QuitGame();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UOverlay* Overlayer_01;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UVerticalBox* Container;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* MyText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Start;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Settings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Quit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* MyImage;								//image widget

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* StartButton_Image;						//Texture

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInterface* Material;						//Material

	UPROPERTY(Transient, BlueprintReadOnly, meta = (BindWidgetAnim))
	UWidgetAnimation* NewAnimation;

	//ComboBox start
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UComboBoxString* Difficulty;

	UFUNCTION()
	virtual void HandleOpening();

	
	UFUNCTION()
	virtual void HandleSelectionChanged(FString Item, ESelectInfo::Type Type);
	//ComboBox end



	//Widget Switcher Start
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UGridPanel* Tabs_Panel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UWidgetSwitcher* Switcher;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Button_3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Text_B1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Text_B2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Text_B3;

	UFUNCTION()
	void OpenTab1();

	UFUNCTION()
	void OpenTab2();

	UFUNCTION()
	void OpenTab3();
	//Widget Switcher end



private:

	class UTextBlock* Start_Text;

	class UTextBlock* Settings_Text;

	class UTextBlock* Quit_Text;
	
	
	
};
