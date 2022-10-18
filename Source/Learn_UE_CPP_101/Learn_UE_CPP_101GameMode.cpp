// Copyright Epic Games, Inc. All Rights Reserved.

#include "Learn_UE_CPP_101GameMode.h"
#include "Learn_UE_CPP_101Character.h"
#include "MyMyPlayerController.h"
#include "MyGameStateBase.h"
#include "MyPlayerState.h"
#include "GameFramework/Controller.h"
#include "MyHUD.h"
#include "Kismet/GameplayStatics.h"



ALearn_UE_CPP_101GameMode::ALearn_UE_CPP_101GameMode()
{
	DefaultPawnClass = ALearn_UE_CPP_101Character::StaticClass();

	PlayerControllerClass = AMyMyPlayerController::StaticClass();

	GameStateClass = AMyGameStateBase::StaticClass();

	PlayerStateClass = AMyPlayerState::StaticClass();

	HUDClass = AMyHUD::StaticClass();

	PrimaryActorTick.bCanEverTick = true;

	

	
}


void ALearn_UE_CPP_101GameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//GetPlayersDeaths();
}

void ALearn_UE_CPP_101GameMode::StartPlay()
{
	//Initialization code goes here

	//AMyMyPlayerController* MyPC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	Super::StartPlay();

	AMyMyPlayerController* MyPC = Cast <AMyMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	
	if (MyPC != nullptr && MyPC->MyPawn != nullptr)
	{
		MyPC->MyPawn->Health = 100;
		GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, TEXT("GAME_MODE: PlayerController object STORED!!!!!!!!"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Red, TEXT("GAME_MODE: PlayerController object FAILED TO BE STORED!"));
	}
	
	//

	
}

int32 ALearn_UE_CPP_101GameMode::GetTeamScore(FString Team) const
{
	if (Team == "A" || Team == "a")
	{
		return GetGameState<AMyGameStateBase>()->TeamScore_A;
	}
	else if (Team == "B" || Team == "b")
	{
		return GetGameState<AMyGameStateBase>()->TeamScore_B;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid Team!"));
		return 0;
	}
}

void ALearn_UE_CPP_101GameMode::SetTeamScore(FString Team, int32 Score)
{
	GetGameState<AMyGameStateBase>()->AddTeamScore(Team, Score);
}



int32 ALearn_UE_CPP_101GameMode::GetTeamKills() const
{
	int32 OverallTeamKills{};
	
	
	
	TArray <AMyPlayerState*> AllPlayers { GetGameState<AMyGameStateBase>()->PlayerArray };

	for (AMyPlayerState* Player : AllPlayers)
	{
		OverallTeamKills += Player->Kills;
	}

	UE_LOG(LogTemp, Warning, TEXT("Total Team Kills: %d"), OverallTeamKills);
	return OverallTeamKills;
}

int32 ALearn_UE_CPP_101GameMode::GetTeamDeaths() const
{
	int32 OverallTeamDeaths{};

	TArray <AMyPlayerState*> AllPlayers { GetGameState<AMyGameStateBase>()->PlayerArray };

	for (AMyPlayerState* Player : AllPlayers)
	{
		OverallTeamDeaths += Player->Deaths;
	}

	UE_LOG(LogTemp, Warning, TEXT("Total Team Deaths: %d"), OverallTeamDeaths);
	return OverallTeamDeaths;
}



