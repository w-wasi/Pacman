// Fill out your copyright notice in the Description page of Project Settings.


#include "PacmanPawn.h"
#include "Components/SphereComponent.h"
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

void APacmanPawn::SetSpeedBack()
{
	ABasePawn::PawnMovement->MaxSpeed = 800.0f;
	ABasePawn::PawnMovement->Acceleration = 800.0f;

	ABasePawn::GetGameMode()->ResetEatenEnemyCount();
}

void APacmanPawn::ActivatePacman()
{
	bFrozenState = false;
}


bool APacmanPawn::GetFrozenStatus()
{
	return bFrozenState;
}


void APacmanPawn::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor->ActorHasTag("SuperFood")) {
	
		if (ConsumeSoundSuper) {

			UGameplayStatics::PlaySound2D(this, ConsumeSoundSuper);
		}
		OtherActor->Destroy();

		ABasePawn::GetGameMode()->UpdateScore(50);
		ABasePawn::GetGameMode()->UpdateFoodItems();

		ABasePawn::PawnMovement->MaxSpeed = 2000.0f;
		ABasePawn::PawnMovement->Acceleration = 2000.0f;

		
		ABasePawn::GetGameMode()->OnPlayerPowerUp.Broadcast();

		FTimerHandle UnUsedHandle;
		GetWorldTimerManager().SetTimer(UnUsedHandle, this, &APacmanPawn::SetSpeedBack, 3.0f, false);

	}

	if (OtherActor->ActorHasTag("NormalFood")) {
		
		if (ConsumeSoundNormal) {
			UGameplayStatics::PlaySound2D(this, ConsumeSoundNormal);
		}
		OtherActor->Destroy();

		ABasePawn::GetGameMode()->UpdateScore(5);
		ABasePawn::GetGameMode()->UpdateFoodItems();
	}

	
	if (OtherActor->ActorHasTag("Enemy")) {

		ABasePawn::GetGameMode()->EnemyEncounter(OtherActor);
	
	}
		
}




