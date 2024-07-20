// Fill out your copyright notice in the Description page of Project Settings.


#include "PacmanGameMode.h"
#include "PacmanPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Sound/SoundBase.h"
#include "EnemyPawn.h"


void APacmanGameMode::BeginPlay()
{
	Super::BeginPlay();
	FoodItems = 174;
}

void APacmanGameMode::UpdateFoodItems()
{
	FoodItems--;
	if (FoodItems <= 0) {
		OnEndGame.Broadcast(true);
	}
}

void APacmanGameMode::UpdateLives()
{
	Lives--;
	if (Lives <= 0) {
		if (GameLoseSound) {
			UGameplayStatics::PlaySound2D(this, GameLoseSound);
		}
		OnEndGame.Broadcast(false);
	}
}

void APacmanGameMode::UpdateScore(float ScoreToAdd)
{
	Score += ScoreToAdd;
	if (Score == 1350.0f) {
		AwardBonusLife();
	}
}

void APacmanGameMode::AwardBonusLife()
{
	Lives++;
	if (Up1Sound) {
		UGameplayStatics::PlaySound2D(this, Up1Sound);
	}
}

void APacmanGameMode::ResetEatenEnemyCount()
{
	EatenEnemyCount = 0;
}

void APacmanGameMode::EnemyEncounter(AActor* EnemyActor)
{
	if (Cast<AEnemyPawn>(EnemyActor)->GetCurrentState() == EEnemyStatus::Vulnerable) {

		EatenEnemyCount++;
		Cast<AEnemyPawn>(EnemyActor)->SetCurrentState(EEnemyStatus::Idle);

		if (EatEnemySound) {
			UGameplayStatics::PlaySound2D(this, EatEnemySound);
		}

		UpdateScore(200);
		
		if (Score == 1825.0f || EatenEnemyCount == 3) {
			AwardBonusLife();
		}
	}
	else if (Cast<AEnemyPawn>(EnemyActor)->GetCurrentState() == EEnemyStatus::Normal) {

		if (PacDeathSound) {
			UGameplayStatics::PlaySound2D(this, PacDeathSound);
		}
		UpdateLives();
		//Move player actor to home location
		UGameplayStatics::GetPlayerController(this, 0)->GetPawn()->SetActorLocation(FVector(-10, 880, 30));
		OnPlayerDeath.Broadcast();
	}
}

