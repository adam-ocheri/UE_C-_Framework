// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "CustomUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class LEARN_UE_CPP_101_API UCustomUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	

	UCustomUserWidget(const FObjectInitializer& ObjectInitializer); // if overriding a constructor from UUserWidget, remember the constructor isn't an empty no args constructor - it needs a const FObjectInitializer Object

	//virtual TSharedRef< SWidget > RebuildWidget();

	FVector2D ScreenResolution;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* MyText;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* Quit;
	
	virtual void NativeOnInitialized() override;

	virtual void NativeConstruct();

	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaSeconds) override;

	
};

