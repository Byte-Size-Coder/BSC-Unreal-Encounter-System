// Fill out your copyright notice in the Description page of Project Settings.


#include "Encounter.h"
#include "EncounterTrigger.h"

AEncounter::AEncounter()
{
	PrimaryActorTick.bCanEverTick = false;

	// Set starting values
	CurrentPhase = EEncounterPhase::READY;
	ObjectivesSucceeded = 0;
	ObjectivesFailed = 0;
}

// Called when the game starts or when spawned
void AEncounter::BeginPlay()
{
	Super::BeginPlay();
		// Set starting values
	CurrentPhase = EEncounterPhase::READY;
	ObjectivesSucceeded = 0;
	ObjectivesFailed = 0;

	for (AEncounterTrigger* Trigger : triggers)
	{
		Trigger->SetOwningEncounter(this);
	}
}

//void AEncounter::AddTrigger()
//{
//	AEncounterTrigger* Trigger = GetWorld()->SpawnActor<AEncounterTrigger>(TriggerClass);
//	Trigger->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
//	triggers.Add(Trigger);
//}

void AEncounter::EncounterIntroBegin()
{
	if (CurrentPhase != EEncounterPhase::READY)
	{	
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Red,
				FString(TEXT("ERROR-> Trying to access Intro to encounter when not in ready"))
			);
		}
		return;
	}

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Blue,
			FString(TEXT("ENCOUNTER -> Encounter Intro Begins"))
		);
	}

	CurrentPhase = EEncounterPhase::INTRO;

	EncounterOnIntroBegin.Broadcast(this);
}

void AEncounter::EncounterIntroEnd()
{
	if (CurrentPhase != EEncounterPhase::INTRO)
	{
			
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Red,
				FString(TEXT("ERROR-> Trying to access Intro End to encounter when not in Intro Phase"))
			);
		}
		return;
	}

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Blue,
			FString(TEXT("ENCOUNTER -> Encounter Intro Ends"))
		);
	}

	EncounterOnIntroEnd.Broadcast(this);
}

void AEncounter::EncounterStart()
{
	if (CurrentPhase != EEncounterPhase::INTRO && CurrentPhase != EEncounterPhase::READY)
	{
			
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Red,
				FString(TEXT("ERROR-> Trying to access START to encounter when not in Intro or ready Phase"))
			);
		}
		return;
	}

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Blue,
			FString(TEXT("ENCOUNTER -> Encounter START"))
		);
	}

	CurrentPhase = EEncounterPhase::START;

	EncounterOnStartBegin.Broadcast(this);
}

void AEncounter::UpdateObjectiveSucceed()
{
	
	if (CurrentPhase != EEncounterPhase::START )
	{
			
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Red,
				FString(TEXT("ERROR-> Trying to Update Objective when not in START PHASE"))
			);
		}
		return;
	}

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Green,
			FString(TEXT("ENCOUNTER -> Encounter Objective Success"))
		);
	}

	EncounterOnUpdateObjectiveSucceed.Broadcast(this);

	ObjectivesSucceeded++;
	if(ObjectivesSucceeded >= ObjectivesCompleteRequirement)
	{
		StartSucceed();
	}
}

void AEncounter::UpdateObjectiveFailed()
{
	if (CurrentPhase != EEncounterPhase::START )
	{
			
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Red,
				FString(TEXT("ERROR-> Trying to Update Objective when not in START PHASE"))
			);
		}
		return;
	}

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Red,
			FString(TEXT("ENCOUNTER -> Encounter Objective Failed"))
		);
	}

	EncounterOnUpdateObjectiveFailed.Broadcast(this);

	ObjectivesFailed++;
	if(ObjectivesFailed >= ObjectivesFailedThreshold)
	{
		StartFailed();
	}
}

void AEncounter::StartSucceed()
{
	if (CurrentPhase != EEncounterPhase::START )
	{
			
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Red,
				FString(TEXT("ERROR-> Trying to Succeed Encounter when not in START PHASE"))
			);
		}
		return;
	}

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Green,
			FString(TEXT("ENCOUNTER -> Encounter Start Success!"))
		);
	}

	CurrentPhase = EEncounterPhase::END;

	EncounterOnSucceedBegin.Broadcast(this);
}

void AEncounter::StartFailed()
{
	if (CurrentPhase != EEncounterPhase::START )
	{
			
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Red,
				FString(TEXT("ERROR-> Trying to Fail Encounter when not in START PHASE"))
			);
		}
		return;
	}

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Red,
			FString(TEXT("ENCOUNTER -> Encoutner Start Failed"))
		);
	}

	CurrentPhase = EEncounterPhase::END;

	EncounterOnFailedBegin.Broadcast(this);
}

void AEncounter::EndSucceed()
{
	if (CurrentPhase != EEncounterPhase::END )
	{
			
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Red,
				FString(TEXT("ERROR-> Trying to EndEncounter when not in END PHASE"))
			);
		}
		return;
	}

		if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Green,
			FString(TEXT("ENCOUNTER -> Encounter End Success!"))
		);
	}

	CurrentPhase = EEncounterPhase::INACTIVE;

	EncounterOnSucceedEnd.Broadcast(this);
}

void AEncounter::EndFailed()
{

	if (CurrentPhase != EEncounterPhase::END )
	{
			
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Red,
				FString(TEXT("ERROR-> Trying to EndEncounter when not in END PHASE"))
			);
		}
		return;
	}

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Red,
			FString(TEXT("ENCOUNTER -> Encounter End Failed"))
		);
	}

	CurrentPhase = EEncounterPhase::INACTIVE;

	EncounterOnFailedEnd.Broadcast(this);
}

void AEncounter::OnTrigger(EEncounterPhase TriggerPhase)
{
	switch (TriggerPhase)
	{
		case EEncounterPhase::INTRO:
			EncounterIntroBegin();
		break;
		case EEncounterPhase::START:
			EncounterStart();
		break;
		default:

		break;
	}
}
