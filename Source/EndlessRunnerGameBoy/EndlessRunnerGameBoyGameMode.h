// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EndlessRunnerGameBoyGameMode.generated.h"

UCLASS(minimalapi)
class AEndlessRunnerGameBoyGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AEndlessRunnerGameBoyGameMode();

	UPROPERTY(BlueprintReadOnly)
	float TotalElapsedTime;

	void PlayerDed();

	UFUNCTION(BlueprintCallable)
	FString GetHighscore();
};



