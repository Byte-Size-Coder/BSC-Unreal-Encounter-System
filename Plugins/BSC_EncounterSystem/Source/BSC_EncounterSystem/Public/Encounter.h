// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Encounter.generated.h"

class AEncounterTrigger;

UENUM(BlueprintType)
enum class EEncounterPhase : uint8
{
    READY UMETA(DisplayName = "Ready"),
	INTRO UMETA(DisplayName = "Intro"),
	START UMETA(DisplayName = "Start"),
	END UMETA(DisplayName = "End"),
	INACTIVE UMETA(DisplayName = "Inactive")
};

UENUM(BlueprintType)
enum class EEncounterType : uint8
{
    MAIN UMETA(DisplayName = "Main"),
	OPTIONAL UMETA(DisplayName = "Optional"),
};

USTRUCT(BlueprintType)
struct FTriggerInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AEncounterTrigger* Trigger;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEncounterPhase TriggerPhase;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEncounterOnIntroBegin, AEncounter*, Encounter);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEncounterOnIntroEnd, AEncounter*, Encounter);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEncounterOnStartBegin, AEncounter*, Encounter);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEncounterOnUpdateObjectiveSucceed, AEncounter*, Encounter);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEncounterOnUpdateObjectiveFailed, AEncounter*, Encounter);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEncounterOnSucceedBegin, AEncounter*, Encounter);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEncounterOnSucceedEnd, AEncounter*, Encounter);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEncounterOnFailedBegin, AEncounter*, Encounter);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEncounterOnFailedEnd, AEncounter*, Encounter);


UCLASS()
class BSC_ENCOUNTERSYSTEM_API AEncounter : public AActor
{
	GENERATED_BODY()
	
public:	
	AEncounter();

	UFUNCTION(BlueprintCallable)
	void EncounterIntroBegin();
	UFUNCTION(BlueprintCallable)
	void EncounterIntroEnd();

	UFUNCTION(BlueprintCallable)
	void EncounterStart();

	UFUNCTION(BlueprintCallable)
	void UpdateObjectiveSucceed();
	UFUNCTION(BlueprintCallable)
	void UpdateObjectiveFailed();

	UFUNCTION(BlueprintCallable)
	void StartSucceed();
	UFUNCTION(BlueprintCallable)
	void StartFailed();
	
	UFUNCTION(BlueprintCallable)
	void EndSucceed();
	UFUNCTION(BlueprintCallable)
	void EndFailed();

	void OnTrigger(EEncounterPhase TriggerPhase);

	UPROPERTY(BlueprintReadWrite)
	int32 ObjectivesSucceeded;
	UPROPERTY(BlueprintReadWrite)
	int32 ObjectivesFailed;

	UPROPERTY(BlueprintReadWrite)
	EEncounterPhase CurrentPhase;

	UPROPERTY(BlueprintAssignable)
	FEncounterOnIntroBegin EncounterOnIntroBegin;

	UPROPERTY(BlueprintAssignable)
	FEncounterOnIntroEnd EncounterOnIntroEnd;

	UPROPERTY(BlueprintAssignable)
	FEncounterOnStartBegin EncounterOnStartBegin;

	UPROPERTY(BlueprintAssignable)
	FEncounterOnUpdateObjectiveSucceed EncounterOnUpdateObjectiveSucceed;

	UPROPERTY(BlueprintAssignable)
	FEncounterOnUpdateObjectiveFailed EncounterOnUpdateObjectiveFailed;

	UPROPERTY(BlueprintAssignable)
	FEncounterOnSucceedBegin EncounterOnSucceedBegin;

	UPROPERTY(BlueprintAssignable)
	FEncounterOnSucceedEnd EncounterOnSucceedEnd;

	UPROPERTY(BlueprintAssignable)
	FEncounterOnFailedBegin EncounterOnFailedBegin;

	UPROPERTY(BlueprintAssignable)
	FEncounterOnFailedEnd EncounterOnFailedEnd;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Encounter Properties")
	TArray<AEncounterTrigger*> triggers;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Encounter Properties")
	FString Id;

	UPROPERTY(EditAnywhere, Category = "Encounter Properties")
	EEncounterType Type;

	UPROPERTY(EditAnywhere, Category = "Encounter Properties")
	int32 TotalObjectives;

	UPROPERTY(EditAnywhere, Category = "Encounter Properties")
	int32 ObjectivesCompleteRequirement;

	UPROPERTY(EditAnywhere, Category = "Encounter Properties")
	int32 ObjectivesFailedThreshold;

	UPROPERTY(EditAnywhere, Category = "Triggers")
	TSubclassOf<AEncounterTrigger> TriggerClass;

	//UFUNCTION(BlueprintCallable, CallInEditor,  Category = "Triggers")
	//void AddTrigger();
};
