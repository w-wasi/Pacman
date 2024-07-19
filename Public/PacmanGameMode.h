// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PacmanGameMode.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPacmanState);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPacmanGameState, bool, flag);


UCLASS()
class PACMANOWN_API APacmanGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	
	FPacmanState OnPlayerPowerUp;
	FPacmanState OnPlayerDeath;

	FPacmanGameState OnEndGame;

protected:

	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void EndGame(bool bIsPlayerWinner);
	
};
