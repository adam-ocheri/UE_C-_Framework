// Copyright Epic Games, Inc. All Rights Reserved.

#include "Learn_UE_CPP_101Character.h"
#include "MyAnimInstance.h"
#include "GameFramework/Controller.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "MyCharacterMovementComponent.h"

#include "UObject/ConstructorHelpers.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "MyObject.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "NumStruct.h"

#include "Perception/AISense_Hearing.h"
#include "GameFramework/DamageType.h"
#include "Perception/AISense_Damage.h"
#include "MyTemplate.h"
//#include "UObject/ObjectMacros.h"
#include "BlueprintEditorSettings.h"
#include "Engine/StreamableManager.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Engine/ObjectLibrary.h"

//////////////////////////////////////////////////////////////////////////
// ALearn_UE_CPP_101Character




ALearn_UE_CPP_101Character::ALearn_UE_CPP_101Character()
{
}

ALearn_UE_CPP_101Character::~ALearn_UE_CPP_101Character()
{
	//FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	//AssetRegistryModule.Get().OnAssetAdded().RemoveAll(this);
}

void* ALearn_UE_CPP_101Character::operator new(size_t _Size, void* _Where)
{
	//return _Where;
}

ALearn_UE_CPP_101Character::ALearn_UE_CPP_101Character(ALearn_UE_CPP_101Character* ThisPtr)
{
	//SharedThis(ThisPtr);
}

void ALearn_UE_CPP_101Character::OnAssetAdded(const FAssetData& AssetData)
{
	// An asset was discovered by the asset registry.
	// This means it was either just created or recently found on disk.
	// Make sure code in this function is fast or it will slow down the gathering process.
	UE_LOG(LogTemp, Warning, TEXT("OnAssetAdded Fired!"));
}


ALearn_UE_CPP_101Character::ALearn_UE_CPP_101Character(const FObjectInitializer& ObjectInitializer) // update construcxtor in cpp file too
	: Super { ObjectInitializer.SetDefaultSubobjectClass<UMyCharacterMovementComponent>(ACharacter::CharacterMovementComponentName) }
{

	// Load the asset registry module to listen for updates
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	AssetRegistryModule.Get().OnAssetAdded().AddUObject(this, &ALearn_UE_CPP_101Character::OnAssetAdded);

	//TODO ----------------------------------------------

	TLazyObjectPtr<UCapsuleComponent> LazyObj = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Lazy Collision"));
	if (LazyObj.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Lazy Collision is Valid"));
		UE_LOG(LogTemp, Warning, TEXT("LAzy Obj: %s"), *LazyObj.Get()->GetName());
	}
	
	static ConstructorHelpers::FObjectFinder<USoundCue> SoundObject(TEXT("SoundCue'/Game/StarterContent/Audio/Explosion_Cue.Explosion_Cue'"));
	SoundToPlay = SoundObject.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable> MyData(TEXT("DataTable'/Game/Blueprints/MyDataBase.MyDataBase'"));
	
	if (MyData.Succeeded())
	{
		MaterialDataBase = MyData.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundCue> Music_3D(TEXT("SoundCue'/Game/StarterContent/Audio/Starter_Music_Cue.Starter_Music_Cue'"));
	MusicToPlay3D = Music_3D.Object;

	AudioComp = CreateDefaultSubobject<UAudioComponent>(FName("AudioComponent"));

	static ConstructorHelpers::FObjectFinder<UAnimSequence> Idle_S(TEXT("AnimSequence'/Game/Characters/Mannequins/Animations/Manny/MM_Idle.MM_Idle'"));
	Idle_Sequence = Idle_S.Object;


	PrimaryActorTick.bCanEverTick = true;
	// set our turn rate for input
	TurnRateGamepad = 50.f;

	//Skeltal mesh setup - (Can it be done using the SoftObjectPointer??)
	static ConstructorHelpers::FObjectFinder <USkeletalMesh> SKMesh(TEXT("/Game/Characters/Mannequins/Meshes/SKM_Manny.SKM_Manny"));
	static ConstructorHelpers::FClassFinder <UAnimInstance> AnimInst(TEXT("AnimBlueprint'/Game/Characters/MyAnimBP'"));
	GetMesh()->SetSkeletalMesh(SKMesh.Object);
	GetMesh()->SetAnimInstanceClass(AnimInst.Class);
	GetMesh()->AddLocalRotation(FRotator(0, -90, 0));
	GetMesh()->AddLocalOffset(FVector(0, 0, -96));

	// Create a camera boom (pulls in towards the player if there is a collision)
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	SpringArm->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	Camera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	//GetCapsuleComponent()->SetHiddenInGame(false);
	

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	
	

	//
	Collision = CreateDefaultSubobject<UCapsuleComponent>(FName("HitCollision"));
	Collision->SetupAttachment(GetMesh(), FName("hand_l"));
	Collision->InitCapsuleSize(10, 15);
	Collision->AddLocalOffset(FVector(20, 0, 0));
	Collision->SetHiddenInGame(false);
	
	//Collision Object Type
	//Collision Profile
	
	//Collision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	
	Collision->SetNotifyRigidBodyCollision(true);
	Collision->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel2); //first Custom Object Type
	Collision->SetCollisionProfileName(FName("Weapon"));
	//Collision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	//Attachment setups


	//static ConstructorHelpers::FClassFinder<ALearn_UE_CPP_101Character> Child(TEXT("Blueprint'/Game/MyLearn_UE_CPP_101Character.MyLearn_UE_CPP_101Character'"));
	//ChildBP = Child.Class;
}

void ALearn_UE_CPP_101Character::LoadItems_Deferred()
{
	for (auto const & Asset : ItemList)
	{
		const UObject* ItemData = Asset.GetAsset();
		UE_LOG(LogTemp, Warning, TEXT("DEFERRED_EXECUTION - Looping....."));
		UE_LOG(LogTemp, Warning, TEXT("DEFERRED_ Asset loaded? : %s"), *(Asset.IsAssetLoaded() ? FString("True") : FString("False")));
		UE_LOG(LogTemp, Warning, TEXT("DEFERRED_ Primary Asset ID : %s"), *Asset.GetPrimaryAssetId().ToString());
		UE_LOG(LogTemp, Warning, TEXT("DEFERRED_ Object Path : %s"), *Asset.ObjectPath.ToString());
		UE_LOG(LogTemp, Warning, TEXT("DEFERRED_ Package Path : %s"), *Asset.PackagePath.ToString());
		UE_LOG(LogTemp, Warning, TEXT("DEFERRED_ Package Name : %s"), *Asset.PackageName.ToString());
		UE_LOG(LogTemp, Warning, TEXT("________________________________________________________________________________"));
	}
}


void ALearn_UE_CPP_101Character::BeginPlay()
{
	//TODO List::
	{
		//! Learn:				Delegates | Plugins | Subsystems | 
		//! Learn:	        	AI Prediction , Team, EQS | ControlRig | Timeline Component | Spline Component | Niagara Component | Chaos Component & Force Fields | Post Processing | Level Streaming |  WorldPartition
		//! Web:				FHttp, FJson and Async operations | Replication | EOS
		//! Understand:			Static vs Dynamic Casting | TypeDefs | Template ConstExpressions | Assertions | Widgets 100% (TWeakChild ?)
		//! GetFancy:			Slate | AssetFactory |  Tie | TDecay?! | Threads |
		
	}

	Super::BeginPlay();

	// ObjectLibrary

	{
		
		UE_LOG(LogTemp, Warning, TEXT("MyObjectLibrary - try......."));

		UObjectLibrary* ObjectLibrary = UObjectLibrary::CreateLibrary(UTexture2D::StaticClass(), false, GIsEditor);
		ObjectLibrary->AddToRoot(); // DONT delete when garbage collecting
		ObjectLibrary->bRecursivePaths = true;
		ObjectLibrary->LoadAssetDataFromPath(TEXT("/Game/StarterContent/Textures"));
		
		ObjectLibrary->LoadAssetsFromAssetData(); // Loades everything, try sync and use async if cant load sync

		UE_LOG(LogTemp, Warning, TEXT("MyObjectLibrary - Name : %s"), *ObjectLibrary->GetName());

		
		// Specifically Load asynchronously
		ObjectLibrary->GetAssetDataList(ItemList);

		TArray<FSoftObjectPath> ItemsToStream;
		FStreamableManager Streamable;
		for (int32 i = 0; i < ItemList.Num(); ++i)
		{
			UE_LOG(LogTemp, Warning, TEXT("ITEMSTOSTREAM are found!"));
			ItemsToStream.AddUnique(ItemList[i].ToSoftObjectPath());
		}
		Streamable.RequestAsyncLoad(ItemsToStream, FStreamableDelegate::CreateUObject(this, &ALearn_UE_CPP_101Character::LoadItems_Deferred));

		//Async Loading
		/*
		for (int32 i = 0; i < AssetDatas.Num(); ++i)
		{
			FAssetData& AssetData = AssetDatas[i];

			TArray<FSoftObjectPath> ItemsToStream;
			FStreamableManager& Streamable = UGameGlobals::Get().StreamableManager;
			for (int32 i = 0; i < AssetDatas.Num(); ++i)
			{
				ItemsToStream.AddUnique(AssetDatas[i].ToStringReference());
			}
			//Streamable.RequestAsyncLoad(ItemsToStream, FStreamableDelegate::CreateUObject(this, &UGameCheatManager::GrantItemsDeferred));

			//Handle Tags and Values
			{
				FString FoundTypeNameString = AssetData.TagsAndValues.FindChecked(GET_MEMBER_NAME_CHECKED(UTexture2D, Filter));

				if (!FoundTypeNameString.IsEmpty()) // && FoundTypeNameString.Contains(TEXT("FooType"))
				{
					UE_LOG(LogTemp, Warning, TEXT("MyObjectLibrary - AssetData Found for UTEXTURE2D class - Tags&Values : %s"), *FoundTypeNameString);

					UE_LOG(LogTemp, Warning, TEXT("Asset loaded? : %s"), *(AssetData.IsAssetLoaded() ? FString("True") : FString("False")));
					UE_LOG(LogTemp, Warning, TEXT("Primary Asset ID : %s"), *AssetData.GetPrimaryAssetId().ToString());
					UE_LOG(LogTemp, Warning, TEXT("Object Path : %s"), *AssetData.ObjectPath.ToString());
					UE_LOG(LogTemp, Warning, TEXT("Package Path : %s"), *AssetData.PackagePath.ToString());
					UE_LOG(LogTemp, Warning, TEXT("Package Name : %s"), *AssetData.PackageName.ToString());
					//return AssetData;
				}
			}
			
		}
		*/
	}

	//Asset Registy
	
	{
		/*
			The Asset Registry is an editor subsystem which gathers information about unloaded assets asynchronously as the editor loads.
			This information is stored in memory so the editor can create lists of assets without loading them.
			The information is authoritative and is kept up to date automatically as assets are changed in memory or files are changed on disk.
			The Content Browser is the primary consumer for this system, but it may be used anywhere in editor code.
		*/

		/*
		
			1) CANNOT use `Asset.GetAsset()` if `!Asset.IsAssetLoaded()` - meaning, cannot dereference the nullptr pointer and get the object asset if it is not loaded in memory - only the FAssetData instance
			   is valid in this case, which is the representation of the asset - but it is not the living asset itself

			2) The AssetRegistry makes us adopt a convention for folder structure, careful planning of Package Names, Packes Paths, and Object Paths,
		
		*/

		//All assets in a path
		{
			FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
			TArray<FAssetData> AssetData;
			AssetRegistryModule.Get().GetAssetsByPath(FName("/Game/StarterContent"), AssetData, true); // `recursive = true` to search in subfolders as well

			int32 iteration = 0;

			for (FAssetData const& Asset : AssetData)
			{
				UE_LOG(LogTemp, Warning, TEXT("Asset Registry Loop (PATH) - current iteration: %d | object is: %s"), iteration, *Asset.AssetName.ToString());
				UE_LOG(LogTemp, Warning, TEXT("Asset loaded? : %s"), *(Asset.IsAssetLoaded() ? FString("True") : FString("False")));
				UE_LOG(LogTemp, Warning, TEXT("Primary Asset ID : %s"), *Asset.GetPrimaryAssetId().ToString());
				UE_LOG(LogTemp, Warning, TEXT("Object Path : %s"), *Asset.ObjectPath.ToString());
				UE_LOG(LogTemp, Warning, TEXT("Package Path : %s"), *Asset.PackagePath.ToString());
				UE_LOG(LogTemp, Warning, TEXT("Package Name : %s"), *Asset.PackageName.ToString());
				UE_LOG(LogTemp, Warning, TEXT("________________________________________________________________________________"));
				++iteration;

				if (Asset.IsAssetLoaded() && Asset.GetClass() == UStaticMesh::StaticClass())
				{
					UObject* ObjectRef = Asset.GetAsset();
					UStaticMesh* StaticMesh = Cast<UStaticMesh>(ObjectRef);

					if (StaticMesh)
					{
						UE_LOG(LogTemp, Warning, TEXT("PARSED UOBJECT TO STATIC MESH - Cast Successful"));
						UE_LOG(LogTemp, Warning, TEXT("________________________________________________________________________________"));
					}
				}
				
			}
		}

		//All assets in a Package
		{
			FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
			TArray<FAssetData> AssetData;
			AssetRegistryModule.Get().GetAssetsByPackageName(FName("/Game/NewerBP"), AssetData); // P_Fire

			int32 iteration = 0;

			for (FAssetData const& Asset : AssetData)
			{
				FStreamableManager Manager;
				Manager.Unload(Asset.ToSoftObjectPath());

				UE_LOG(LogTemp, Warning, TEXT("Asset Registry Loop (PACKAGE!) - current iteration: %d | object is: %s"), iteration, *Asset.AssetName.ToString());
				UE_LOG(LogTemp, Warning, TEXT("Asset loaded? : %s"), *(Asset.IsAssetLoaded() ? FString("True") : FString("False")));
				UE_LOG(LogTemp, Warning, TEXT("Primary Asset ID : %s"), *Asset.GetPrimaryAssetId().ToString());
				UE_LOG(LogTemp, Warning, TEXT("Object Path : %s"), *Asset.ObjectPath.ToString());
				UE_LOG(LogTemp, Warning, TEXT("Package Path : %s"), *Asset.PackagePath.ToString());
				UE_LOG(LogTemp, Warning, TEXT("Package Name : %s"), *Asset.PackageName.ToString());
				UE_LOG(LogTemp, Warning, TEXT("________________________________________________________________________________"));

				if (!Asset.IsAssetLoaded())
				{
					UE_LOG(LogTemp, Warning, TEXT("Asset is NOT LOADED!"));
					//Load Asset if it isn't loaded
					FSoftObjectPath Path = Asset.ToSoftObjectPath();
					Manager.RequestAsyncLoad(Path, FStreamableDelegate::CreateLambda([this, Asset]() {
						AActor* LoadedAsset = Cast<AActor>(Asset.GetAsset());
						if (LoadedAsset) {
							LoadedAsset->SetActorLocation(FVector(0, 0, 200));
							UE_LOG(LogTemp, Warning, TEXT("MyActor Loaded!! : %s"), *LoadedAsset->GetName());
						}
						

					}));
				}
				

				++iteration;
			}
		}

		//All assets of a class
		{
			FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
			TArray<FAssetData> AssetData;
			const FName Class = UStaticMesh::StaticClass()->GetFName();
			AssetRegistryModule.Get().GetAssetsByClass(Class, AssetData);

			int32 iteration = 0;

			for (FAssetData const& Asset : AssetData)
			{
				UE_LOG(LogTemp, Warning, TEXT("Asset Registry Loop (CLASS) - current iteration: %d | object is: %s"), iteration, *Asset.GetAsset()->GetName());
				UE_LOG(LogTemp, Warning, TEXT("Asset loaded? : %s"), *(Asset.IsAssetLoaded() ? FString("True") : FString("False")));
				UE_LOG(LogTemp, Warning, TEXT("Primary Asset ID : %s"), *Asset.GetClass()->GetFName().ToString());
				UE_LOG(LogTemp, Warning, TEXT("Object Path : %s"), *Asset.ObjectPath.ToString());
				UE_LOG(LogTemp, Warning, TEXT("Package Path : %s"), *Asset.PackagePath.ToString());
				UE_LOG(LogTemp, Warning, TEXT("Package Name : %s"), *Asset.PackageName.ToString());
				UE_LOG(LogTemp, Warning, TEXT("________________________________________________________________________________"));
				++iteration;
			}
		}

		//Using a filter
		{
			
			FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
			TArray<FAssetData> AssetData;

			FARFilter Filter; 
			//Filter.ClassNames.Append({ FName("Blueprint") });					// Will search for the specified type(s) - 
			/*
			Can only search for UE Native Types, and "Blueprint" - meaning, you cannot search for 
			your child BP Character "BP_Soldier" using your specialized "ASoldier" Class, only through "ACharacter".
			*/
			//Filter.PackagePaths.Append({ FName("/Game/StarterContent/Particles"), FName("/Game/StarterContent/Audio"), FName("/Game") } );				// Will search for the specified type(s) only in the defined path, i.e "Game/Characters" path
			//Filter.PackagePaths.Append({ FName("/Game/Characters") });
			Filter.ObjectPaths.Append({FName("/Game/MyTick_Char.MyTick_Char")});	// Will include this object path in the search
			Filter.bRecursivePaths = false;
			Filter.bRecursiveClasses = false;

			AssetRegistryModule.Get().GetAssets(Filter, AssetData);

			int32 iteration = 0;

			for (FAssetData const& Asset : AssetData)
			{
				UE_LOG(LogTemp, Warning, TEXT("Asset Registry Loop (FILTER_ASSETS) - current iteration: %d | object is: %s"), iteration, *Asset.AssetName.ToString());
				UE_LOG(LogTemp, Warning, TEXT("Asset loaded? : %s"), *(Asset.IsAssetLoaded() ? FString("True") : FString("False")));
				UE_LOG(LogTemp, Warning, TEXT("Primary Asset ID : %s"), *Asset.GetClass()->GetName());
				UE_LOG(LogTemp, Warning, TEXT("Object Path : %s"), *Asset.ObjectPath.ToString());
				UE_LOG(LogTemp, Warning, TEXT("Package Path : %s"), *Asset.PackagePath.ToString());
				UE_LOG(LogTemp, Warning, TEXT("Package Name : %s"), *Asset.PackageName.ToString());
				for (auto const& KVPair : Asset.TagsAndValues.CopyMap())
				{
					UE_LOG(LogTemp, Warning, TEXT("FOUND A KVP"));
					UE_LOG(LogTemp, Warning, TEXT("KVP - Key : %s"), *KVPair.Key.ToString());
					UE_LOG(LogTemp, Warning, TEXT("KVP - Value : %s"), *KVPair.Value);
				}

				for (auto const& KVPair : Asset.TagsAndValues)
				{
					UE_LOG(LogTemp, Warning, TEXT("FOUND A KVP2"));
					UE_LOG(LogTemp, Warning, TEXT("KVP2 - Key : %s"), *KVPair.Key.ToString());
					UE_LOG(LogTemp, Warning, TEXT("KVP2 - Value : %s"), *KVPair.Value.GetValue());
				}
				/*
				FAssetTagValueRef Ref = Asset.TagsAndValues.FindTag(FName("WeaponState"));
				if (!Ref.GetValue().IsEmpty())
				{
					UE_LOG(LogTemp, Warning, TEXT("KVP - Trying to find reference string... : %s"), *Ref.GetValue());
				}
				*/
				
				
				UE_LOG(LogTemp, Warning, TEXT("________________________________________________________________________________"));
				++iteration;
			}
		}
		
	}

	//Smart Pointers

	{
		UE_LOG(LogTemp, Warning, TEXT("________________________________________________________________________________"));
		TUniquePtr<int> Ptr(new int(30));
		*Ptr = 29;
		UE_LOG(LogTemp, Warning, TEXT("Smart Pointer (UNIQUE) value is: %d"), *Ptr);

		UE_LOG(LogTemp, Warning, TEXT("________________________________________________________________________________"));

		TSharedPtr<int> SPtr1(new int(42));
		TSharedPtr<int> SPtr2 = SPtr1;
		UE_LOG(LogTemp, Warning, TEXT("Smart Pointer (SHARED_1) value is: %d"), *SPtr1);
		UE_LOG(LogTemp, Warning, TEXT("Smart Pointer (SHARED_2) value is: %d"), *SPtr2);
		UE_LOG(LogTemp, Warning, TEXT("Changing value of shared ptr...."));
		*SPtr2 *= 2;
		UE_LOG(LogTemp, Warning, TEXT("Post Change:"));
		UE_LOG(LogTemp, Warning, TEXT("Smart Pointer (SHARED_1) value is: %d"), *SPtr1);
		UE_LOG(LogTemp, Warning, TEXT("Smart Pointer (SHARED_2) value is: %d"), *SPtr2);

		UE_LOG(LogTemp, Warning, TEXT("________________________________________________________________________________"));

		TWeakPtr<int> WPtr = SPtr2;
		*WPtr.Pin() = 440;
		UE_LOG(LogTemp, Warning, TEXT("Smart Pointer (WEAK) value is: %d"), *WPtr.Pin());
		UE_LOG(LogTemp, Warning, TEXT("Smart Pointer (SHARED) value is: %d"), *SPtr2);
		UE_LOG(LogTemp, Warning, TEXT("________________________________________________________________________________"));

		//! TSharedRef - Does the class need to supply an override for the 'new' operator???
		//! INVESTIGATE
		// TSharedPtr<ALearn_UE_CPP_101Character*> SharedPtr = MakeShared<ALearn_UE_CPP_101Character*>(this);
		// TSharedRef<ALearn_UE_CPP_101Character> SharedRef (*SharedPtr);
		// FString srName = SharedRef.Get().GetName();
		// UE_LOG(LogTemp, Warning, TEXT("Smart Pointer (SHARED) value is: %s"), *srName);

		TSharedPtr<int32> SharedPtr (new int32 (42));
		TSharedRef<int32> SharedRef(SharedPtr.ToSharedRef());
		SharedPtr.Reset();
		int32 value = SharedRef.Get();
		UE_LOG(LogTemp, Warning, TEXT("Smart Pointer (SHARED_REF) value is: %d"), value);
		UE_LOG(LogTemp, Warning, TEXT("________________________________________________________________________________"));

		//UObjects derived classes
		TObjectPtr<ALearn_UE_CPP_101Character> ObjPtr(this);
		UE_LOG(LogTemp, Warning, TEXT("CHAR: Smart Pointer (OBJECT_PTR) Health value is: %f"), ObjPtr.Get()->Health);

		MyString = FString("Nah Uh!!");
		UE_LOG(LogTemp, Warning, TEXT("CHAR: Smart Pointer (OBJECT_PTR) MyString value is: %s"), *ObjPtr.Get()->MyString);
		ObjPtr.Get()->MyString = FString("Hell Yeah!!!");
		UE_LOG(LogTemp, Warning, TEXT("CHAR: Post Change in ObjectPtr - MyString value is: %s"), *MyString);

		MyObjPtr = GetWorld()->SpawnActor<AActor>();
		UE_LOG(LogTemp, Warning, TEXT("ObjectPtr Actor Name: %s"), *MyObjPtr.Get()->GetName());

		//TLazyObjectPtr

		TLazyObjectPtr<ALearn_UE_CPP_101Character> LazyObj(this);
		if (LazyObj.IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("Lazy OvjectPtr is Valid"));
			UE_LOG(LogTemp, Warning, TEXT("LAzy Obj: %s"), *LazyObj.Get()->GetName());
		}

		//TSoftObjectPtr

		FSoftObjectPath PathTo(FString("/Game/StarterContent/Textures/T_Ground_Grass_D.T_Ground_Grass_D"));
		SPtr = (PathTo);
		SPtr.LoadSynchronous();
		if (SPtr.IsValid()) {
			UTexture2D* Texture = SPtr.Get();
			UE_LOG(LogTemp, Warning, TEXT("Texture 1 Loaded!!!"));
			UE_LOG(LogTemp, Warning, TEXT("TextureName: %s"), *Texture->GetName());
		}

		FSoftObjectPath PathTo1(FString("/Game/StarterContent/Textures/T_ground_Moss_D.T_ground_Moss_D"));
		AssetPtr = (PathTo1);
		UTexture2D* TextureAsset = AssetPtr.LoadSynchronous();
		if (TextureAsset) {
			UE_LOG(LogTemp, Warning, TEXT("Texture 2 Loaded!!!"));
			UE_LOG(LogTemp, Warning, TEXT("TextureName: %s"), *AssetPtr.Get()->GetName());
		}


		FStreamableManager StreamableManager;
		FSoftObjectPath PathTo2 (FString("/Game/StarterContent/Textures/T_Concrete_Poured_D.T_Concrete_Poured_D"));
		TSoftObjectPtr<UTexture2D> MyAssetPtr (PathTo2);
		UTexture2D* Texture =  MyAssetPtr.LoadSynchronous();
		if (!Texture) // If Asset hasn't loaded yet, AsyncLoad it
		{
			StreamableManager.RequestAsyncLoad(PathTo2, FStreamableDelegate::CreateLambda([this, MyAssetPtr]()
			{
				UTexture2D* LoadedTexture = Cast<UTexture2D>(MyAssetPtr.Get());
				if (LoadedTexture != nullptr)
				{
					// Asset has successfully loaded Asynchronously - can now do something with it
					UE_LOG(LogTemp, Warning, TEXT("Texture 3 ASYNC Loaded!!!"));
				}
			}));
		}
		else	// Asset successfully loaded Synchronously
		{
			UE_LOG(LogTemp, Warning, TEXT("Texture 3 HAS Loaded!!!"));
			UE_LOG(LogTemp, Warning, TEXT("TextureName: %s"), *Texture->GetName());
		}

	}
	

	//Template Functionality
	{
		ALearn_UE_CPP_101Character* Inst = SpawnAnyActor<ALearn_UE_CPP_101Character>(GetWorld(), ALearn_UE_CPP_101Character::StaticClass(), FVector(0, 0, 500), FRotator(0, 0, 0));
		if (Inst)
		{
			UE_LOG(LogTemp, Warning, TEXT("Template spawn Worked!!! instance is %s"), *Inst->GetName());
			Inst->GetMesh()->SetSimulatePhysics(true);
		}

		ALearn_UE_CPP_101Character* NewActor = UMyGenericClass<ALearn_UE_CPP_101Character>::DoSomething(this);
		TMyContainer<ALearn_UE_CPP_101Character, UCameraComponent>::SpawnComponent(this);

		TMyRealContainer<ALearn_UE_CPP_101Character*> CharacterContainer;
		//CharacterContainer.AddIndex(this);
		CharacterContainer.Add(this);
		CharacterContainer.AddIndex(Inst);
		CharacterContainer.PrintAll();



		AActor* Obj = ActOnSomething<AActor>();
		UE_LOG(LogTemp, Warning, TEXT("Newly created Object via template function! name is: %s"), *Obj->GetName());
	}
	

	//TArray
	{
		TArray<float> Arr;
		Arr.Add(1.0f);
		Arr.Append({ 2.0f, 3.0f, 4.0f, 5.0f });
		Arr.Insert(999.0f, 0);
		Arr.EmplaceAt(0, 251.5f);
		bool bIsEmpty = Arr.IsEmpty();
		bool bContains = Arr.Contains(432.0f);
		bool bIndexIsValid = Arr.IsValidIndex(0);

		for (int32 i = 0; i < Arr.Num(); ++i)
		{
			UE_LOG(LogTemp, Warning, TEXT("Looping over array... Index is: %d | value is: %f"), i, Arr[i]);
		}
	}

	//TSet
	{
		TSet<float> Set1;
		TSet<float> Set2;
		Set1.Add(1.0f);
		Set1.Add(1.0f);
		Set1.Add(1.0f);
		Set1.FindOrAdd(2.0f);
		Set1.Append({ 3.0f, 4.0f, 5.0f });
		
		
		for (float num: Set1)
		{
			UE_LOG(LogTemp, Warning, TEXT("Looping over Set...  value is: %f"), num);
		}

		float num = Set1.FindOrAdd(2.0f);
		TSet Union = Set1.Union(Set2);
		TSet Intersection = Set1.Intersect(Set2);
		TSet Difference = Set1.Difference(Set2);
		bool bContains = Set1.Contains(6.0f);
	}

	//TMap
	{
		TMap<FString, float> Map1;
		Map1.Add(FString("Element 1"), 440.0f);
		Map1.Add(FString("Element 2"), 540.0f);
		Map1.Add(FString("Element 3"), 640.0f);

		float num = *Map1.Find("Element 1");
		

		for (TTuple<FString, float>& Pair : Map1)
		{
			UE_LOG(LogTemp, Warning, TEXT("Looping over Map...  Key is: %s | Value is: %f"), *Pair.Key, Pair.Value);
		}
	}

	//TTuple
	{
		TTuple <float, int32> MyTuple;
		MyTuple.Key = 42.0f;
		MyTuple.Value = 420;

		UE_LOG(LogTemp, Warning, TEXT("Logging Tuple...  Key is: %f | Value is: %d"), MyTuple.Key, MyTuple.Value);
	}

	//Min/Max
	{
		TArray<float> MyVars;
		MyVars.Append({ 1.0f, 202.0f, 5221.0f, 98237.0f, 0.01f });
		const float MaxValue = FMath::Max<float>(MyVars); //dont need to know the index of the max value
		UE_LOG(LogTemp, Warning, TEXT("max value within this array is: %f"), MaxValue);

		TArray<int32> MyInts;
		MyInts.Append({ 23, 921, 62, 4239, 2 });
		int32 MaxIndex;
		const int32 MaxValueInIndex = FMath::Max<int32>(MyInts, &MaxIndex);
		UE_LOG(LogTemp, Warning, TEXT("index of the max value is: %d"), MaxIndex);
	}

	
	
	//Relative Logging
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *GetClass()->GetName());
		UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(__FUNCSIG__));
		UE_LOG(LogTemp, Warning, TEXT("%d"), __LINE__);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(__FUNCTION__));
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(__FUNCDNAME__));

		UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(__FUNCTIONW__));
		UE_LOG(LogTemp, Warning, TEXT("%d"), __LINE__);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(__FILE__));
	}
	
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(__BASE_FILE__));
	//Class members can be iterated upon - as long as they are gathered by the Reflection System
	/*
		The engine uses Macro declarations as additional declarations for C++ classes, functions and variables - in order for 
		them to be extendable and accessible to Blueprints and to the project editor.
		They can also accept arguements for further articulating the setup needed for the annotated code.
		Found at: Engine/Source/Runtime/CoreUObject/Public/UObject/ObjectMacros.h => Line #597

		These macros are used as annotations for the Unreal Header Tool, which is responsible for converting our annotated code 
		into auto generated code (that we should never be concerned about) for the engine to expose the annotated classes and members for
		modifications in the editor.
		UHT will parse this code, see those anotations (like UCLASS()), and know that it needs to generate some code about that class and 
		place it somewhere (and obviously remove the annotations afterwards).
		Part of that generated code goes in that "MyObject.generated.h" file, and part of that code is injected in the location of 
		that GENERATED_BODY() macro just before we compile.

		Reflection is the ability of a program to examine itself at runtime. This is hugely useful and is a foundational technology 
		of the Unreal engine, powering many systems such as detail panels in the editor, serialization, garbage collection, network replication, 
		and Blueprint/C++ communication. However, C++ doesn’t natively support any form of reflection, so Unreal has its own system to harvest, query, 
		and manipulate information about C++ classes, structs, functions, member variables, and enumerations. We typically refer to reflection as the 
		property system since reflection is also a graphics term.

		The type hierarchy for the property system looks like this:

		UField
			UStruct
				UClass (C++ class)
				UScript++++++Struct (C++ struct)
				UFunction (C++ function)

			UEnum (C++ enumeration)

			UProperty (C++ member variable or function parameter)

				(Many subclasses for different types)
		UStruct is the basic type of aggregate structures (anything that contains other members, such as a C++ class, struct, or function), and shouldn’t be confused 
		with a C++ struct (that's UScriptStruct). UClass can contain functions or properties as their children, while UFunction and UScriptStruct are limited to just properties.

		You can get the UClass or UScriptStruct for a reflected C++ type by writing UTypeName::StaticClass() or FTypeName::StaticStruct(), and you can get the type for a UObject 
		instance using Instance->GetClass() (it's not possible to get the type of a struct instance since there is no common base class or required storage for structs).

		Unreal has a robust system for handling game objects. The base class for objects in Unreal is UObject. The UCLASS macro can be used to tag classes 
		derived from UObject so that the UObject handling system is aware of them.
		UObjects can have member variables (known as properties) or functions of any type. However, for the Unreal Engine to recognize and manipulate those variables 
		or functions, they must be marked with special macros and must conform to certain type standards. For details on those standards, refer to 
		the Properties and UFunctions reference pages.
		This is why we can create a function that returns an unreal data type, such as UCameraComponent* GetCamera(){return MyCamera;}
	*/

	//CDO
	{
		{
			UClass* MyObject = UMyObject::StaticClass();
			;
			for (TFieldIterator<FProperty> PropertyIterator(MyObject); PropertyIterator; ++PropertyIterator)
			{
				FProperty* Property = *PropertyIterator;

				UE_LOG(LogTemp, Warning, TEXT("LOOPING OVER : UMyObject Properties - now at : % s"), *Property->GetName());

			}

			for (TFieldIterator<UFunction> FunctionIterator(MyObject); FunctionIterator; ++FunctionIterator)
			{
				UFunction* Function = *FunctionIterator;

				UE_LOG(LogTemp, Warning, TEXT("Looping OVER : UMyObject Function - now at : %s"), *Function->GetName());
			}
		}
		UE_LOG(LogTemp, Warning, TEXT("Finished Looping. Prepare for begining new task... \n Now Getting Bass Class CDO:"));

		//-------------------------------------------------------------------------------------------------------------------------------------

		//Changing CDO attributes for the c++ class
		/*
			UObject is the base class for objects managed by Unreal and is required to
			get our class garbage collected, replicated over the network, serialized, and more.

			UObject keeps the StaticClass() form
			UClass holds the default object of the class
		*/
		{
			UClass* BaseClass = UMyObject::StaticClass();
			UMyObject* BaseCDO = BaseClass->GetDefaultObject<UMyObject>();
			//! SAME AS
			UMyObject* BaseCDO_ = GetMutableDefault<UMyObject>();
			// ! OR AS
			UMyObject* MyObject = UMyObject::StaticClass()->GetDefaultObject<UMyObject>();

			UMyObject* BaseClass_BeforeEdit = NewObject<UMyObject>(this, BaseClass, NAME_None, RF_NoFlags, BaseCDO, true);
			UE_LOG(LogTemp, Warning, TEXT("BassClass before modifying: %f"), BaseClass_BeforeEdit->MyForce);

			BaseCDO->MyForce = 15.0f;
			UE_LOG(LogTemp, Warning, TEXT("Modified CDO property......."));

			UMyObject* BaseClass_AfterEdit = NewObject<UMyObject>(this, BaseClass, NAME_None, RF_NoFlags, BaseCDO, true);
			UE_LOG(LogTemp, Warning, TEXT("BaseClass after modifying: %f"), BaseClass_AfterEdit->MyForce);

			//Get all instances that use this CDO
			TArray<UObject*> ActiveInstancesOfCDO;
			BaseCDO->GetArchetypeInstances(ActiveInstancesOfCDO);
		}

		UE_LOG(LogTemp, Warning, TEXT("Task Finished. Prepare for begining new task... \n Now Getting Derived Class CDO:"));

		//Changing CDO attributes for the BP class
		{
			UClass* DerivedBPClass = LoadClass<UMyObject>(NULL, TEXT("Blueprint'/Game/BP_MyObject.BP_MyObject_C'"));
			UMyObject* DerivedBPCDO = DerivedBPClass->GetDefaultObject<UMyObject>();

			UMyObject* DerivedBPClass_BeforeEdit = NewObject<UMyObject>(this, DerivedBPClass, NAME_None, RF_NoFlags, DerivedBPCDO, true);
			UE_LOG(LogTemp, Warning, TEXT("BassClass before modifying: %f"), DerivedBPClass_BeforeEdit->MyForce);

			DerivedBPCDO->MyForce = 30.0f;
			UE_LOG(LogTemp, Warning, TEXT("Modified CDO property......."));

			UMyObject* DerivedBPClass_AfterEdit = NewObject<UMyObject>(this, DerivedBPClass, NAME_None, RF_NoFlags, DerivedBPCDO, true);
			UE_LOG(LogTemp, Warning, TEXT("BaseClass after modifying: %f"), DerivedBPClass_AfterEdit->MyForce);
		}
	}
	
	
		
	

	Collision->OnComponentHit.AddUniqueDynamic(this, &ALearn_UE_CPP_101Character::OnHit);

	AudioComp->SetSound(SoundToPlay);
	AudioComp->bOverrideAttenuation = true;
	//AudioComp->AttenuationSettings 
	AudioComp->Play();

	MusicToPlay3D->PitchMultiplier = FMath::RandRange(0.8f, 1.2f);
	//UGameplayStatics::PlaySound2D(this, MusicToPlay3D);
	
	//UGameplayStatics::PlaySoundAtLocation();
	
	//Looping over data rows of the DT
	TArray <FName> MyArray{ MaterialDataBase->GetRowNames() };

	for (FName RowName : MyArray)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, FString::Printf(TEXT("DataTable Row Name is: %s"), *(RowName.ToString()) ));
	}

	//Getting data from DT
	static const FString Context("Some Context eh");
	FMyDataBase* DataMaterial = MaterialDataBase->FindRow<FMyDataBase>(FName("R_1"), Context);
	if (DataMaterial)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, FString::Printf(TEXT("DataTable Material name is: %s"), *(DataMaterial->Material->GetName())));
	}

	FMyDataBase* DataMaterial2 = MaterialDataBase->FindRow<FMyDataBase>(FName("R_2"), Context, true);
	if (DataMaterial2)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, FString::Printf(TEXT("DataTable Material name is: %s"), *(DataMaterial2->Material->GetName())));
	}
	
	//Writing new data to DT
	FMyDataBase NewRow;
	NewRow.Material = DataMaterial->Material;
	NewRow.Specs = FString("WTF IS THIS DATATABLE EH?!?!?!?!");

	MaterialDataBase->AddRow(FName("This_Is_A_New_Row"), NewRow);



	TArray <FName> MyArray2{ MaterialDataBase->GetRowNames() };
	for (FName RowName : MyArray2)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("UPDATED DataTable Row Name is: %s"), *(RowName.ToString())));
	}

	//FMyDataBase* DataMaterial = MaterialDataBase->FindRow<FMyDataBase>(FName("R_2"), Context, true);




	{
	if (WillState == EWillState::Alarm_State)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, FString("Will state is: Alarmed"));
	}
	if (AgressionMode == EAgressionMode::FullBerserk)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, FString("Agression mode is: Full Berserk"));
	}

	//Bitmask Enum
	AnimThreads &= ~static_cast<uint8>(EAnimationThreads::Idle);			//Bitwise Remove

	if (AnimThreads & static_cast<uint8>(EAnimationThreads::Idle))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, FString("Anim Thread is: Idle"));
	}

	AnimThreads |= static_cast<uint8>(EAnimationThreads::Punch);		//Bitwise Add

	AnimThreads = static_cast<uint8>(EAnimationThreads::Shoot);			//Override current mask and set a single Enumerator value

	if (AnimThreads & static_cast<uint8>(EAnimationThreads::Punch))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, FString("Anim Thread is: Punch"));
	}
	if (AnimThreads & static_cast<uint8>(EAnimationThreads::Shoot))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, FString("Anim Thread is: Shoot"));
	}
	}

	
}

void ALearn_UE_CPP_101Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UE_LOG(LogTemp, Display, TEXT("Tick On C++ Class - MoveUpdatedComponent F7"));
	
	

	//bool bA { GetCharacterMovement()->MoveUpdatedComponent(FVector(100, 100, 0), GetActorRotation(), true) };
	//bool bB { GetCharacterMovement()->MoveUpdatedComponent(FVector(-100, -100, 0), GetActorRotation(), true) };

}

void ALearn_UE_CPP_101Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ALearn_UE_CPP_101Character::FireTrace);

	{
	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &ALearn_UE_CPP_101Character::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &ALearn_UE_CPP_101Character::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &ALearn_UE_CPP_101Character::LookUpRate);			// Look up
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &ALearn_UE_CPP_101Character::LookRightRate);	// Look Right

	
	// "turnAtRate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &ALearn_UE_CPP_101Character::LookUpAtRateGMPD);
	PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &ALearn_UE_CPP_101Character::TurnAtRateGMPD);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ALearn_UE_CPP_101Character::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ALearn_UE_CPP_101Character::TouchStopped);
	}
}

void ALearn_UE_CPP_101Character::FireTrace()
{
	//You can think of the CDO as a Dormant object which is never instantiated - instead, it is used as a template upon which new objects of a particular class are instantiated
	/*ALearn_UE_CPP_101Character* Char = GetMutableDefault<ALearn_UE_CPP_101Character>();
	Char->Health = 51.0f;
	Char->SaveConfig();*/

	//Trigger AI Listener Perception event
	//UAISense_Hearing::ReportNoiseEvent(GetWorld(), GetActorLocation(), 1.0f, this, 0.0f, FName("Noise"));

	FVector3d LocationForMusic(991.f,2760.f,50.f);
	DrawDebugLine(GetWorld(), LocationForMusic, LocationForMusic + FVector(0, 0, 1000), FColor::Purple, false, 5.0f);
	UGameplayStatics::PlaySoundAtLocation(this, MusicToPlay3D, LocationForMusic);
	UGameplayStatics::PlaySoundAtLocation(this, SoundToPlay, GetActorLocation(), 0.5f);

	UMyAnimInstance* MyAnimInstance = Cast<UMyAnimInstance>( GetMesh()->GetAnimInstance() );
	MyAnimInstance->PlayMyMontage();

	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString("Attempting to interact..."));

	FCollisionQueryParams CollisionQuery;
	CollisionQuery.AddIgnoredActor(this);
	CollisionQuery.bTraceComplex = true;
	


	FHitResult HitResults;
	FVector Start(GetActorLocation() + (GetActorForwardVector() * 50));
	FVector End(Start + (GetActorForwardVector() * 500));
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResults, Start, End, ECollisionChannel::ECC_Camera, CollisionQuery);

	FHitResult TraceResult;
	FRotator TraceRotation;
	FVector TraceStartLocation;
	GetActorEyesViewPoint(TraceStartLocation, TraceRotation);
	FVector TraceEndLocation = FVector(UKismetMathLibrary::Conv_RotatorToVector(TraceRotation) * 500 + TraceStartLocation);
	bool bInteract = GetWorld()->LineTraceSingleByChannel(TraceResult, TraceStartLocation + (GetActorForwardVector() * 50), TraceEndLocation, ECollisionChannel::ECC_Camera, CollisionQuery);

	DrawDebugLine(GetWorld(), HitResults.TraceStart, HitResults.TraceEnd, FColor::Red, false, 5.0f);
	DrawDebugLine(GetWorld(), TraceResult.TraceStart, TraceResult.TraceEnd, FColor::Green, false, 5.0f);

	if (bHit)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Orange, FString("Forward Trace Hit Something!"));

		if (HitResults.GetActor() != nullptr)
		{
			//TSubclassOf<UDamageType> DamageType = UDamageType::StaticClass();
			
			//UClass* DamageTypeClass = UDamageType::StaticClass();
			TSubclassOf<UDamageType> DamageType = (UDamageType::StaticClass());
			DamageType.Get();
			FDamageEvent DamageEvent(DamageType);
			HitResults.GetActor()->TakeDamage(20.0f, DamageEvent, GetInstigatorController(), this);

			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, FString("Trying to damage enemy.....FORWARD"));
		}

		if (HitResults.GetActor()->Implements<UInteract>())//(TraceResults.GetActor()->GetClass()->ImplementsInterface(UInteract::StaticClass()))
		{
			IInteract::Execute_InteractWithObject(HitResults.GetActor());
		}
	}
	else if (bInteract)
	{
		if (TraceResult.GetActor() != nullptr)
		{
			//TSubclassOf<UDamageType> DamageType = UDamageType::StaticClass();

			//UClass* DamageTypeClass = UDamageType::StaticClass();

			//Deal Damage & Report a damage event to the Hit Actor
			TSubclassOf<UDamageType> DamageType = (UDamageType::StaticClass());
			DamageType.Get()->GetClass();
			FDamageEvent DamageEvent(DamageType);
			TraceResult.GetActor()->TakeDamage(20.0f, DamageEvent, GetInstigatorController(), this);
			UAISense_Damage::ReportDamageEvent(this, TraceResult.GetActor(), this, 20, TraceResult.TraceStart, TraceResult.Location);
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, FString("Trying to damage enemy.....CAMERA"));
		}
		
		if (TraceResult.GetActor()->Implements<UInteract>())
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Orange, FString("Camera Trace Hit Something!"));
			IInteract::Execute_InteractWithObject(TraceResult.GetActor());
		}
	}
}

void ALearn_UE_CPP_101Character::InteractWithObject_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, FString("Who the fuck is interacting with me?"));
}

void ALearn_UE_CPP_101Character::LookUpRate(float Rate)
{
	AddControllerPitchInput(Rate); // * GetWorld()->GetDeltaSeconds() * 100
}

void ALearn_UE_CPP_101Character::LookRightRate(float Rate)
{
	AddControllerYawInput(Rate); //  * GetWorld()->GetDeltaSeconds() * 100
}



void ALearn_UE_CPP_101Character::TurnAtRateGMPD(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void ALearn_UE_CPP_101Character::LookUpAtRateGMPD(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void ALearn_UE_CPP_101Character::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}


void ALearn_UE_CPP_101Character::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}


void ALearn_UE_CPP_101Character::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void ALearn_UE_CPP_101Character::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void ALearn_UE_CPP_101Character::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Orange, FString("Collision Component HitCollider Success!"));
	CollisionHit = Hit;
}

void ALearn_UE_CPP_101Character::GetMyObject(UMyObject* Object)
{
	// &MyStaticClass == &MyClass
	UClass* MyStaticClass = UMyObject::StaticClass();
	UClass* MyClass = Object->GetClass();

	//Class Default Object
	UMyObject* CDO = MyClass->GetDefaultObject<UMyObject>();

	//Get all instances that use this CDO
	TArray<UObject*> ActiveInstancesOfCDO;
	CDO->GetArchetypeInstances(ActiveInstancesOfCDO);
}




