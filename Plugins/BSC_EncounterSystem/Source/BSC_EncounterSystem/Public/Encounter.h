// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Encounter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEncounterOnIntroBegin, FString, EncounterId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEncounterOnIntroEnd, FString, EncounterId);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEncounterOnStartBegin, FString, EncounterId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEncounterOnUpdateObjectiveSucceed, FString, EncounterId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEncounterOnUpdateObjectiveFailed, FString, EncounterId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEncounterOnEncounterEndSucceed, FString, EncounterId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEncounterOnEncounterEndFailed, FString, EncounterId);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEncounterOnSucceedBegin, FString, EncounterId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEncounterOnSucceedEnd, FString, EncounterId);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEncounterOnFailedBegin, FString, EncounterId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEncounterOnFailedEnd, FString, EncounterId);


UCLASS()
class BSC_ENCOUNTERSYSTEM_API AEncounter : public AActor
{
	GENERATED_BODY()
	
public:	
	AEncounter();
	virtual void Tick(float DeltaTime) override;

	void EncounterIntroBegin();
	void EncounterIntroEnd();

	void EncounterStart();
	void EncounterEndSucceed();
	void EncounterEndFailed();

	void UpdateObjectiveSucceed();
	void UpdateObjectiveFailed();

	void StartSucceed();
	void StartFailed();
	
	void EndSucceed();
	void EndFailed();

	FEncounterOnIntroBegin EncounterOnIntroBegin;
	FEncounterOnIntroEnd EncounterOnIntroEnd;
	FEncounterOnStartBegin EncounterOnStartBegin;
	FEncounterOnUpdateObjectiveSucceed EncounterOnUpdateObjectiveSucceed;
	FEncounterOnUpdateObjectiveFailed EncounterOnUpdateObjectiveFailed;
	FEncounterOnEncounterEndSucceed EncounterOnEncounterEndSucceed;
	FEncounterOnEncounterEndFailed EncounterOnEncounterEndFailed;
	FEncounterOnSucceedBegin EncounterOnSucceedBegin;
	FEncounterOnSucceedEnd EncounterOnSucceedEnd;
	FEncounterOnFailedBegin EncounterOnFailedBegin;
	FEncounterOnFailedEnd EncounterOnFailedEnd;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Encounter Properties")
	FString Id;

	UPROPERTY(EditAnywhere, Category = "Encounter Properties")
	int32 TotalObjectives;

	UPROPERTY(EditAnywhere, Category = "Encounter Properties")
	int32 ObjectivesCompleteRequirement;

	UPROPERTY(EditAnywhere, Category = "Encounter Properties")
	int32 ObjectivesFailedThreshold;

	int32 ObjectivesSucceeded;
	int32 ObjectivesFailed;

};
