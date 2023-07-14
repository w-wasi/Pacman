// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "EnemyPawn.generated.h"

/**
 * 
 */

class APacmanPawn;

UENUM()
enum class EEnemyStatus : uint8
{
	Idle,		//OutOfAmmo		needs to be added	color: GREY
	Normal,		//OutOfRange	needs to be renamed	color: RED
	Vulnerable,	//Reloading		needs to be renamed	color: YELLOW
	Eaten		//ValidTarget	needs to be renamed	color: GREEN	
};

UCLASS()
class PACMANOWN_API AEnemyPawn : public ABasePawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	EEnemyStatus EnemyStatus = EEnemyStatus::Idle;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Setup)
	float ActivationDelay = 0.0f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Setup)
	FVector HomeLocation = FVector::ZeroVector;

	FVector CurrEscapeRoute;

	TArray<FVector> EscapeRoutes;
	TArray<FVector> EscapeRoutes2;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetCurrentState(EEnemyStatus State);
	EEnemyStatus GetCurrentState();
	
	float GetActivationDelay();
	FVector GetHomeLocation();


	FVector GetCurrEscapeRoute();
	void SetCurrEscapeRoute();
	void SetCurrEscapeRoute2();

	//	FVector CurrEscapeRoute2;

	void Vulnerable();
	void Hunt();
	
	void RetreatToTop();
	void RetreatToBelow();

	APacmanPawn* GetPacmanPawn();


private:
	UFUNCTION()
		void OnPacmanSuperState();

	UFUNCTION()
		void OnPacmanDeadState();
};
