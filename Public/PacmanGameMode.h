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

protected:

	virtual void BeginPlay() override;

public:
	
	FPacmanState OnPlayerPowerUp;
	FPacmanState OnPlayerDeath;
	
	FPacmanGameState OnEndGame;

	void UpdateFoodItems();
	void UpdateLives();
	void UpdateScore(float ScoreToAdd);
	void AwardBonusLife();
	void EnemyEncounter(AActor* EnemyActor);
	void ResetEatenEnemyCount();


protected:

	int32 FoodItems = 0;
	float EatenEnemyCount = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Lives = 2.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Score = 0.0f;


	UPROPERTY(EditAnywhere)
	class USoundCue* Up1Sound;
	UPROPERTY(EditAnywhere)
	class USoundBase* GameLoseSound;
	UPROPERTY(EditAnywhere)
	class USoundCue* EatEnemySound;
	UPROPERTY(EditAnywhere)
	class USoundCue* PacDeathSound;
	
};
