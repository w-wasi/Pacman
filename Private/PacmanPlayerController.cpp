// Fill out your copyright notice in the Description page of Project Settings.


#include "PacmanPlayerController.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "PacmanPawn.h"



APacmanPawn* APacmanPlayerController::GetPacmanPawn()
{
	return Cast<APacmanPawn>(GetPawn());
}

void APacmanPlayerController::BeginPlay()
{
	TArray<AActor*> CameraActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),ACameraActor::StaticClass(),CameraActors);

	SetViewTargetWithBlend(CameraActors[0], 1.0f);

	
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
	if (GetPacmanPawn() != nullptr && GetPacmanPawn()->GetFrozenStatus() == false) {
		GetPacmanPawn()->SetActorRotation(FRotator(0, 270, 0));
	}
}

void APacmanPlayerController::MoveDown()
{
	if (GetPacmanPawn() != nullptr && GetPacmanPawn()->GetFrozenStatus() == false) {
		GetPacmanPawn()->SetActorRotation(FRotator(0, 90, 0));
	}
}

void APacmanPlayerController::MoveLeft()
{
	if (GetPacmanPawn() != nullptr && GetPacmanPawn()->GetFrozenStatus() == false) {
		GetPacmanPawn()->SetActorRotation(FRotator(0, 180, 180));
	}
}

void APacmanPlayerController::MoveRight()
{
	if (GetPacmanPawn() != nullptr && GetPacmanPawn()->GetFrozenStatus() == false) {
		GetPacmanPawn()->SetActorRotation(FRotator(0, 0, 0));
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
