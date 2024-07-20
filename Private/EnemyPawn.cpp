// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPawn.h"
#include "Components/SphereComponent.h"
#include "PacmanGameMode.h"



AEnemyPawn::AEnemyPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ABasePawn::PawnRoot->SetSphereRadius(170.0f);

	// Y -ve means upper part
	EscapeRoutes.Add(FVector(-400, -600, 30));
	EscapeRoutes.Add(FVector(400, -600, 30));
	EscapeRoutes.Add(FVector(-780, -1400, 30));
	EscapeRoutes.Add(FVector(780, -1400, 30));
	EscapeRoutes.Add(FVector(-230, -1800, 30));
	EscapeRoutes.Add(FVector(230, -1800, 30));



	// Y +ve means lower part
	EscapeRoutes2.Add(FVector(-400, 600, 30));
	EscapeRoutes2.Add(FVector(400, 600, 30));
	EscapeRoutes2.Add(FVector(-780, 1400, 30));
	EscapeRoutes2.Add(FVector(780, 1400, 30));
	EscapeRoutes2.Add(FVector(-230, 1800, 30));
	EscapeRoutes2.Add(FVector(230, 1800, 30));

}

APawn* AEnemyPawn::GetPacmanPawn()
{
	auto Pawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	return Pawn;
}


// Called when the game starts or when spawned
void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();
	EnemyStatus = EEnemyStatus::Idle;

	if (GetPacmanPawn() == nullptr) { return; }

	ABasePawn::GetGameMode()->OnPlayerDeath.AddUniqueDynamic(this, &AEnemyPawn::OnPacmanDeadState);
	ABasePawn::GetGameMode()->OnPlayerPowerUp.AddUniqueDynamic(this, &AEnemyPawn::OnPacmanSuperState);
}

// Called every frame
void AEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


float AEnemyPawn::GetActivationDelay()
{
	return ActivationDelay;
}

FVector AEnemyPawn::GetHomeLocation()
{
	return HomeLocation;
}

EEnemyStatus AEnemyPawn::GetCurrentState()
{
	return EnemyStatus;
}

void AEnemyPawn::SetCurrentState(EEnemyStatus State)
{
	EnemyStatus = State;

}

FVector AEnemyPawn::GetCurrEscapeRoute()
{
	return CurrEscapeRoute;
}

 void AEnemyPawn::SetCurrEscapeRoute()
{
	int32 Choice = FMath::RandRange(0, 5);
	CurrEscapeRoute = EscapeRoutes[Choice];
}

 void AEnemyPawn::SetCurrEscapeRoute2()
 {
	 int32 Choice = FMath::RandRange(0, 5);
	 CurrEscapeRoute = EscapeRoutes2[Choice];
 }

 void AEnemyPawn::Vulnerable()
 {
	 SetCurrentState(EEnemyStatus::Idle);
	
 }

 void AEnemyPawn::Hunt()
 {
	 SetCurrentState(EEnemyStatus::Normal);
 }

 void AEnemyPawn::RetreatToTop()
 {
	 SetCurrentState(EEnemyStatus::Vulnerable);
	 SetCurrEscapeRoute(); //escape route1 is above
 }

 void AEnemyPawn::RetreatToBelow()
 {
	 SetCurrentState(EEnemyStatus::Vulnerable);
	 SetCurrEscapeRoute2(); //escape route2 is below
 }

 void AEnemyPawn::OnPacmanSuperState()
 {
	 if (GetPacmanPawn() == nullptr) { return; }

	 auto PlayerLocation = GetPacmanPawn()->GetActorLocation().Y;

	 if (PlayerLocation > 0) {
		 //Player is Below
		 RetreatToTop();
	 }
	 else if (PlayerLocation < 0) {
		 //Player is Above
		 RetreatToBelow();
	 }

	 //change state back to normal 
	 FTimerHandle UnUsedHandle;
	 GetWorldTimerManager().SetTimer(UnUsedHandle, this, &AEnemyPawn::Hunt, 4.0f, false);
 }

 void AEnemyPawn::OnPacmanDeadState()
 {
	SetCurrentState(EEnemyStatus::Idle);
 }



