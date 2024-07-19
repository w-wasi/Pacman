// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "EnemyPawn.generated.h"

/**
 * 
 */



UENUM()
enum class EEnemyStatus : uint8
{
	Idle,		
	Normal,		
	Vulnerable,	
	Eaten			
};

UCLASS()
class PACMANOWN_API AEnemyPawn : public ABasePawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyPawn();

	APawn* GetPacmanPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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


	void Vulnerable();
	void Hunt();
	
	void RetreatToTop();
	void RetreatToBelow();

private:

	UFUNCTION()
		void OnPacmanSuperState();

	UFUNCTION()
		void OnPacmanDeadState();

protected:

	EEnemyStatus EnemyStatus = EEnemyStatus::Idle;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Setup)
	float ActivationDelay = 0.0f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Setup)
	FVector HomeLocation = FVector::ZeroVector;

	FVector CurrEscapeRoute;

	TArray<FVector> EscapeRoutes;
	TArray<FVector> EscapeRoutes2;
};
