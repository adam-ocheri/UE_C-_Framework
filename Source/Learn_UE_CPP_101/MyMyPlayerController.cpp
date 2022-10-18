// Fill out your copyright notice in the Description page of Project Settings.


#include "MyMyPlayerController.h"
#include "Learn_UE_CPP_101Character.h"
#include "Kismet/GameplayStatics.h"

//1. PlayerState - "InitPlayerState" and "OnRep_PlayerState"				-	(Via inculding the custom PlayerState class header file)
//2. Getting the Controlled Pawn via a Cast									-	(Via UGameplayStatics)
//3. Getting a reference to the Controller in the game mode via a Cast		-	(Via UGameplayStatics)


//The PlayerController would contain data that is relevant to it's local player, and it owns the pawn (the "ControlledPawn")
//Among the many things that the player controller is responsible for, such as handling input data and HUD management, the PlayerState is initialized within the PlayerController function "InitPlayerState".
//...


//The PlayerController class is a very unique class that is used for controlling a pawn/ character
//If the game was a multiplayer, then each client would get a PlayerController of it's own.
//The PlayerState, PlayerController, and ControlledPawn would all be instantiated multiple times for as many players currntly ib the match
//In contrast, it is important to note that the GameMode and the GameState are global, being spawned once, and they exist on the server.

//Additionaly, the PlayerController has numerous Replication events that assist in passing data to the server, such as the "OnRep_PlayerState" function. 
//This function is called after the PlayerState is initialized - and succesfully replicated.

/*
  It is important to know, that the Input system exists under Hierarchies:
	1- Actors(in order of latest enabled)
	2- PlayerControllers
	3- LevelScripts
	4- Pawns


	By default, each member in this hierarchy would have it's input Consumed by the member above it in the hierarchy tree.



*/

AMyMyPlayerController::AMyMyPlayerController()
{

	PrimaryActorTick.bCanEverTick = true;

}

void AMyMyPlayerController::BeginPlay()
{



	MyPawn = Cast<ALearn_UE_CPP_101Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (MyPawn != nullptr)
	{
		SetPawn(MyPawn);
		MyPawn->Health = 100;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("HERE_PlayerController - THIS Player Name is: %s"), *MyPawn->GetName()));
		UE_LOG(LogTemp, Warning, TEXT("HERE_Player Controller - Player Name is : %s"), *GetPawn()->GetName());

	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("HERE_PlayerController FAIL!!!!!!!!!!")));
		UE_LOG(LogTemp, Warning, TEXT("Player Controller FAIL"));
	}

	MyHUD = GetHUD<AMyHUD>();




	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("PlayerController - THIS Player Name is: %s")));
}

void AMyMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	FInputActionBinding& Jump_Bind = InputComponent->BindAction("Jump", IE_Pressed, this, &AMyMyPlayerController::JumpStart);
	InputComponent->BindAction("Jump", IE_Released , this, &AMyMyPlayerController::JumpEnd);
	Jump_Bind.bConsumeInput = false;

	FInputAxisBinding& LookUp_Bind = InputComponent->BindAxis("Look Up / Down Mouse", this, &AMyMyPlayerController::LookUp);
	LookUp_Bind.bConsumeInput = false;
	FInputAxisBinding& LookRight_Bind = InputComponent->BindAxis("Turn Right / Left Mouse", this, &AMyMyPlayerController::LookRight);
	LookRight_Bind.bConsumeInput = false;
}

void AMyMyPlayerController::LookUp(float Rate)
{
	//AddPitchInput(Rate);
	MyPawn->LookUpRate(Rate);
}

void AMyMyPlayerController::LookRight(float Rate)
{
	//AddYawInput(Rate);
	MyPawn->LookRightRate(Rate);
}

void AMyMyPlayerController::JumpStart()
{
	MyPawn->Jump(); //ACharacter inherited
}
void AMyMyPlayerController::JumpEnd()
{
	MyPawn->StopJumping(); //ACharcter inherited
}

//====================================================================================================================================================================================//
void AMyMyPlayerController::ExecuteConsoleCommand(FString Command)
{
	ConsoleCommand(Command);
}

AMyPlayerState* AMyMyPlayerController::GetThisPlayerState()
{
	return ThisPlayerState;
}

void AMyMyPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("PlayerController")));
}

void AMyMyPlayerController::InitPlayerState()
{
	Super::InitPlayerState();

	ThisPlayerState = GetPlayerState<AMyPlayerState>();

	ThisPlayerState->Kills = 0;
	ThisPlayerState->Deaths = 0;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("PlayerState - THIS Player ID is: %d"), ThisPlayerState->GetPlayerId()));


	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("PlayerState has Initialized!"));
	
}



void AMyMyPlayerController::SetPlayerKills()
{
	ThisPlayerState->Kills += 1;
}

int32 AMyMyPlayerController::GetPlayerKills()
{
	return ThisPlayerState->Kills;
}






void AMyMyPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	

	UE_LOG(LogTemp, Warning, TEXT("ON REP - THIS Player ID is: %d"), ThisPlayerState->GetPlayerId());
	int32 PlayerID = ThisPlayerState->GetPlayerId();
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("ON REP - THIS Player ID is: %d"), GetPlayerState<AMyPlayerState>()->GetPlayerId()));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("ON REP - THIS Player ID is: %d"), ThisPlayerState->GetPlayerId()));
}
