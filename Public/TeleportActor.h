// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TeleportActor.generated.h"

UCLASS()
class PACMANOWN_API ATeleportActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATeleportActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void TeleportToTarget(AActor* Actor);

	UFUNCTION()
	void OnOverlap(AActor* ThisActor, AActor* OtherActor);

	UPROPERTY(EditAnywhere)
	class USoundCue* TeleportSound;

	//shoild be editinstanceonly
	UPROPERTY(EditAnywhere)
	ATeleportActor* Target = nullptr;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
