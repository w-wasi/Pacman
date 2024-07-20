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

	UFUNCTION(BlueprintImplementableEvent, Category = "Ending Setup")
	void EndGameWin();

	UFUNCTION(BlueprintImplementableEvent, Category = "Ending  Setup")
	void EndGameLose();

	UFUNCTION()
	void EndGame(bool bIsPlayerWinner);

public:
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

	void QuitGame();
	void RestartGame();

	

	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

protected:

	TArray<AActor*> Enemies;

};
