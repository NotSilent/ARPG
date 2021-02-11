// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_RotateYaw.h"

#include "PlayerAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Rotator.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

UBTTask_RotateYaw::UBTTask_RotateYaw()
{
    NodeName = "RotateYaw";
    bNotifyTick = true;

    // accept only vectors
    BlackboardKey.AddRotatorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_RotateYaw, BlackboardKey));
}

EBTNodeResult::Type UBTTask_RotateYaw::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    return EBTNodeResult::InProgress;
}

void UBTTask_RotateYaw::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    AAIController* MyController = OwnerComp.GetAIOwner();

    APlayerAIController* PlayerAIController = Cast<APlayerAIController>(MyController);

    if (PlayerAIController)
    {
        APawn* Pawn = PlayerAIController->GetPawn();
        if (Pawn)
        {
            const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
            const FRotator Rotation = MyBlackboard->GetValue<UBlackboardKeyType_Rotator>(
                BlackboardKey.GetSelectedKeyID());

            Pawn->SetActorRotation(Rotation);
        }
    }
}
