// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"

#include "BTTask_RotateYaw.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UBTTask_RotateYaw : public UBTTask_BlackboardBase
{
    GENERATED_BODY()

public:
    UBTTask_RotateYaw();

private:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
    virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
