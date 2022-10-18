// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimNotify.h"

void UMyAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) 
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Purple, FString("MY ANIM NOTIFY FIRED!"));
}

