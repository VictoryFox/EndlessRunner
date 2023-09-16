// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleSpawner.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AObstacleSpawner::AObstacleSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AObstacleSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	Player = Cast<AEndlessRunnerGameBoyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	GameMode = Cast<AEndlessRunnerGameBoyGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

void AObstacleSpawner::MoveObstacles()
{
	for (int i = 0; i < SpawnedObstacles.Num(); i++)
	{
		AObstacle* Obstacle = SpawnedObstacles[i];
		Obstacle->AddActorWorldOffset(FVector::BackwardVector * ObstacleSpeed * GameMode->TotalElapsedTime / 10.f);

		if (FVector::Distance(Obstacle->GetActorLocation(), GetActorLocation()) > 5000)
		{
			SpawnedObstacles.Remove(Obstacle);

			Obstacle->Destroy();
			return;
		}

		if (IsValid(Player)) 
		{
			FVector PlayerLocation = Player->GetActorLocation();
			FVector ObstacleLocation = Obstacle->GetActorLocation();

			// Ran past obstacle
			if (ObstacleLocation.X < PlayerLocation.X && !Obstacle->HasPassedPlayer)
			{
				Obstacle->HasPassedPlayer = true;

				if (FMath::RandRange(0.f, 1.f) <= .20f && IsValid(LastObstacle))
				{
					SpawnedObstacles.Remove(LastObstacle);

					LastObstacle->Destroy();
				}
			}

			if (FVector::Distance(ObstacleLocation, PlayerLocation) <= 150.f)
			{
				Player->DamageOnHit();
			
				SpawnedObstacles.Remove(Obstacle);
			
				Obstacle->Destroy();
				return;
			}
		}

		if (IsValid(Bot)) 
		{
			FVector BotLocation = Bot->GetActorLocation();
			FVector ObstacleLocation = Obstacle->GetActorLocation();

			// Ran past obstacle
			if (ObstacleLocation.X < BotLocation.X && !Obstacle->HasPassedBot) 
			{
				Obstacle->HasPassedBot = true;

				if (FMath::RandRange(0.f, 1.f) <= .20f && IsValid(LastObstacle))
				{
					SpawnedObstacles.Remove(LastObstacle);

					LastObstacle->Destroy();
				}
			}

			if (FVector::Distance(ObstacleLocation, BotLocation) <= 150.f)
			{
				SpawnedObstacles.Remove(Obstacle);
			
				Obstacle->Destroy();
			
				Bot->DamageOnHit();
				return;
			}

		}
	}
}

// Called every frame
void AObstacleSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveObstacles();
	if (IsValid(GameMode))
	{
		GameMode->TotalElapsedTime += DeltaTime;
	}

	ElapsedTime += DeltaTime;

	if (ElapsedTime >= SpawnFrequency)
	{
		SpawnFrequency = FMath::RandRange(.8f, 2.5f);
		int SpawnIndex = FMath::RandRange(0, SpawnPositions.Num() - 1);

		FVector SpawnPosition = SpawnPositions[SpawnIndex];

		AObstacle* Obstacle = GetWorld()->SpawnActor<AObstacle>(ObstacleBaseClass);

		Obstacle->SetActorLocation(SpawnPosition);

		SpawnedObstacles.Add(Obstacle);

		ElapsedTime = 0;

		LastObstacle = Obstacle;
	}


}

