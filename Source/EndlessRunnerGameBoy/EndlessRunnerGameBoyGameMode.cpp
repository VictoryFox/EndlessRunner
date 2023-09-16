// Copyright Epic Games, Inc. All Rights Reserved.

#include "EndlessRunnerGameBoyGameMode.h"
#include "EndlessRunnerGameBoyCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "FileHandler.h"
#include "Kismet/GameplayStatics.h"

AEndlessRunnerGameBoyGameMode::AEndlessRunnerGameBoyGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
	}
}

void AEndlessRunnerGameBoyGameMode::PlayerDed()
{
    int score = FMath::RoundToInt(TotalElapsedTime);
    bool bOutSuccess;
    FString OutMessageInfo;
    FString scoreString = FileHandler::ReadStringFromFile("C:/Temp/HighScore.txt", bOutSuccess, OutMessageInfo);
    if (!bOutSuccess)
    {
        GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, OutMessageInfo);
        FileHandler::WriteStringToFile("C:/Temp/HighScore.txt", FString::FromInt(score), bOutSuccess, OutMessageInfo);

        if (!bOutSuccess)
        {
            GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::White, OutMessageInfo);
        }
    }
    else
    {
        scoreString.Append(" ");
        scoreString.Append(FString::FromInt(score));

        FileHandler::WriteStringToFile("C:/Temp/HighScore.txt", scoreString, bOutSuccess, OutMessageInfo);

        if (!bOutSuccess)
        {
            GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::White, OutMessageInfo);
        }
    }

	UGameplayStatics::OpenLevel(GetWorld(), FName("MainMenu"));
}

FString AEndlessRunnerGameBoyGameMode::GetHighscore()
{
	bool bOutSuccess;
	FString OutMessageInfo;
	return FileHandler::ReadStringFromFile("C:/Temp/HighScore.txt", bOutSuccess, OutMessageInfo);
}
