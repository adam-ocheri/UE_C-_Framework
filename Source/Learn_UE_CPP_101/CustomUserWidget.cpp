// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomUserWidget.h"
#include "Widgets/Layout/Anchors.h"

#include "Components/Button.h"

#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/WidgetTree.h"

/*

There exists some form of hierarchy between the various classes in regards to "ownership" of widget elements over other widget elements.
As we have seen, any sub-widgets would be contained within an overlay.
The overlay is then contained within the RootWidget, which is derived from PanelWidgets.
The RootWidget is contained within our UserWidget class.
Lastly, the WidgetTree is used as a manger, an object handler and constructor which is responsible for the creation of all sub-widgets and core widgets.

WidgetTree
	ThisUUserWidget
		   |->RootWidget
				|->Overlay
					|->SubWidgets
						|->Sub-SubWidgets

*/

UCustomUserWidget::UCustomUserWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
	
}

	
/*
TSharedRef<SWidget> UCustomUserWidget::RebuildWidget()
{
	//A child of the UWidget "master" base class, UPanelWidget is the base class for all UMG panel widgets. Panel widgets allow for the laying-out of a collection of child widgets.
	//any UI UObjects we have will need to be passed as a child widget to a UPanelWidget, in order for them to be able to displayed and layed-out on the screen.
	//A PanelWidget can be set to allow only one child, or to allow multiple childs, via a boolean property it owns, "bCanHaveMultipleChildren".
	//So we need to perform a cast to the UPanelWidget, and feed it with the Root widget of our custom c++ UserWidget class, so that it could be passed into the WidgetTree for construction.
	UPanelWidget* ThisRootWGT = Cast<UPanelWidget>(GetRootWidget());

	//The widget tree manages the collection of widgets in a blueprint widget.
	ThisRootWGT = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), TEXT("WidgetRoot!"));																					//DELETE

	//After the CanvasPanel is constructed, we'll need to set it as the root widget again, via the WidgetTree.
	WidgetTree->RootWidget = ThisRootWGT;																																						//DELETE





	//Validation_______________________________________________________________________________________________________________________________
	if (!ThisRootWGT)
	{
		ThisRootWGT = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), TEXT("WidgetRoot!"));

		//UCanvasPanelSlot allows us to modify the 'Slot' global parameters of the widget, such as the Anchor and Margin.
		UCanvasPanelSlot* RootWidgetSlot = Cast<UCanvasPanelSlot>(ThisRootWGT->Slot);

		if (RootWidgetSlot)
		{
			RootWidgetSlot->SetAnchors(FAnchors(0.0f, 0.0f, 1.0f, 1.0f));
			RootWidgetSlot->SetOffsets(FMargin(0.0f, 0.0f));
		}

		WidgetTree->RootWidget = ThisRootWGT;
	}
	//Validation_______________________________________________________________________________________________________________________________


	//Create a container object for widget and initialize it to the value retreived from the Super function							**? wouldn't doing "return Super::NativeOnInitialized" suffice ??*
	TSharedRef<SWidget> RebuiltWidget = Super::RebuildWidget();

	// Construct class members: any sub-widget objects in our custom c++ UserWidget
	MyText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), TEXT("MyTextBlock"));																							//DELETE
	// and add these subwidget members as children of this custom UserWidget
	ThisRootWGT->AddChild(MyText);																																								//DELETE


	//Validation_______________________________________________________________________________________________________________________________
	if (ThisRootWGT && WidgetTree)
	{
		MyText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), TEXT("BOX OF TEXT"));

		ThisRootWGT->AddChild(MyText);

		MyText->SetText(FText::FromString("WIDGET IN PURE C++!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"));

		UCanvasPanelSlot* Slot_01 = Cast<UCanvasPanelSlot>(MyText->Slot);

		if (Slot_01)
		{
			Slot_01->SetAutoSize(true);
		}
	}
	//Validation_______________________________________________________________________________________________________________________________


	//With all of our UI elements added to a newly constructed CanvasPanel, we return and pass on this widget for a rebuild. 		**? wouldn't doing "return Super::NativeOnInitialized" suffice ??*
	return RebuiltWidget;																		
}

*/

void UCustomUserWidget::NativeOnInitialized()				// Preconstruct, construction script
{
	Super::NativeOnInitialized();

	ScreenResolution = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());

	MyText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), TEXT("MyTextBlock"));																							
	Quit = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass(), TEXT("Quit Button"));
	
	UOverlay* MonOverlay = WidgetTree->ConstructWidget<UOverlay>(UOverlay::StaticClass(), TEXT("Overlayer"));				
	//MonOverlay->SetRenderTransformPivot(FVector2D(0.5f, 0.5f));
	//MyText->SetRenderTranslation(FVector2D(ScreenResolution.X / 2, 0));
	
	

	// Two ways of creating slots/+adding widgets to slots:
	
	//MonOverlay->AddChildToOverlay(MyText);
	//UOverlaySlot* Slot_01 = Cast<UOverlaySlot>(MyText->Slot);
	UOverlaySlot* Slot_01 = MonOverlay->AddChildToOverlay(MyText);
	UOverlaySlot* Slot_02 = MonOverlay->AddChildToOverlay(Quit);
	if (Slot_01 && Slot_02)
	{
		Slot_01->SetPadding(FMargin(0, 0,1,1));
		//Slot_01->SetPadding(FMargin(0, 1,0,0));
		//Slot_01->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
		//Slot_02->SetPadding(FMargin(0, ScreenResolution.Y));
		GEngine->AddOnScreenDebugMessage(-1, 6.0f, FColor::Green, TEXT("Slot Is VALID!!!!!"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 6.0f, FColor::Red, TEXT("Slot is INVALID!!!!!!!!!"));
	}
	



	UPanelWidget* ThisRootWGT = Cast<UPanelWidget>(GetRootWidget());
	
	if (!ThisRootWGT)
	{
		ThisRootWGT = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), TEXT("WidgetRoot!"));
	}

	if (ThisRootWGT)
	{
		ThisRootWGT->AddChild(MonOverlay);
		UCanvasPanelSlot* Slot_00 = Cast<UCanvasPanelSlot>(MonOverlay->Slot);
		//Slot_00->SetOffsets(FMargin(ScreenResolution.X / 2, ScreenResolution.Y / 2,));
		FAnchors OA(0, 0, 1, 0);
		Slot_00->SetAnchors(OA);
		WidgetTree->RootWidget = ThisRootWGT;
	}
	


	//

	

	
	
	
	
	
	
	



	if (MyText != nullptr)
	{
		MyText->SetText(FText::FromString("C++"));
		//Text->SetRenderScale(FVector2D(10,10));
	}
	
}




void UCustomUserWidget::NativeConstruct()					//Construct, begin play
{
	Super::NativeConstruct();

	if (MyText != nullptr)
	{
		//MyText->SetText(FText::FromString("THIS IS IT"));
	}

	
	

}

void UCustomUserWidget::NativeTick(const FGeometry& MyGeometry, float DeltaSeconds)
{
	Super::NativeTick(MyGeometry, DeltaSeconds);

	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("UUserWidget Tick is ALIVE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"));
}
