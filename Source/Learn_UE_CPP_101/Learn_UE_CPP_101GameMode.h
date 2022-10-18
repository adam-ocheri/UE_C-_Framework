// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "Learn_UE_CPP_101GameMode.generated.h"

UCLASS(minimalapi)
class ALearn_UE_CPP_101GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ALearn_UE_CPP_101GameMode();

	virtual ~ALearn_UE_CPP_101GameMode() = default;

	virtual void StartPlay();

	UFUNCTION(BlueprintPure)
	virtual int32 GetTeamScore(FString Team) const;

	UFUNCTION(BlueprintCallable)
	virtual void SetTeamScore(FString Team, int32 Score);

	int32 GetTeamKills() const;

	int32 GetTeamDeaths() const;

	virtual void Tick(float DeltaSeconds);

	
	
};



