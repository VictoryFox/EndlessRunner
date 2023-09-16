// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Obstacle.h"
#include "Bot.h"
#include "EndlessRunnerGameBoyGameMode.h"
#include "EndlessRunnerGameBoyCharacter.h"
#include "ObstacleSpawner.generated.h"

UCLASS()
class ENDLESSRUNNERGAMEBOY_API AObstacleSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacleSpawner();

	UPROPERTY(EditAnywhere)
	TSubclassOf<AObstacle> ObstacleBaseClass;

	UPROPERTY(EditAnywhere, meta=(MakeEditWidget=true))
	TArray<FVector> SpawnPositions;

	UPROPERTY(EditAnywhere)
	float SpawnFrequency = 1.f;

	UPROPERTY(EditAnywhere)
	float ObstacleSpeed = 10.f;

	UPROPERTY(EditAnywhere)
	TArray<AObstacle*> SpawnedObstacles;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float ElapsedTime;

	void MoveObstacles();
	
	UPROPERTY()
	AEndlessRunnerGameBoyCharacter* Player;

	UPROPERTY(EditInstanceOnly)
	ABot* Bot;

	UPROPERTY()
	AEndlessRunnerGameBoyGameMode* GameMode;

	AObstacle* LastObstacle;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
