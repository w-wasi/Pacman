// Fill out your copyright notice in the Description page of Project Settings.


#include "PacmanPlayerController.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "PacmanPawn.h"
#include "PacmanGameMode.h"



APacmanPawn* APacmanPlayerController::GetPacmanPawn()
{
	return Cast<APacmanPawn>(GetPawn());
}

void APacmanPlayerController::BeginPlay()
{
	TArray<AActor*> CameraActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),ACameraActor::StaticClass(),CameraActors);
	SetViewTargetWithBlend(CameraActors[0], 1.0f);

	GetPacmanPawn()->GetGameMode()->OnEndGame.AddUniqueDynamic(this, &APacmanPlayerController::EndGame);
}

void APacmanPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Up", IE_Pressed, this, &APacmanPlayerController::MoveUp);
	InputComponent->BindAction("Down", IE_Pressed, this, &APacmanPlayerController::MoveDown);
	InputComponent->BindAction("Left", IE_Pressed, this, &APacmanPlayerController::MoveLeft);
	InputComponent->BindAction("Right", IE_Pressed, this, &APacmanPlayerController::MoveRight);

	InputComponent->BindAction("Quit", IE_Pressed, this, &APacmanPlayerController::QuitGame);
	InputComponent->BindAction("Restart", IE_Pressed, this, &APacmanPlayerController::RestartGame);
}



void APacmanPlayerController::MoveUp()
{
	if (GetPacmanPawn() && !GetPacmanPawn()->GetFrozenStatus()) {
		GetPacmanPawn()->MoveDirection = FVector::LeftVector;
		GetPacmanPawn()->SetActorRotation(GetPacmanPawn()->MoveDirection.Rotation());
	}
}

void APacmanPlayerController::MoveDown()
{
	if (GetPacmanPawn() && !GetPacmanPawn()->GetFrozenStatus()) {
		GetPacmanPawn()->MoveDirection = FVector::RightVector;
		GetPacmanPawn()->SetActorRotation(GetPacmanPawn()->MoveDirection.Rotation());
	}
}

void APacmanPlayerController::MoveLeft()
{
	if (GetPacmanPawn() && !GetPacmanPawn()->GetFrozenStatus()) {
		GetPacmanPawn()->MoveDirection = FVector::BackwardVector;
		GetPacmanPawn()->SetActorRotation(GetPacmanPawn()->MoveDirection.Rotation());
	}
}

void APacmanPlayerController::MoveRight()
{
	if (GetPacmanPawn() && !GetPacmanPawn()->GetFrozenStatus()) {
		GetPacmanPawn()->MoveDirection = FVector::ForwardVector;
		GetPacmanPawn()->SetActorRotation(GetPacmanPawn()->MoveDirection.Rotation());
	}
}

void APacmanPlayerController::QuitGame()
{
	if (GetPacmanPawn() != nullptr) {
		GetPacmanPawn()->GameQuit();
	}
}

void APacmanPlayerController::RestartGame()
{
	if (GetPacmanPawn() != nullptr) {
		GetPacmanPawn()->GameReset();
	}
}


void APacmanPlayerController::EndGame(bool bIsPlayerWinner)
{
	if (bIsPlayerWinner) {

		GameHasEnded(GetPawn(), bIsPlayerWinner);
	}
	else {
		GameHasEnded(GetPawn(), bIsPlayerWinner);
	}
}

void APacmanPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	if (bIsWinner) {
		EndGameWin();
	}
	else {
		EndGameLose();
	}
}

