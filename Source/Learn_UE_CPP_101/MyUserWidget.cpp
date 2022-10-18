// Fill out your copyright notice in the Description page of Project Settings.

//-----------------------------------------------------------------This is the MAIN MENU UserWidget-----------------------------------------------------------------\\

#include "MyUserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "SettingsMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Styling/SlateBrush.h"
#include "Styling/SlateTypes.h"

#include "Components/ComboBoxString.h"
#include "GameFramework/GameUserSettings.h"

#include "Components/WidgetSwitcher.h"
#include "Components/GridPanel.h"
#include "Components/GridSlot.h"

#include "MyInterface.h"
#include "Learn_UE_CPP_101Character.h"

//#include "MyHUD.h"
#include "MyMyPlayerController.h"
#include "Components/OverlaySlot.h"
#include "Components/Overlay.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/Button.h"
#include "Components/ButtonSlot.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

#include "MyGameInstance.h"



//#include "Blueprint/WidgetTree.h"



UMyUserWidget::UMyUserWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static  ConstructorHelpers::FObjectFinder<UTexture2D> Image(TEXT("/Game/StarterContent/Textures/T_CobbleStone_Pebble_D"));
	StartButton_Image = Image.Object;
	
	static  ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialAsset(TEXT("/Game/StarterContent/Textures/T_CobbleStone_Pebble_Mat"));
	Material = MaterialAsset.Object;
}




void UMyUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	//ComboBox
	Difficulty->AddOption(FString("1920x1080"));
	Difficulty->AddOption(FString("1600x900"));
	Difficulty->AddOption(FString("1280x1024"));
	Difficulty->SetSelectedOption("1920x1080");


	//Initialize private sub-widgets that are not Bound and exposed to BP 
	Start_Text = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
	Settings_Text = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
	Quit_Text = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());

	//Set widget brushes, styles, and values
	MyText->SetText(FText::FromString("PAWNDER"));
	MyText->Font.Size = 50;
	MyImage->SetBrushFromTexture(StartButton_Image);

	Start_Text->SetText(FText::FromString("Start Game"));
	Settings_Text->SetText(FText::FromString("Settings"));
	Quit_Text->SetText(FText::FromString("Quit"));

	//Buttom - start
	FSlateBrush ButtonNormal_Start;
	FSlateBrush ButtonHovered_Start;
	FSlateBrush ButtonPressed_Start;
	ButtonNormal_Start.DrawAs = ESlateBrushDrawType::Image;
	ButtonNormal_Start.Tiling = ESlateBrushTileType::NoTile;
	ButtonNormal_Start.SetResourceObject(Material);
	ButtonHovered_Start.DrawAs = ESlateBrushDrawType::Image;
	ButtonHovered_Start.Tiling = ESlateBrushTileType::NoTile;
	ButtonHovered_Start.TintColor = FLinearColor(0.7f, 0.5f, 1.0f);
	ButtonHovered_Start.SetResourceObject(Material);
	ButtonPressed_Start.DrawAs = ESlateBrushDrawType::Image;
	ButtonPressed_Start.Tiling = ESlateBrushTileType::NoTile;
	ButtonPressed_Start.TintColor = FLinearColor(0.2f, 1.0f, 0.3f, 1.0f);
	ButtonPressed_Start.SetResourceObject(Material);

	
	Start->WidgetStyle.SetNormal(ButtonNormal_Start);
	Start->WidgetStyle.SetHovered(ButtonHovered_Start);
	Start->WidgetStyle.SetPressed(ButtonPressed_Start);

	//button - Settings
	FSlateBrush ButtonNormal_Settings;
	FSlateBrush ButtonHovered_Settings;
	FSlateBrush ButtonPressed_Settings;
	ButtonNormal_Settings.DrawAs = ESlateBrushDrawType::Image;
	ButtonNormal_Settings.Tiling = ESlateBrushTileType::NoTile;
	ButtonNormal_Settings.SetResourceObject(Material);
	ButtonHovered_Settings.DrawAs = ESlateBrushDrawType::Image;
	ButtonHovered_Settings.Tiling = ESlateBrushTileType::NoTile;
	ButtonHovered_Settings.TintColor = FLinearColor(0.7f, 0.5f, 1.0f);
	ButtonHovered_Settings.SetResourceObject(Material);
	ButtonPressed_Settings.DrawAs = ESlateBrushDrawType::Image;
	ButtonPressed_Settings.Tiling = ESlateBrushTileType::NoTile;
	ButtonPressed_Settings.TintColor = FLinearColor(0.2f, 1.0f, 0.3f, 1.0f);
	ButtonPressed_Settings.SetResourceObject(Material);
	
	Settings->WidgetStyle.SetNormal(ButtonNormal_Settings);
	Settings->WidgetStyle.SetHovered(ButtonHovered_Settings);
	Settings->WidgetStyle.SetPressed(ButtonPressed_Settings);

	//button quit
	FSlateBrush ButtonNormal_Quit;
	FSlateBrush ButtonHovered_Quit;
	FSlateBrush ButtonPressed_Quit;
	ButtonNormal_Quit.DrawAs = ESlateBrushDrawType::Image;
	ButtonNormal_Quit.Tiling = ESlateBrushTileType::NoTile;
	ButtonNormal_Quit.SetResourceObject(Material);
	ButtonHovered_Quit.DrawAs = ESlateBrushDrawType::Image;
	ButtonHovered_Quit.Tiling = ESlateBrushTileType::NoTile;
	ButtonHovered_Quit.TintColor = FLinearColor(0.7f, 0.5f, 1.0f);
	ButtonHovered_Quit.SetResourceObject(Material);
	ButtonPressed_Quit.DrawAs = ESlateBrushDrawType::Image;
	ButtonPressed_Quit.Tiling = ESlateBrushTileType::NoTile;
	ButtonPressed_Quit.TintColor = FLinearColor(0.2f, 1.0f, 0.3f, 1.0f);
	ButtonPressed_Quit.SetResourceObject(Material);
	
	Quit->WidgetStyle.SetNormal(ButtonNormal_Quit);
	Quit->WidgetStyle.SetHovered(ButtonHovered_Quit);
	Quit->WidgetStyle.SetPressed(ButtonPressed_Quit);
	


	//Slots
	UButtonSlot* Slot_StartButtonText = Cast<UButtonSlot>(Start->AddChild(Start_Text));
	UButtonSlot* Slot_SettingsButtonText = Cast<UButtonSlot>(Settings->AddChild(Settings_Text));
	UButtonSlot* Slot_QuitButtonText = Cast<UButtonSlot>(Quit->AddChild(Quit_Text));

	UVerticalBoxSlot* Slot_00_Title = Container->AddChildToVerticalBox(MyText);
	UVerticalBoxSlot* Slot_01_StartButton = Container->AddChildToVerticalBox(Start);
	UVerticalBoxSlot* Slot_02_SettingsButton = Container->AddChildToVerticalBox(Settings);
	UVerticalBoxSlot* Slot_03_QuitButton = Container->AddChildToVerticalBox(Quit);
	
	Slot_00_Title->SetPadding(FMargin(100, 100));
	Slot_01_StartButton->SetPadding(FMargin(0, 10));
	Slot_02_SettingsButton->SetPadding(FMargin(0, 10));
	Slot_03_QuitButton->SetPadding(FMargin(0, 10));

	

	UOverlaySlot* Slot_BackgroundImage = Overlayer_01->AddChildToOverlay(MyImage);
	UOverlaySlot* Slot_Main = Overlayer_01->AddChildToOverlay(Container);
	
	Slot_Main->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
	Slot_Main->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);




	

}

void UMyUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	
	
	//ComboBox start
	Difficulty->OnOpening.AddUniqueDynamic(this, &UMyUserWidget::HandleOpening);
	Difficulty->OnSelectionChanged.AddUniqueDynamic(this, &UMyUserWidget::HandleSelectionChanged);
	//ComboBox end



	//WidgetSwitcher start

	

	Text_B1->SetMinDesiredWidth(100.0f);
	Text_B1->SetJustification(ETextJustify::Center);
	Text_B2->SetMinDesiredWidth(100.0f);
	Text_B2->SetJustification(ETextJustify::Center);
	Text_B3->SetMinDesiredWidth(100.0f);
	Text_B3->SetJustification(ETextJustify::Center);

	Button_1->AddChild(Text_B1);
	Button_2->AddChild(Text_B2);
	Button_3->AddChild(Text_B3);

	UGridSlot* B1 = Tabs_Panel->AddChildToGrid(Button_1, 0, 0);
	UGridSlot* B2 = Tabs_Panel->AddChildToGrid(Button_2, 0, 1);
	UGridSlot* B3 = Tabs_Panel->AddChildToGrid(Button_3, 0, 2);
	Tabs_Panel->AddChildToGrid(Switcher, 1, 4);
	
	B1->SetNudge(FVector2D(400, 0));
	B2->SetNudge(FVector2D(405, 0));
	B3->SetNudge(FVector2D(410, 0));
	
	UOverlaySlot* Overlay_Slot_GridPanel = Overlayer_01->AddChildToOverlay(Tabs_Panel);
	Overlay_Slot_GridPanel->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Right);
	Overlay_Slot_GridPanel->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);

	Button_1->OnClicked.AddUniqueDynamic(this, &UMyUserWidget::OpenTab1);
	Button_2->OnClicked.AddUniqueDynamic(this, &UMyUserWidget::OpenTab2);
	Button_3->OnClicked.AddUniqueDynamic(this, &UMyUserWidget::OpenTab3);
	//WidgetSwitcher end





	MyImage->SetDesiredSizeOverride(GetHUDClass()->ScreenResolution);
	
	
	Start->OnClicked.AddUniqueDynamic(this, &UMyUserWidget::StartGame);
	Settings->OnClicked.AddUniqueDynamic(this, &UMyUserWidget::SettingsMenu);
	Quit->OnClicked.AddUniqueDynamic(this, &UMyUserWidget::QuitGame);
	
	
	PlayAnimation(NewAnimation, 0.0f, 0, EUMGSequencePlayMode::PingPong, 0.5f);
}

void UMyUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	//UUserWidget::TickActionsAndAnimation(InDeltaTime);
}



void UMyUserWidget::StartGame()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Orange, TEXT("Button is Working!"));
	HideWidget();
	HUDClass->SpawnScreenHUDWidget_StartGame();
	UMyGameInstance* GI = Cast<UMyGameInstance>(GetGameInstance());
	GI->DoSomething();
	
	ALearn_UE_CPP_101Character* MyChar = Cast<ALearn_UE_CPP_101Character>(UGameplayStatics::GetPlayerCharacter(this, 0));
	//Execute_CommunicateBP(MyChar);
	//Communicate();
	//IMyInterface::Communicate();
	//MyChar->Communicate();
	
	bool bDoesImplementInterface = MyChar->GetClass()->ImplementsInterface(UMyInterface::StaticClass());
	bool bDoesImplementInterface2 = this->Implements<UMyInterface>();
	IMyInterface* MI = Cast<IMyInterface>(this);
	
	//IsChildOf
	
	if (MyChar->GetClass()->IsChildOf(UMyInterface::StaticClass()))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Orange, TEXT("this object DOES Implement Interface!!!"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Orange, TEXT("this object just DOES NOT Implement the Interface!!!"));
	}
	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Orange, FString::Printf(TEXT("First Implement Interface Bool is: %n"), bDoesImplementInterface));
	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Orange, FString::Printf(TEXT("First Implement Interface Bool is: %n"), bDoesImplementInterface2));
}

void UMyUserWidget::SettingsMenu()
{
	HideWidget();
	GetHUDClass()->SpawnSettingsMenu();
}

void UMyUserWidget::QuitGame()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

void UMyUserWidget::HandleOpening()
{
	//Difficulty->RefreshOptions();
	// do something? play audio?
}


void UMyUserWidget::HandleSelectionChanged(FString Item, ESelectInfo::Type Type)
{
	if (Difficulty->GetSelectedIndex() == 0)
	{
		GetOwningPlayer()->ConsoleCommand(FString("r.SetRes 1920x1080w|r.ScreenPercentage 200"));
	}
	else if (Difficulty->GetSelectedIndex() == 1)
	{
		GetOwningPlayer()->ConsoleCommand(FString("r.SetRes 1600x900w|r.ScreenPercentage 100"));
	}
	else if (Difficulty->GetSelectedIndex() == 2)
	{
		GetOwningPlayer()->ConsoleCommand(FString("r.SetRes 1280x1024w|r.ScreenPercentage 25"));
	}


	//GetOwningPlayer()->ConsoleCommand(FString("r.SetRes 640x480f"));

	//AMyMyPlayerController* PC = Cast<AMyMyPlayerController>(GetOwningPlayer());
	//PC->ExecuteConsoleCommand(FString("stat fps"));
	/*
	FIntPoint IP = FIntPoint(640, 480);
	GEngine->GetGameUserSettings()->SetScreenResolution(IP);
	*/
	/*
	AMyMyPlayerController* PC = Cast<AMyMyPlayerController>(GetOwningPlayer());
	FString N = FString("r.SetRes ");
	FString M = FString("r.ScreenPercentage ");
	FString Command = M + Item;
	PC->ConsoleCommand(*Command);
	//GetWorld()->Exec(GetWorld(), *Command);
	//GEngine->Exec(GetWorld(), *Command);
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Orange, *Command);
	*/
}

void UMyUserWidget::OpenTab1()
{
	Switcher->SetActiveWidgetIndex(0);
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Orange, TEXT("Button1 is Working!"));
}

void UMyUserWidget::OpenTab2()
{
	Switcher->SetActiveWidgetIndex(1);
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Orange, TEXT("Button2 is Working!"));
}

void UMyUserWidget::OpenTab3()
{
	Switcher->SetActiveWidgetIndex(2);
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Orange, TEXT("Button3 is Working!"));
}