// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimNotifyState.h"
#include "Learn_UE_CPP_101Character.h"
#include "MyAnimInstance.h"

void UMyAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, FString("Anim Notify STATE has started"));
}

void UMyAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	

	ALearn_UE_CPP_101Character* Pawn = Cast<ALearn_UE_CPP_101Character>(MeshComp->GetOwner());
	if (Pawn)
	{
		if (Pawn->CollisionHit.bBlockingHit)
		{
			UMyAnimInstance* MyAnimInstance = Cast<UMyAnimInstance>(Pawn->GetMesh()->GetAnimInstance());
			if (MyAnimInstance)
			{
				if (MyAnimInstance->Montage_IsPlaying(MyAnimInstance->Interact_Montage))
				{
					MyAnimInstance->Montage_Pause(MyAnimInstance->Interact_Montage);
					GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, FString("Anim Notify State Is ticking AND logic is ok"));
				}
			}
		}
	}
}

void UMyAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString("Anim Notify STATE has ended"));
}
