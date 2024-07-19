// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleportActor.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SceneComponent.h"

// Sets default values
ATeleportActor::ATeleportActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ATeleportActor::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &ATeleportActor::OnOverlap);
	
}

// Called every frame
void ATeleportActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATeleportActor::TeleportToTarget(AActor* Actor)
{
	if (TeleportSound != nullptr) {
		UGameplayStatics::PlaySound2D(this, TeleportSound);
	}

	auto TargetSpawn = Cast<USceneComponent>(Target->GetDefaultSubobjectByName("Spawn"));

	if (TargetSpawn != nullptr) {
		Actor->SetActorLocation(TargetSpawn->GetComponentLocation());
	}

}

void ATeleportActor::OnOverlap(AActor* ThisActor, AActor* OtherActor)
{
	if (OtherActor->ActorHasTag("Pacman")) {

		FTimerDelegate SpawnPacman;
		SpawnPacman.BindUFunction(this, FName("TeleportToTarget"), OtherActor);
		GetWorldTimerManager().SetTimerForNextTick(SpawnPacman);
	}
}

