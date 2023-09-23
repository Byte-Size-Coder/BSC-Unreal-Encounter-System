// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Encounter.h"
#include "EncounterTrigger.generated.h"

UCLASS()
class BSC_ENCOUNTERSYSTEM_API AEncounterTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEncounterTrigger();

	void SetOwningEncounter(AEncounter* Encounter);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess=true)) 
	class USphereComponent* TriggerCollider;

	AEncounter* OwningEncounter;

	UPROPERTY(EditAnywhere)
	EEncounterPhase TriggerPhase;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AActor>> TriggerClasses;

	UFUNCTION()
	void OnComponentOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);
};
