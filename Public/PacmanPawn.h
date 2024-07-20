// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "PacmanPawn.generated.h"

/**
 * 
 */



UCLASS()
class PACMANOWN_API APacmanPawn : public ABasePawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APacmanPawn();

protected:

	void SetSpeedBack();
	void ActivatePacman();
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool GetFrozenStatus();

	UFUNCTION(BlueprintImplementableEvent, Category = "Ending  Setup")
	void GameReset();

	UFUNCTION(BlueprintImplementableEvent, Category = "Ending  Setup")
	void GameQuit();

	
private:

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:

	FVector MoveDirection;

protected:

	UPROPERTY(EditAnywhere)
	class USoundCue* ConsumeSoundNormal;
	UPROPERTY(EditAnywhere)
	class USoundCue* ConsumeSoundSuper;
	
	UPROPERTY(EditAnywhere)
	class USoundBase* StartSound;

	bool bFrozenState = true;

	FString CurrEnemyState;
};
