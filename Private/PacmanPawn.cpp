// Fill out your copyright notice in the Description page of Project Settings.


#include "PacmanPawn.h"
#include "Components/SphereComponent.h"
#include "EnemyPawn.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Sound/SoundCue.h"
#include "Sound/SoundBase.h"
#include "PacmanGameMode.h"


// Sets default values
APacmanPawn::APacmanPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ABasePawn::PawnRoot->SetSphereRadius(180.0f);
	ABasePawn::PawnMovement->MaxSpeed = 800.0f;
	ABasePawn::PawnMovement->Acceleration = 800.0f;
}


void APacmanPawn::GetAllFoodActors()
{
	
	FoodItems = 174;
	/*
		might need to shift in GM BP
	*/
	
}

// Called when the game starts or when spawned
void APacmanPawn::BeginPlay()
{
	Super::BeginPlay();
	ABasePawn::PawnRoot->OnComponentBeginOverlap.AddDynamic(this, &APacmanPawn::OnOverlap);

	if (StartSound) {
		UGameplayStatics::PlaySoundAtLocation(this, StartSound, GetActorLocation());
	}

	//set frozen false here with timer
	FTimerHandle UnUsedHandle;
	GetWorldTimerManager().SetTimer(UnUsedHandle, this, &APacmanPawn::ActivatePacman, 3.5f, false);

	GetAllFoodActors();
	MoveDirection = GetActorForwardVector();

}

// Called every frame
void APacmanPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//only move if not frozen
	if (!bFrozenState) {
		
		AddMovementInput(MoveDirection);
	}

}

// Called to bind functionality to input
void APacmanPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APacmanPawn::UpdateFoodItems()
{
	FoodItems--;
	if (FoodItems <= 0) {	
		ABasePawn::GetGameMode()->OnEndGame.Broadcast(true);
	}
}

void APacmanPawn::UpdateLives()
{
	Lives--;
	if (Lives <= 0) {
		bFrozenState = true;
		if (GameLoseSound) {
			UGameplayStatics::PlaySoundAtLocation(this, GameLoseSound, GetActorLocation());
		}
		ABasePawn::GetGameMode()->OnEndGame.Broadcast(false);
	}
}

void APacmanPawn::SetSpeedBack()
{
	ABasePawn::PawnMovement->MaxSpeed = 800.0f;
	ABasePawn::PawnMovement->Acceleration = 800.0f;
	EatenEnemyCount = 0;
}

void APacmanPawn::ActivatePacman()
{
	bFrozenState = false;
}

void APacmanPawn::AwardBonusLife()
{
	Lives++;
	if (Up1Sound) {
		UGameplayStatics::PlaySound2D(this, Up1Sound);
	}
}

bool APacmanPawn::GetFrozenStatus()
{
	return bFrozenState;
}

void APacmanPawn::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor->ActorHasTag("SuperFood")) {
		
		Score += 50;
		if (ConsumeSoundSuper) {

			UGameplayStatics::PlaySound2D(this, ConsumeSoundSuper);
		}
		UpdateFoodItems();

		if (Score == 1350.0f) {
			AwardBonusLife();
		}

		OtherActor->Destroy();

		ABasePawn::PawnMovement->MaxSpeed = 2000.0f;
		ABasePawn::PawnMovement->Acceleration = 2000.0f;

		
		ABasePawn::GetGameMode()->OnPlayerPowerUp.Broadcast();

		FTimerHandle UnUsedHandle;
		GetWorldTimerManager().SetTimer(UnUsedHandle, this, &APacmanPawn::SetSpeedBack, 3.0f, false);

	}

	if (OtherActor->ActorHasTag("NormalFood")) {
		
		Score += 5;

		if (ConsumeSoundNormal) {
			UGameplayStatics::PlaySound2D(this, ConsumeSoundNormal);
		}
		UpdateFoodItems();

		if (Score == 1350.0f) {
			AwardBonusLife();
		}

		OtherActor->Destroy();
	}

	
	if (OtherActor->ActorHasTag("Enemy")) {
		if (Cast<AEnemyPawn>(OtherActor)->GetCurrentState() == EEnemyStatus::Vulnerable) {

			EatenEnemyCount++;
			Cast<AEnemyPawn>(OtherActor)->SetCurrentState(EEnemyStatus::Idle);

			if (EatEnemySound) {
				UGameplayStatics::PlaySound2D(this, EatEnemySound);
			}

			Score += 200;

			if (Score == 1825.0f || EatenEnemyCount == 3) {
				AwardBonusLife();
			}
		}
		else if (Cast<AEnemyPawn>(OtherActor)->GetCurrentState() == EEnemyStatus::Normal) {
			
				if (PacDeathSound) {
					UGameplayStatics::PlaySound2D(this, PacDeathSound);
				}
				UpdateLives();
				//Move player actor to home location
				SetActorLocation(FVector(-10, 880, 30));
				ABasePawn::GetGameMode()->OnPlayerDeath.Broadcast();
		}
			
	}
		
}




