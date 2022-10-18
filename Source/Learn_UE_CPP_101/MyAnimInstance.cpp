// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "UObject/ConstructorHelpers.h"
#include "Animation/AnimNode_StateMachine.h"
#include "Learn_UE_CPP_101Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


UMyAnimInstance::UMyAnimInstance(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Interact_M(TEXT("AnimMontage'/Game/Characters/Mannequins/Animations/Manny/HandsUp2_Montage.HandsUp2_Montage'"));
	Interact_Montage = Interact_M.Object;
	
}

void UMyAnimInstance::NativeInitializeAnimation()
{
	GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Orange, FString("Animation Class Initialized!"));

	MyPawnOwner = Cast<ALearn_UE_CPP_101Character>(TryGetPawnOwner());
	
	//CreateAnimInstanceProxy();
	//AnimInstanceProxy = &MyProxy;
	
}


void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	GEngine->AddOnScreenDebugMessage(-1, DeltaSeconds, FColor::Cyan, FString("Animation Class TICK"));

	if (MyPawnOwner)
	{
		GEngine->AddOnScreenDebugMessage(-1, DeltaSeconds, FColor::Green, FString("Pawn Owner is VALID"));
		/*
		bIsInAir = MyPawnOwner->GetCharacterMovement()->IsFalling();
		Speed = UKismetMathLibrary::VSizeXY( MyPawnOwner->GetCharacterMovement()->GetLastUpdateVelocity() );
		Velocity = MyPawnOwner->GetCharacterMovement()->GetLastUpdateVelocity();
		*/
		
		
		GEngine->AddOnScreenDebugMessage(-1, DeltaSeconds, FColor::Green, FString::Printf(TEXT("Speed is: %f"), Speed));
	}
}

void UMyAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	//GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Purple, FString("Animation Class BeginPlay!!!!!!!!!!!!!"));
	
	//MyPawnOwner->GetMesh()->PlayAnimation(Idle_Sequence, true);

	//CreateAnimInstanceProxy();
	//AnimInstanceProxy = &MyProxy;
}




void UMyAnimInstance::PlayMyMontage()
{
	

	if (Interact_Montage)
	{
		Montage_Play(Interact_Montage);								// If we want the montage to play from the start
		//Montage_JumpToSection(FName("MySec"), Interact_Montage);  //  To play from a specific section, the montage needs to first begin playing and THEN we jump to the desired section
		
		/*
		Montage_Play(Interact_Montage);
		Montage_Pause(Interact_Montage);
		Montage_Resume(Interact_Montage);
		Montage_Stop(0.35f, Interact_Montage);
		Montage_IsActive(Interact_Montage);
		Montage_IsPlaying(Interact_Montage);
		Montage_GetIsStopped(Interact_Montage);
		Montage_GetPosition(Interact_Montage);
		Montage_GetCurrentSection(Interact_Montage);
		Montage_GetNextSectionID(Interact_Montage, 0);
		Montage_GetBlendTime(Interact_Montage);
		Montage_JumpToSection(FName("Sec1"), Interact_Montage);
		Montage_JumpToSectionsEnd(FName("Sec1"), Interact_Montage);
		Montage_SetNextSection(FName("Sec1"), FName("Sec2"), Interact_Montage);
		Montage_SetPlayRate(Interact_Montage, 0.85f);
		Montage_SetPosition(Interact_Montage, 2.75f);
		
		FMontageBlendSettings BlendSettings;
		BlendSettings.Blend.BlendOption = EAlphaBlendOption::Sinusoidal;
		BlendSettings.Blend.BlendTime = 0.5f;
		Montage_PlayWithBlendSettings(Interact_Montage, BlendSettings);
		*/
		
		
		GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Purple, FString("Montage Play!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Red, FString("Montage FAIL!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"));
	}
	
}

