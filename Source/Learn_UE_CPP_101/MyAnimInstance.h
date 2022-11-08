// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimInstanceProxy.h"
#include "Learn_UE_CPP_101Character.h"
#include "MyCharacterMovementComponent.h"

#include "MyAnimInstance.generated.h"


/*

An advanced setup of an AnimInstance class would include a struct of type FAnimInstanceProxy.
This struct serves as as mediator between the AnimInstance class and the derived Animation BP that actually contains all of our animations and state machines.
Uttilizing this struct to update the character properties that need to be updated on tick can help performance, as well is it allows us to uttilize animation Threads, for very
advanced use cases.

*/


USTRUCT(BlueprintType)
struct FMyAnimInstanceProxy : public FAnimInstanceProxy
{
	GENERATED_BODY()

	FMyAnimInstanceProxy() : FAnimInstanceProxy() {}
	
	FMyAnimInstanceProxy(UAnimInstance* InAnimInstance) : FAnimInstanceProxy()
	{
		
		UE_LOG(LogTemp, Warning, TEXT("FAnimProxy CONSTRUCTOR has initialized!"));
		
		
	}
	
	virtual void Initialize (UAnimInstance* InAnimInstance)
	{
		Super::Initialize(InAnimInstance);

		
		MyAnimInstance = static_cast<TSubclassOf<UMyAnimInstance>>(InAnimInstance->GetClass());
		
		if (MyAnimInstance)
		{
			MyPawnOwner = Cast<ALearn_UE_CPP_101Character>(InAnimInstance->TryGetPawnOwner());
		}
		
		

		if (MyPawnOwner)
		{
			GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Purple, FString::Printf(TEXT("FAnimProxy Character Initialized, it IS: %s"), *MyPawnOwner->GetName()));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Purple, FString("PLAYER INVALID THROUGH FANIMPROXY"));
		}

		GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Purple, FString::Printf(TEXT("MY FAnimProxy Initialized, and Anim Instance IS: %s"), *MyAnimInstance->GetName()));
		
	}
	
	virtual void Update(float DeltaSeconds)
	{
		if (MyPawnOwner)
		{
			bIsInAir = MyPawnOwner->GetCharacterMovement()->IsFalling();
			Speed = MyPawnOwner->GetCharacterMovement()->GetLastUpdateVelocity().Size();
			Velocity = MyPawnOwner->GetCharacterMovement()->GetLastUpdateVelocity();

			
			GEngine->AddOnScreenDebugMessage(-1, DeltaSeconds, FColor::Purple, FString("FAnimProxy IS TICKING!"));
		}
		
	}
//public:

	ALearn_UE_CPP_101Character* MyPawnOwner;

	

	class TSubclassOf<UAnimInstance> MyAnimInstance;

	UPROPERTY(Transient, BlueprintReadWrite, EditAnywhere)
		float Speed;

	UPROPERTY(Transient, BlueprintReadWrite, EditAnywhere)
		bool bIsInAir;

	UPROPERTY(Transient, BlueprintReadWrite, EditAnywhere)
		FVector Velocity;
};


/**
 * 
 */
UCLASS(transient, BlueprintType, Blueprintable)
class LEARN_UE_CPP_101_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UMyAnimInstance(const FObjectInitializer& ObjectInitializer);

	virtual void NativeInitializeAnimation();

	virtual void NativeUpdateAnimation(float DeltaSeconds);

	virtual void NativeBeginPlay();

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsInAir;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector Velocity;

	class ALearn_UE_CPP_101Character* MyPawnOwner;

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
		FORCEINLINE ALearn_UE_CPP_101Character* GetMyPawnOwner() const { return MyPawnOwner; }

	friend struct FMyAnimInstanceProxy;
	
	UPROPERTY(Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		FMyAnimInstanceProxy MyProxy {this};
	
	virtual FAnimInstanceProxy* CreateAnimInstanceProxy() override
	{
		return &MyProxy;
	}
	
	virtual void DestroyAnimInstanceProxy(FAnimInstanceProxy* InProxy) override
	{

	}
	

	


	void PlayMyMontage();
	UAnimMontage* Interact_Montage;
	

	

	UAnimSequence* Idle_Sequence;
	UAnimSequence* Walk_Sequence;
	
	bool bIdle = true;
	bool bWalking = false;
	
public:

	
		
};
