// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyHUD.h"
#include "Blueprint/WidgetTree.h"
#include "MasterUserWidget.generated.h"

/*
UMG Conclusions:
	-Hybrid approach wins
	-Should include UMG SlateCore and Slate modules in build.cs file to avoid having to include a lot of headers 
	-
	-Game will need to run as standalone game to fully visulize changes for grphical settings


*/

/**
 * 
 */
UCLASS()
class LEARN_UE_CPP_101_API UMasterUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	
	void ShowWidget();
	void HideWidget();

protected:
	UMasterUserWidget(const FObjectInitializer& ObjectInitializer);
	//~UMasterUserWidget();
	virtual ~UMasterUserWidget() = default;
	virtual void NativeOnInitialized();
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	
	FVector2D GetCurrentScreenResolution() const;
	FVector2D ScreenResolution;
	class AMyHUD* HUDClass;
	AMyHUD* GetHUDClass() const;
	
	
};

/*
	A Master Widget is a very important advocate of scalability for our flexible UI system.
	It is where we define the most rudimentary behaviours and functionalities that all child widgets in the project should inherit and benefit from.

	The MasterWidget is a C++ only widget, that only needs to be created as an object as soon as the game start (Spawned at AMyHUD::BeginPlay).
	Since this widget is simply a functional class that does not need any visual elements, it is not added to the Viewport.
	It is actually not essential that we instantiate an object of the MasterWidget class in order for the child widgets to inherit it's functionality, but it could serve as an
	additional layer of support, so we can design and use it to execute global functions on all living child widgets simultaneously.

	For our example, we would simply store a reference to out HUD class, retrieve from it the current screen resolution, and set up simple functions that show or hide a widget.
	By doing this in the master widget, these properties and functionality will all be easily accessible to any widget class derived from this Master class.

*/
