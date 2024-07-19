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

	void UpdateFoodItems();
	void UpdateLives();
	void SetSpeedBack();
	void ActivatePacman();
	void AwardBonusLife();

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

	void GetAllFoodActors();

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:

	FVector MoveDirection;

protected:

	int32 FoodItems;

	UPROPERTY(EditAnywhere)
	class USoundCue* ConsumeSoundNormal;
	UPROPERTY(EditAnywhere)
	class USoundCue* ConsumeSoundSuper;
	UPROPERTY(EditAnywhere)
	class USoundCue* Up1Sound;
	UPROPERTY(EditAnywhere)
	class USoundCue* PacDeathSound;
	UPROPERTY(EditAnywhere)
	class USoundCue* EatEnemySound;

	UPROPERTY(EditAnywhere)
	class USoundBase* StartSound;

	UPROPERTY(EditAnywhere)
	class USoundBase* GameLoseSound;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Lives = 2.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Score = 0.0f;

	float EatenEnemyCount = 0;

	bool bFrozenState = true;
};
