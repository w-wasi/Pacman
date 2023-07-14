// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PacmanPlayerController.generated.h"
/**
 * 
 */

class APacmanPawn;


UCLASS()
class PACMANOWN_API APacmanPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	void SetupInputComponent() override;

	UFUNCTION(BlueprintCallable)
	APacmanPawn* GetPacmanPawn();

	TArray<AActor*> Enemies;

public:
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

	void QuitGame();
	void RestartGame();

};
