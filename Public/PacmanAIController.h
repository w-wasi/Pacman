// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PacmanAIController.generated.h"

/**
 * 
 */

class AEnemyPawn;

UCLASS()
class PACMANOWN_API APacmanAIController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	void UpdateActivationState();
	void Activate();
	void Hunt();
	void Retreat();
	void RetreatToHome();
	
	bool bShouldPossesPawn = false;

	void PossesPawn();

public:

	virtual void Tick(float DeltaTime) override;

	APawn* GetPlayerPawn() const;

	AEnemyPawn* GetEnemyPawn() const;
	
};
