// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyEnum.h"
#include "Interact.h"
#include "Engine/DataTable.h"
#include "AssetRegistry/IAssetRegistry.h"

//#include "../../../../../../../UE5_1/UnrealEngine/Engine/Source/Runtime/Core/Public/Templates/SharedPointerInternals.h"
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
class ALearn_UE_CPP_101Character : public ACharacter, public IInteract//, public TSharedFromThis<ALearn_UE_CPP_101Character>
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"), AssetRegistrySearchable)
	class USpringArmComponent* SpringArm;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"), AssetRegistrySearchable)
	class UCameraComponent* Camera;

	TSubclassOf<ALearn_UE_CPP_101Character> ChildBP;

	/*
	template< class OtherType >
	FORCEINLINE static TSharedRef< OtherType, ESPMode::ThreadSafe > SharedThis(OtherType* ThisPtr)
	{
		return StaticCastSharedRef< OtherType >(ThisPtr->AsShared());
	}*/
	//FORCEINLINE TSharedRef <ALearn_UE_CPP_101Character> SharedThis(const ALearn_UE_CPP_101Character* ThisPtr) { return MakeShareable<ALearn_UE_CPP_101Character>(ThisPtr); }
	//template<typename OtherType>
	//FORCEINLINE TSharedRef <T, ESPMode::ThreadSafe> TSharedFromThis<const ALearn_UE_CPP_101Character>::SharedThis(const OtherType* ThisPtr) {
	//	return MakeShared
	//}
	
protected:
	

	/** Register/Unregister a callback for when assets are added to the registry */
	UFUNCTION()
	void OnAssetAdded(const FAssetData& AssetData); //virtual FAssetAddedEvent&

	/** Register/Unregister a callback for when assets are removed from the registry */
	//virtual FAssetRemovedEvent& OnAssetRemoved() = 0;

	/** Register/Unregister a callback for when assets are renamed in the registry */
	//virtual FAssetRenamedEvent& OnAssetRenamed() = 0;

	/** Register/Unregister a callback for when the asset registry is done loading files */
	//virtual FFilesLoadedEvent& OnFilesLoaded() = 0;

	/** Register/Unregister a callback to update the progress of the background file load */
	//virtual FFileLoadProgressUpdatedEvent& OnFileLoadProgressUpdated() = 0;

	/** Returns true if the asset registry is currently loading files and does not yet know about all assets */
	//virtual bool IsLoadingAssets() = 0;
	
	//virtual void OnAssetAdded(const FAssetData& AssetData);

	TArray<FAssetData> ItemList;
	void LoadItems_Deferred();

public:

	template<typename T>
	T* ActOnSomething();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
	class UDataTable* MaterialDataBase;

	class USoundCue* SoundToPlay;
	UAudioComponent* AudioComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, AssetRegistrySearchable)
	class USoundCue* MusicToPlay3D;

	FString MyString = FString("Hello World! :)");
	UAnimSequence* Idle_Sequence;

	TObjectPtr<AActor> MyObjPtr;

	
	TSoftObjectPtr<UTexture2D> SPtr;
	
	TSoftObjectPtr<UTexture2D> AssetPtr;
	
	//Needed for UE Smart Pointer OBJ
	FORCEINLINE void* operator new(size_t _Size, void* _Where);
	ALearn_UE_CPP_101Character(ALearn_UE_CPP_101Character* ThisPtr);

	ALearn_UE_CPP_101Character();
	~ALearn_UE_CPP_101Character();
	//
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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AssetRegistrySearchable)
	TEnumAsByte<EWeaponState::FireState> WeaponState = EWeaponState::FireState::Auto;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, AssetRegistrySearchable)
	TEnumAsByte<EAnimThreads> AnimationThreads = EAT_Idle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, AssetRegistrySearchable)
	EWillState WillState = EWillState::Alarm_State; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAgressionMode AgressionMode = EAgressionMode::FullBerserk;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Bitmask, BitmaskEnum = "EAnimationThreads"))		//Bitmask Enum declaration - must be a UPROPERTY with meta = (Bitmask, BitmaskEnum = "EEnumerationName")
	uint8 AnimThreads = static_cast<uint8>(EAnimationThreads::Idle);										//The variable itself is a uint8, and to initialize it we perform a c++ static cast to the uint8 parent. The object we provide for the cast would be the Enumerator value 
	

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return SpringArm; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return Camera; }

	UPROPERTY(EditAnywhere)
	float Health = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, AssetRegistrySearchable)
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

	void GetMyObject(class UMyObject* Object);

	FHitResult CollisionHit;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

};

template<typename T>
FORCEINLINE T* ALearn_UE_CPP_101Character::ActOnSomething()
{
	T* OBJ = NewObject<T>(this);
	return OBJ;
}
