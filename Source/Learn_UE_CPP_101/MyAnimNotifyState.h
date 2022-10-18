// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "MyAnimNotifyState.generated.h"

/*
 AnimNotifyState is more robust than it's sibling, in that it provides us with the ability to execute custom functionalities when a montage begins to play, while it plays, and
 when it ends.
 This class is more suited for cases when we need to execute rather complex behaviours, quries, or logic, for the entire lifetime of a playing animation montage.


 */
UCLASS()
class LEARN_UE_CPP_101_API UMyAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	
		
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference);
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference);
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference);
};
