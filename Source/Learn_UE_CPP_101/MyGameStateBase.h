// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyPlayerState.h"
#include "MyGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class LEARN_UE_CPP_101_API AMyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	int32 TeamScore_A;
	int32 TeamScore_B;

	TArray<AMyPlayerState*> AllPlayers{ PlayerArray };

	

	int32 GetTeamKills()
	{
		int32 OverallTeamKills{};

		for (AMyPlayerState* Player : AllPlayers)
		{
			OverallTeamKills += Player->Kills;
		}

		return OverallTeamKills;
	}


	void  AddTeamScore(FString Team, int32 InScore)
	{
		if(Team == "A" || Team == "a")
		{
			TeamScore_A += InScore;
			UE_LOG(LogTemp, Warning, TEXT("Team %s got %d points!"), *Team, InScore);
		}
		else if (Team == "B" || Team == "b")
		{
			TeamScore_B += InScore;
			UE_LOG(LogTemp, Warning, TEXT("Team %s got %d points!"), *Team, InScore);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Invalid Team! %d points wasted!"), InScore);
		}
		
	}
};
