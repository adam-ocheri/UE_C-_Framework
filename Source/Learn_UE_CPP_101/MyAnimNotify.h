// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"		
#include "MyAnimNotify.generated.h"

// AnimNotify and AnimNotifyState are siblings
///
//This is good for cases when in parallel to the onset of the animation, we need to execute some kind of "fire and forget" functionality.
UCLASS()
class LEARN_UE_CPP_101_API UMyAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

	virtual	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
	
};
