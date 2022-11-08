// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyEnum.h"
#include "Interact.h"
#include "Engine/DataTable.h"
#include "Learn_UE_CPP_101Character.generated.h"

USTRUCT(BlueprintType)
struct FMyDataBase : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMaterial* Material = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Specs;
};

UCLASS(config=Game)
class ALearn_UE_CPP_101Character : public ACharacter, public IInteract
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
	class UDataTable* MaterialDataBase;

	class USoundCue* SoundToPlay;
	UAudioComponent* AudioComp;

	class USoundCue* MusicToPlay3D;


	UAnimSequence* Idle_Sequence;
	

	ALearn_UE_CPP_101Character(const FObjectInitializer& ObjectInitializer); // Constructor to initialize new component
	virtual void BeginPlay();
	virtual void Tick(float DeltaTime);

	void FireTrace();
	void InteractWithObject_Implementation() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input)
	float TurnRateGamepad;

	//UENUM
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EWeaponState::FireState> WeaponState = EWeaponState::FireState::Auto;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EAnimThreads> AnimationThreads = EAT_Idle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EWillState WillState = EWillState::Alarm_State; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAgressionMode AgressionMode = EAgressionMode::FullBerserk;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Bitmask, BitmaskEnum = "EAnimationThreads"))		//Bitmask Enum declaration - must be a UPROPERTY with meta = (Bitmask, BitmaskEnum = "EEnumerationName")
	uint8 AnimThreads = static_cast<uint8>(EAnimationThreads::Idle);										//The variable itself is a uint8, and to initialize it we perform a c++ static cast to the uint8 parent. The object we provide for the cast would be the Enumerator value 
	

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return SpringArm; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return Camera; }

	float Health = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCapsuleComponent* Collision;

	void LookUpRate(float Rate);
	void LookRightRate(float Rate);

	void MoveForward(float Value);
	void MoveRight(float Value);

	void TurnAtRateGMPD(float Rate);
	void LookUpAtRateGMPD(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	FHitResult CollisionHit;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

};

