// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bot.generated.h"

UCLASS()
class ENDLESSRUNNERGAMEBOY_API ABot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABot();

	int Health = 3;

	void DamageOnHit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnyWhere, meta = (MakeEditWidget = true))
		TArray<FVector> LanePositions;

	TArray<FVector> LaneWorldPositions;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
