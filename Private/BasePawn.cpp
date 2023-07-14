// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnRoot = CreateDefaultSubobject<USphereComponent>(FName("Sphere Mesh"));
	SetRootComponent(PawnRoot);
	
	PawnBase = CreateDefaultSubobject<UStaticMeshComponent>(FName("Actor Base"));
	PawnBase->SetupAttachment(RootComponent);
	
	PawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Actor Mesh"));
	PawnMesh->SetupAttachment(PawnBase);

	PawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(FName("Pawn Movement"));


}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

