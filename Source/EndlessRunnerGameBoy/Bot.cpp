// Fill out your copyright notice in the Description page of Project Settings.


#include "Bot.h"

// Sets default values
ABot::ABot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ABot::DamageOnHit()
{
	Health--;

	if (Health <= 0) 
	{
		Destroy();
	}
}

// Called when the game starts or when spawned
void ABot::BeginPlay()
{
	Super::BeginPlay();
	
	FTransform Transform = GetActorTransform();

	LaneWorldPositions.Empty();

	for (int i = 0; i < LanePositions.Num(); i++)
	{
		LaneWorldPositions.Add(Transform.TransformPosition(LanePositions[i]));
	}
}

// Called every frame
void ABot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<FVector> FreeLanes;
	FHitResult HitResult;
	FVector Start = GetActorLocation() + FVector::UpVector * 50;
	FVector End = Start + FVector::ForwardVector * 300;

	bool Avoid = GetWorld()->LineTraceSingleByObjectType(HitResult, Start, End, ECC_WorldStatic);

	if (!Avoid)
		return;

	for (int i = 0; i < LaneWorldPositions.Num(); i++)
	{
		Start = LaneWorldPositions[i] + FVector::UpVector * 50;
		End = FVector::ForwardVector * 300 + Start;

		DrawDebugLine(GetWorld(), Start, End, FColor::Red);

		if (GetWorld()->LineTraceSingleByObjectType(HitResult, Start, End, ECC_WorldStatic))
		{
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::White, "Hit");
		}
		else 
		{
			FreeLanes.Add(Start);
		}
	}

	SetActorLocation(FreeLanes[FMath::RandRange(0, FreeLanes.Num() - 1)]);
}

