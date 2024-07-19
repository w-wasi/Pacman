// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UFloatingPawnMovement;
class APacmanGameMode;

UCLASS()
class PACMANOWN_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();
	
protected:

	APacmanGameMode* GetGameMode();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:

	UPROPERTY(EditAnywhere)
	UFloatingPawnMovement* PawnMovement = nullptr;

	UPROPERTY(EditAnywhere)
	USphereComponent* PawnRoot = nullptr;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* PawnBase = nullptr;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* PawnMesh = nullptr;

};
