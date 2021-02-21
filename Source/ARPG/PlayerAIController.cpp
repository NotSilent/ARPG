// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAIController.h"

#include "HumanoidAnimInstance.h"
#include "PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

void APlayerAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BehaviourTree);
}

void APlayerAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PlayerCharacter = GetPawn<APlayerCharacter>();

	if (PlayerCharacter && PlayerCharacter->HumanoidAnimInstance)
	{
		PlayerCharacter->HumanoidAnimInstance->OnEndSpellCast.AddDynamic(
			this, &APlayerAIController::OnPlayerStoppedCasting);
	}
}

void APlayerAIController::OnPlayerStoppedCasting()
{
	GetBlackboardComponent()->SetValueAsBool(FName(TEXT("IsCasting")), false);
}

void APlayerAIController::Move(const FVector& Destination)
{
	if (PlayerCharacter)
	{
		const FVector Direction = Destination - PlayerCharacter->GetActorLocation();
		FRotator Rotation = Direction.Rotation();
		Rotation.Pitch = 0.0f;
		Rotation.Roll = 0.0f;
		GetBlackboardComponent()->SetValueAsRotator(FName(TEXT("Rotation")), Rotation);
		GetBlackboardComponent()->SetValueAsVector(FName(TEXT("Destination")), Destination);
		GetBlackboardComponent()->ClearValue(FName(TEXT("SpellDestination")));
	}
}

void APlayerAIController::InitSpell(const FVector& Destination)
{
	if (PlayerCharacter)
	{
		const FVector Direction = Destination - PlayerCharacter->GetActorLocation();
		FRotator Rotation = Direction.Rotation();
		Rotation.Pitch = 0.0f;
		Rotation.Roll = 0.0f;
		GetBlackboardComponent()->ClearValue(FName(TEXT("Destination")));
		GetBlackboardComponent()->SetValueAsRotator(FName(TEXT("Rotation")), Rotation);
		GetBlackboardComponent()->
			SetValueAsVector(FName(TEXT("SpellDestination")), Destination);
		GetBlackboardComponent()->
			SetValueAsFloat(FName(TEXT("SpellRadius")), PlayerCharacter->GetEquippedSpellRadius());


		PlayerCharacter->PrepareWeapon(Destination);
	}
}

void APlayerAIController::StartCastingSpell()
{
	PlayerCharacter->StartWeaponAnimation();

	GetBlackboardComponent()->SetValueAsBool(FName(TEXT("IsCasting")), true);
}
