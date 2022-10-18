// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenWidgetHUD.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/CanvasPanel.h"
#include "Components/Overlay.h"
#include "Components/GridPanel.h"
#include "Components/SizeBox.h"
#include "Components/OverlaySlot.h"
#include "Components/GridSlot.h"
#include "Components/SizeBoxSlot.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

//#include "Styling/SlateBrush.h"
//#include "Styling/SlateTypes.h"




UScreenWidgetHUD::UScreenWidgetHUD(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UTexture2D>Background_TextureAsset(TEXT("/Game/VA")); 
	Background_TextureObject = Background_TextureAsset.Object;

	static ConstructorHelpers::FObjectFinder<UTexture2D>BarEmpty_TextureAsset(TEXT("/Game/Gauge_01_Main"));
	BarEmpty_TextureObject = BarEmpty_TextureAsset.Object;

	static ConstructorHelpers::FObjectFinder<UTexture2D>BarFull_TextureAsset(TEXT("/Game/Gauge_01_Combo"));
	BarFull_TextureObject = BarFull_TextureAsset.Object;
}

void UScreenWidgetHUD::NativeOnInitialized()
{
	
	Super::NativeOnInitialized();

	//Construct c++ widget components
	Overlayer = WidgetTree->ConstructWidget<UOverlay>(UOverlay::StaticClass());
	BackPanel = WidgetTree->ConstructWidget<UGridPanel>(UGridPanel::StaticClass());
	HealthPanel = WidgetTree->ConstructWidget<UGridPanel>(UGridPanel::StaticClass());
	HealthBar = WidgetTree->ConstructWidget<UProgressBar>(UProgressBar::StaticClass());
	HealthBar_R = WidgetTree->ConstructWidget<USizeBox>(USizeBox::StaticClass());
	Health_Text = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
	Backdrop = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass());
	
	HealthBar->SetPercent(0.45f);
	Health_Text->Font.Size = 32;
	Health_Text->SetText(FText::FromString("HEALTH"));
	

	//ProgressBar styling
	FSlateBrush Empty;
	FSlateBrush Full;

	Empty.DrawAs = ESlateBrushDrawType::Image;
	Empty.SetResourceObject(BarEmpty_TextureObject);
	Full.DrawAs = ESlateBrushDrawType::Image;
	Full.SetResourceObject(BarFull_TextureObject);

	HealthBar->WidgetStyle.SetBackgroundImage(Empty);
	HealthBar->WidgetStyle.SetFillImage(Full);
 
	//SizeBox
	HealthBar_R->bOverride_WidthOverride = true;
	HealthBar_R->bOverride_HeightOverride = true;
	HealthBar_R->WidthOverride = 400.0f;				//Should not use power of 2 AND/OR equal height and width textures. its a waste of TRANSPARENT pixels for images used in UI.
	HealthBar_R->HeightOverride = 100.0f;
	
	HealthBar_R->AddChild(HealthBar);
	
	
	
	
	
	//Slots hierarchies setup
	UGridSlot* Slot_Backdrop = BackPanel->AddChildToGrid(Backdrop);
	UGridSlot* Slot_Text = HealthPanel->AddChildToGrid(Health_Text, 0);
	UGridSlot* Slot_HealthBar = HealthPanel->AddChildToGrid(HealthBar_R, 1);

	UOverlaySlot* Slot_BackPanel = Overlayer->AddChildToOverlay(BackPanel);
	UOverlaySlot* Slot_HealthPanel = Overlayer->AddChildToOverlay(HealthPanel); //HealthBar
	
	Slot_Text->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
	Slot_HealthPanel->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
	Slot_HealthPanel->SetPadding(FMargin(ScreenResolution.X- ScreenResolution.X/2.5, ScreenResolution.Y - ScreenResolution.Y/3.5,0,0)); //
	
	//Root
	UCanvasPanel* RootWGT = Cast<UCanvasPanel>(GetRootWidget());

	if (!RootWGT)		//This condition is what would execute in the case of a c++ only widget - see page
	{
		RootWGT = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass());
		UPanelSlot* Slot_Main = RootWGT->AddChild(Overlayer);
		WidgetTree->RootWidget = RootWGT;
	}
	else				//This will not execute in a c++ only widget - only in derived BP wwidgets - see page
	{
		RootWGT->AddChild(Overlayer);
		WidgetTree->RootWidget = RootWGT;
		GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Orange, TEXT("ProgressBar is Working!"));
	}
}

void UScreenWidgetHUD::NativeConstruct()
{
	Super::NativeConstruct();

	Backdrop->SetDesiredSizeOverride(ScreenResolution);
	Backdrop->SetBrushFromTexture(Background_TextureObject);
	
	
}



/*


#include "ScreenWidgetHUD.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Components/GridPanel.h"
#include "Components/GridSlot.h"
#include "Components/VerticalBox.h"
#include "Components/SizeBox.h"
#include "Components/SizeBoxSlot.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/ProgressBar.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Styling/SlateBrush.h"
#include "Styling/SlateTypes.h"
#include "UObject/ConstructorHelpers.h"




UScreenWidgetHUD::UScreenWidgetHUD(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UTexture2D>Background_TextureAsset(TEXT("/Game/VA"));
	Background_TextureObject = Background_TextureAsset.Object;

	static ConstructorHelpers::FObjectFinder<UTexture2D>BarEmpty_TextureAsset(TEXT("/Game/Gauge_01_Main"));
	BarEmpty_TextureObject = BarEmpty_TextureAsset.Object;

	static ConstructorHelpers::FObjectFinder<UTexture2D>BarFull_TextureAsset(TEXT("/Game/Gauge_01_Combo"));
	BarFull_TextureObject = BarFull_TextureAsset.Object;
}

void UScreenWidgetHUD::NativeOnInitialized()
{

	Super::NativeOnInitialized();
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, FString("!!!!!!!!Player HUD Screen Widget Is LOADED!!!!!!!!"));
	OverPanel = WidgetTree->ConstructWidget<UGridPanel>(UGridPanel::StaticClass());
	HealthPanel = WidgetTree->ConstructWidget<UGridPanel>(UGridPanel::StaticClass());
	Overlayer = WidgetTree->ConstructWidget<UOverlay>(UOverlay::StaticClass());
	Container = WidgetTree->ConstructWidget<UVerticalBox>(UVerticalBox::StaticClass());
	HealthBar_R = WidgetTree->ConstructWidget<USizeBox>(USizeBox::StaticClass());
	Backdrop = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass());
	//HealthText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
	HealthBar = WidgetTree->ConstructWidget<UProgressBar>(UProgressBar::StaticClass());
	//HealthText->SetText(FText::FromString("HEALTH"));
	//HealthText->Font.Size = 32;
	HealthBar->SetPercent(0.45f);
	Backdrop->SetBrushFromTexture(Background_TextureObject);


	FSlateBrush EBB;
	FSlateBrush FBB;
	EBB.DrawAs = ESlateBrushDrawType::Image;
	EBB.SetResourceObject(BarEmpty_TextureObject);
	EBB.SetImageSize(FVector2D(1500, 700));
	FBB.DrawAs = ESlateBrushDrawType::Image;
	FBB.SetResourceObject(BarFull_TextureObject);
	FBB.SetImageSize(FVector2D(1500, 700));
	HealthBar->WidgetStyle.SetBackgroundImage(EBB);
	HealthBar->WidgetStyle.SetFillImage(FBB);



HealthBar_R->AddChild(HealthBar);

HealthBar_R->bOverride_WidthOverride = true;
HealthBar_R->bOverride_HeightOverride = true;
HealthBar_R->WidthOverride = 400.0f;				//Should not use power of 2 AND/OR equal height and width textures. its a waste of TRANSPARENT pixels for images used in UI.
HealthBar_R->HeightOverride = 100.0f;



UGridSlot* Slot_Back = OverPanel->AddChildToGrid(Backdrop);
UGridSlot* Slot_HB = HealthPanel->AddChildToGrid(HealthBar_R);
UOverlaySlot* Slot_00 = Overlayer->AddChildToOverlay(OverPanel);
UOverlaySlot* Slot_01 = Overlayer->AddChildToOverlay(HealthPanel); //HealthBar

Slot_01->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center); // Why isnt the alignment working? wtf?
//Slot_01->SetVerticalAlignment(EVerticalAlignment::VAlign_Bottom);
Slot_01->SetPadding(FMargin(ScreenResolution.X - ScreenResolution.X / 2.5, ScreenResolution.Y - ScreenResolution.Y / 4, 0, 0)); //

UCanvasPanel* RootWGT = Cast<UCanvasPanel>(GetRootWidget());



if (!RootWGT)
{
	RootWGT = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass());
	UPanelSlot* Slot_Panel = RootWGT->AddChild(Overlayer);
	WidgetTree->RootWidget = RootWGT;
}
else
{
	RootWGT->AddChild(Overlayer);
	WidgetTree->RootWidget = RootWGT;
	GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Orange, TEXT("ProgressBar is Working!"));
}
}

void UScreenWidgetHUD::NativeConstruct()
{
	Super::NativeConstruct();
	//Backdrop->SetBrushSize(FVector2D(1920, 1080));
	Backdrop->SetDesiredSizeOverride(FVector2D(1920, 1080));
}

*/


