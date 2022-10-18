// Fill out your copyright notice in the Description page of Project Settings.


#include "SettingsMenu.h"
#include "MyGameInstance.h"
#include "UObject/ConstructorHelpers.h"


#include "Components/Overlay.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"
#include "Components/CheckBox.h"
#include "Components/Slider.h"
#include "Components/Button.h"
#include "Components/OverlaySlot.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/ButtonSlot.h"
//#include "Blueprint/WidgetTree.h"





USettingsMenu::USettingsMenu(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder <UTexture2D> TextureAsset(TEXT("/Game/StarterContent/Textures/T_Burst_M"));
	TextureObject = TextureAsset.Object;
}

void USettingsMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UMyGameInstance* GI = Cast<UMyGameInstance>(GetGameInstance());
	OptionA_CheckBox->SetIsChecked(GI->bAbilities);
	OptionB_Slider->SetValue(GI->Thershold);

	UVerticalBoxSlot* Slot_00 = VBox_Container->AddChildToVerticalBox(Text_Option_A);
	UVerticalBoxSlot* Slot_01 = VBox_Container->AddChildToVerticalBox(OptionA_CheckBox);
	UVerticalBoxSlot* Slot_02 = VBox_Container->AddChildToVerticalBox(Text_Option_B);
	UVerticalBoxSlot* Slot_03 = VBox_Container->AddChildToVerticalBox(OptionB_Slider);
	UVerticalBoxSlot* Slot_04 = VBox_Container_2->AddChildToVerticalBox(Text_Back);
	UVerticalBoxSlot* Slot_05 = VBox_Container_2->AddChildToVerticalBox(Button_Back);

	UOverlaySlot* Slot_Main = Overlayer->AddChildToOverlay(VBox_Container);
	Slot_Main->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
	Slot_Main->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);

	UOverlaySlot* Slot_Back = Overlayer->AddChildToOverlay(VBox_Container_2);
	Slot_Back->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Left);
	Slot_Back->SetVerticalAlignment(EVerticalAlignment::VAlign_Bottom);
	Slot_Back->SetPadding(FMargin(100, 0, 0, 100));

	Overlayer = Cast<UOverlay>(GetRootWidget());

	


	WidgetTree->RootWidget = Overlayer;
}

void USettingsMenu::NativeConstruct()
{

	Super::NativeConstruct();

	

	OptionA_CheckBox->OnCheckStateChanged.AddDynamic(this, &USettingsMenu::OnCheckStateChanged);
	OptionB_Slider->OnValueChanged.AddDynamic(this, &USettingsMenu::OnValueChanged);
	Button_Back->OnClicked.AddUniqueDynamic(this, &USettingsMenu::OnBackPressed);

	Text_Option_A->SetText(FText::FromString("Abilities"));
	Text_Option_B->SetText(FText::FromString("Threshold"));
	Text_Back->SetText(FText::FromString("Back"));

	//Checkbox
	FSlateBrush Checkbox_Normal_Unchecked;
	FSlateBrush Checkbox_Normal_Checked;
	FSlateBrush Checkbox_Hovered_Unchecked;
	FSlateBrush Checkbox_Hovered_Checked;
	FSlateBrush Checkbox_Pressed_Unchecked;
	FSlateBrush Checkbox_Pressed_Checked;

	Checkbox_Normal_Unchecked.DrawAs = ESlateBrushDrawType::Image;
	Checkbox_Normal_Unchecked.SetResourceObject(TextureObject);
	Checkbox_Normal_Checked.DrawAs = ESlateBrushDrawType::Image;
	Checkbox_Normal_Checked.TintColor = FLinearColor(1, 0, 0, 1);
	Checkbox_Normal_Checked.SetResourceObject(TextureObject);
	Checkbox_Hovered_Unchecked.DrawAs = ESlateBrushDrawType::Image;
	Checkbox_Hovered_Unchecked.TintColor = FLinearColor(0.5, 0.5, 0.5, 0.5);
	Checkbox_Hovered_Unchecked.SetResourceObject(TextureObject);
	Checkbox_Hovered_Checked.DrawAs = ESlateBrushDrawType::Image;
	Checkbox_Hovered_Checked.TintColor = FLinearColor(1, 0, 0, 0.5);
	Checkbox_Hovered_Checked.SetResourceObject(TextureObject);
	Checkbox_Pressed_Unchecked.DrawAs = ESlateBrushDrawType::Image;
	Checkbox_Pressed_Unchecked.TintColor = FLinearColor(0.1, 1, 0.1, 0.1);
	Checkbox_Pressed_Unchecked.SetResourceObject(TextureObject);
	Checkbox_Pressed_Checked.DrawAs = ESlateBrushDrawType::Image;
	Checkbox_Pressed_Checked.TintColor = FLinearColor(1, 0.1, 0.1, 0.1);
	Checkbox_Pressed_Checked.SetResourceObject(TextureObject);

	OptionA_CheckBox->WidgetStyle.SetUncheckedImage(Checkbox_Normal_Unchecked);
	OptionA_CheckBox->WidgetStyle.SetUncheckedHoveredImage(Checkbox_Hovered_Unchecked);
	OptionA_CheckBox->WidgetStyle.SetUncheckedPressedImage(Checkbox_Pressed_Unchecked);
	OptionA_CheckBox->WidgetStyle.SetCheckedImage(Checkbox_Normal_Checked);
	OptionA_CheckBox->WidgetStyle.SetCheckedHoveredImage(Checkbox_Hovered_Unchecked);
	OptionA_CheckBox->WidgetStyle.SetCheckedPressedImage(Checkbox_Pressed_Checked);
	

	//Slider
	FSlateBrush Slider_Normal;
	FSlateBrush Slider_Hovered;
	FSlateBrush Thumb_Normal;
	FSlateBrush Thumb_Hovered;

	Slider_Normal.SetResourceObject(TextureObject);
	Slider_Hovered.TintColor = FLinearColor(1, 1, 1, 0.5);
	Slider_Hovered.SetResourceObject(TextureObject);
	Thumb_Normal.SetResourceObject(TextureObject);
	Thumb_Hovered.TintColor = FLinearColor(1, 1, 1, 0.5);
	Thumb_Hovered.SetResourceObject(TextureObject);


	OptionB_Slider->WidgetStyle.SetNormalBarImage(Slider_Normal);
	OptionB_Slider->WidgetStyle.SetHoveredBarImage(Slider_Hovered);
	OptionB_Slider->WidgetStyle.SetNormalThumbImage(Thumb_Normal);
	OptionB_Slider->WidgetStyle.SetHoveredThumbImage(Thumb_Hovered);
	OptionB_Slider->WidgetStyle.SetBarThickness(10);
	OptionB_Slider->SetMinValue(0);
	OptionB_Slider->MaxValue = 100;
	

	//Back Button
	Button_Back->WidgetStyle.Normal.DrawAs = ESlateBrushDrawType::Image;
	Button_Back->WidgetStyle.Normal.SetResourceObject(TextureObject);
	Button_Back->WidgetStyle.Hovered.DrawAs = ESlateBrushDrawType::Image;
	Button_Back->WidgetStyle.Hovered.SetResourceObject(TextureObject);
	Button_Back->WidgetStyle.Pressed.DrawAs = ESlateBrushDrawType::Image;
	Button_Back->WidgetStyle.Pressed.SetResourceObject(TextureObject);

	PlayAnimation(SpinnerAnimation, 0.0f, 0, EUMGSequencePlayMode::PingPong, 0.5f);
}

void USettingsMenu::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)    
{																				   
	Super::NativeTick(MyGeometry, InDeltaTime);									 // This is where UUserWidget::TickActionsAndAnimation() is executed
}

void USettingsMenu::OnCheckStateChanged(bool bIsChecked)
{
	UMyGameInstance* GI = Cast<UMyGameInstance>(GetGameInstance());
	
	if (OptionA_CheckBox->IsChecked())
	{
		if (!GI->bAbilities)
		{
			GI->bAbilities = true;
		}
	}
	else
	{
		if (GI->bAbilities)
		{
			GI->bAbilities = false;
		}
	}
	
}

void USettingsMenu::OnValueChanged(float InValue)
{
	UMyGameInstance* GI = Cast<UMyGameInstance>(GetGameInstance());

	GI->Thershold = OptionB_Slider->GetValue();
}

void USettingsMenu::OnBackPressed()
{
	HideWidget();
	GetHUDClass()->SpawnMainMenu();
}









