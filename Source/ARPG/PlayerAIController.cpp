// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAIController.h"
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
    }
}

void APlayerAIController::CastSpell(const FVector& Destination)
{
    if (PlayerCharacter)
    {
        const FVector Direction = Destination - PlayerCharacter->GetActorLocation();
        FRotator Rotation = Direction.Rotation();
        Rotation.Pitch = 0.0f;
        Rotation.Roll = 0.0f;
        GetBlackboardComponent()->SetValueAsRotator(FName(TEXT("Rotation")), Rotation);
        GetBlackboardComponent()->SetValueAsVector(FName(TEXT("Destination")), PlayerCharacter->GetActorLocation());

        PlayerCharacter->InitSpell(this, Destination);
    }
}
