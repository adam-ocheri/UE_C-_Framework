// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterUserWidget.h"


UMasterUserWidget::UMasterUserWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ScreenResolution = FVector2D(0, 0);
}




void UMasterUserWidget::NativeOnInitialized()
{
	
	
	HUDClass = Cast<AMyHUD>(GetOwningPlayer()->GetHUD());

	ScreenResolution = HUDClass->ScreenResolution;
	
	Super::NativeOnInitialized();
	{
		float X = ScreenResolution.X;
		float Y = ScreenResolution.Y;
		FString ClassName = GetName();

		if (this->GetClass() == UMasterUserWidget::StaticClass())
		{
			GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red, FString::Printf(TEXT("Screen Resolution through the %s is: %f on %f"), *ClassName, X, Y));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Blue, FString::Printf(TEXT("Screen Resolution through the %s is: %f on %f"), *ClassName, X, Y));
		}


		if (this->GetClass() == UMasterUserWidget::StaticClass())
		{
			GEngine->AddOnScreenDebugMessage(-1, 12.0f, FColor::Turquoise, FString("Master Widget - Is Loaded!!!!!!!!!!!!!!!!!!!!!!!!!!!!!@#@@#@##"));
		}
		else
		{
			ClassName = GetName();
			GEngine->AddOnScreenDebugMessage(-1, 12.0f, FColor::Orange, FString::Printf(TEXT("--------Class: %s - is now LOADED--------"), *ClassName));
		}
	}
	
}

void UMasterUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red, FString::Printf(TEXT("GAME STARTED - THROUGH THE MASTER WIDGET")));
}

void UMasterUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) 
{
	/*
	
	{

		FString ClassName = GetName();
		if (this->GetClass() == UMasterUserWidget::StaticClass())
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, FString::Printf(TEXT("HEY! Ticking through the %s Class"), *ClassName));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Blue, FString::Printf(TEXT("HEY! Ticking through the %s Class"), *ClassName));
		}
	}
	*/
	Super::NativeTick(MyGeometry, InDeltaTime);
}

FVector2D UMasterUserWidget::GetCurrentScreenResolution() const
{
	return ScreenResolution;
}

AMyHUD* UMasterUserWidget::GetHUDClass() const
{
	return HUDClass;
}

void UMasterUserWidget::ShowWidget()
{
	this->SetVisibility(ESlateVisibility::Visible);
	FInputModeUIOnly InputMode;
	GetOwningPlayer()->bShowMouseCursor = true;
	InputMode.SetWidgetToFocus(this->TakeWidget());
	GetOwningPlayer()->SetInputMode(InputMode);

}

void UMasterUserWidget::HideWidget()
{
	this->SetVisibility(ESlateVisibility::Hidden);
	FInputModeGameOnly InputMode;
	GetOwningPlayer()->bShowMouseCursor = false;
	GetOwningPlayer()->SetInputMode(InputMode);
	//find a way to destroy widget, remove from memory, or alternatively:
																		//make widgets static, and truly hide and show them when needed
	
}

