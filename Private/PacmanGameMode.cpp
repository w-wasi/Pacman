// Fill out your copyright notice in the Description page of Project Settings.


#include "PacmanGameMode.h"
#include "PacmanPlayerController.h"
#include "Kismet/GameplayStatics.h"

void APacmanGameMode::BeginPlay()
{
	Super::BeginPlay();
	OnEndGame.AddUniqueDynamic(this, &APacmanGameMode::EndGame);
}

void APacmanGameMode::EndGame(bool bIsPlayerWinner)
{
	auto PLC = Cast<APacmanPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	if (bIsPlayerWinner) {
		
		PLC->GameHasEnded(PLC->GetPawn(), bIsPlayerWinner);
	}
	else {
		PLC->GameHasEnded(PLC->GetPawn(), bIsPlayerWinner);
	}
}
