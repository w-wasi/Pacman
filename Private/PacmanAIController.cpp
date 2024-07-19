// Fill out your copyright notice in the Description page of Project Settings.


#include "PacmanAIController.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyPawn.h"

APawn* APacmanAIController::GetPlayerPawn() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	return PlayerPawn;
}

AEnemyPawn* APacmanAIController::GetEnemyPawn() const
{
	
	auto EnemyPawn = Cast<AEnemyPawn>(GetPawn());
	return EnemyPawn;
}

void APacmanAIController::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle UnUsedHandle;
	GetWorldTimerManager().SetTimer(UnUsedHandle, this, &APacmanAIController::PossesPawn, 3.5f, false);
}



void APacmanAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bShouldPossesPawn) {

		if (GetEnemyPawn() == nullptr) { return; }

		// move to player
		if (GetEnemyPawn()->GetCurrentState() == EEnemyStatus::Normal) {
			Hunt();
		}
		else if (GetEnemyPawn()->GetCurrentState() == EEnemyStatus::Idle) {
			UpdateActivationState();
		}
		else if (GetEnemyPawn()->GetCurrentState() == EEnemyStatus::Eaten) {
			RetreatToHome();
		}
		else if (GetEnemyPawn()->GetCurrentState() == EEnemyStatus::Vulnerable) {
			Retreat();
		}
	}
}


void APacmanAIController::UpdateActivationState()
{
	if (GetEnemyPawn() == nullptr) { return; }

	auto Home = GetEnemyPawn()->GetHomeLocation();
	GetEnemyPawn()->SetActorLocation(Home);

	auto Activation = GetEnemyPawn()->GetActivationDelay();
	FTimerHandle UnUsedHandle;
	GetWorldTimerManager().SetTimer(UnUsedHandle, this, &APacmanAIController::Activate, Activation, false);
}

void APacmanAIController::Activate()
{
	if (GetEnemyPawn() == nullptr) { return; }
	GetEnemyPawn()->SetCurrentState(EEnemyStatus::Normal);
}

void APacmanAIController::Hunt()
{
	if (GetPlayerPawn() != nullptr) {

		MoveToActor(GetPlayerPawn(), 0.0f);
	}
}

void APacmanAIController::Retreat()
{
	if (GetEnemyPawn() == nullptr) { return; }

	auto DummyLocation = GetEnemyPawn()->GetCurrEscapeRoute();
	MoveToLocation(DummyLocation, 0.0f);
}

void APacmanAIController::RetreatToHome()
{
	if (GetEnemyPawn() == nullptr) { return; }

	//auto HomeLocation = FVector(-20, 70, 30);
	auto HomeLocation = GetEnemyPawn()->GetHomeLocation();
	MoveToLocation(HomeLocation, 0.0f);

}

void APacmanAIController::PossesPawn()
{
	bShouldPossesPawn = true;
}

