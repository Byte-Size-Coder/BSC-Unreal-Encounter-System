// Fill out your copyright notice in the Description page of Project Settings.


#include "Encounter.h"

// Sets default values
AEncounter::AEncounter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEncounter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEncounter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEncounter::EncounterIntroBegin()
{
	EncounterOnIntroBegin.Broadcast(Id);
}

void AEncounter::EncounterIntroEnd()
{
	EncounterOnIntroEnd.Broadcast(Id);
}

void AEncounter::EncounterStart()
{
	EncounterOnStartBegin.Broadcast(Id);
}

void AEncounter::EncounterEndSucceed()
{
	EncounterOnEncounterEndSucceed.Broadcast(Id);
}

void AEncounter::EncounterEndFailed()
{
	EncounterOnEncounterEndFailed.Broadcast(Id);
}

void AEncounter::UpdateObjectiveSucceed()
{
	EncounterOnUpdateObjectiveSucceed.Broadcast(Id);
}

void AEncounter::UpdateObjectiveFailed()
{
	EncounterOnUpdateObjectiveFailed.Broadcast(Id);
}

void AEncounter::StartSucceed()
{
	EncounterOnSucceedBegin.Broadcast(Id);
}

void AEncounter::StartFailed()
{
	EncounterOnFailedBegin.Broadcast(Id);
}

void AEncounter::EndSucceed()
{
	EncounterOnSucceedEnd.Broadcast(Id);
}

void AEncounter::EndFailed()
{
	EncounterOnFailedEnd.Broadcast(Id);
}
