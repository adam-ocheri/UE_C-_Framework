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

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "NumStruct.h"

//////////////////////////////////////////////////////////////////////////
// ALearn_UE_CPP_101Character

ALearn_UE_CPP_101Character::ALearn_UE_CPP_101Character(const FObjectInitializer& ObjectInitializer) // update construcxtor in cpp file too
	: Super { ObjectInitializer.SetDefaultSubobjectClass<UMyCharacterMovementComponent>(ACharacter::CharacterMovementComponentName) }
{
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
	GetCapsuleComponent()->SetHiddenInGame(false);
	

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
	
}



void ALearn_UE_CPP_101Character::BeginPlay()
{
	Super::BeginPlay();

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






//////////////////////////////////////////////////////////////////////////
// Input

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
	FVector3d LocationForMusic(991.f,2760.f,50.f);
	DrawDebugLine(GetWorld(), LocationForMusic, LocationForMusic + FVector(0, 0, 1000), FColor::Purple, false, 5.0f);
	UGameplayStatics::PlaySoundAtLocation(this, MusicToPlay3D, LocationForMusic);
	UGameplayStatics::PlaySoundAtLocation(this, SoundToPlay, GetActorLocation(), 0.5f);

	UMyAnimInstance* MyAnimInstance = Cast<UMyAnimInstance>( GetMesh()->GetAnimInstance() );
	MyAnimInstance->PlayMyMontage();

	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString("Attempting to interact..."));

	FCollisionQueryParams CollisionQuery;
	CollisionQuery.AddIgnoredActor(this);


	FHitResult HitResults;
	FVector Start(GetActorLocation());
	FVector End(Start + (GetActorForwardVector() * 500));
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResults, Start, End, ECollisionChannel::ECC_Camera, CollisionQuery);

	FHitResult TraceResult;
	FRotator TraceRotation;
	FVector TraceStartLocation;
	GetActorEyesViewPoint(TraceStartLocation, TraceRotation);
	FVector TraceEndLocation = FVector(UKismetMathLibrary::Conv_RotatorToVector(TraceRotation) * 500 + TraceStartLocation);
	bool bInteract = GetWorld()->LineTraceSingleByChannel(TraceResult, TraceStartLocation, TraceEndLocation, ECollisionChannel::ECC_Camera, CollisionQuery);

	DrawDebugLine(GetWorld(), HitResults.TraceStart, HitResults.TraceEnd, FColor::Red, false, 5.0f);
	DrawDebugLine(GetWorld(), TraceResult.TraceStart, TraceResult.TraceEnd, FColor::Green, false, 5.0f);

	if (bHit)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Orange, FString("Forward Trace Hit Something!"));

		if (HitResults.GetActor()->Implements<UInteract>())//(TraceResults.GetActor()->GetClass()->ImplementsInterface(UInteract::StaticClass()))
		{
			IInteract::Execute_InteractWithObject(HitResults.GetActor());
		}
	}
	else if (bInteract)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Orange, FString("Camera Trace Hit Something!"));
		if (TraceResult.GetActor()->Implements<UInteract>())
		{
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




//with the core functionality and behaviour of animations defined in both our custom c++ and BP AnimInstance class, we can expand on this basic animation system setup by incorporating0


