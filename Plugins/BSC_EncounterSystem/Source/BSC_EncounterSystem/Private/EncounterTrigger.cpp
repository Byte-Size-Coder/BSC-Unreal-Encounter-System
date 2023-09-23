// Fill out your copyright notice in the Description page of Project Settings.


#include "EncounterTrigger.h"
#include "Components/SphereComponent.h"

// Sets default values
AEncounterTrigger::AEncounterTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TriggerCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));
	RootComponent = TriggerCollider;
	TriggerCollider->SetGenerateOverlapEvents(true);

	TriggerCollider->OnComponentBeginOverlap.AddDynamic(this, &AEncounterTrigger::OnComponentOverlap);
}

void AEncounterTrigger::SetOwningEncounter(AEncounter* Encounter)
{
	OwningEncounter = Encounter;
}

// Called when the game starts or when spawned
void AEncounterTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEncounterTrigger::OnComponentOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Blue,
			FString(TEXT("ENTERED TRIGGER"))
		);

	for (auto Class : TriggerClasses)
	{
		if (OtherActor->GetClass() == Class)
		{
			OwningEncounter->OnTrigger(TriggerPhase);
			TriggerCollider->SetGenerateOverlapEvents(false);
		}
	}
}                                      

