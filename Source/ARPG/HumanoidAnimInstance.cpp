// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanoidAnimInstance.h"

void UHumanoidAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* Owner = TryGetPawnOwner();

	if (Owner)
	{
		const FVector CurrentLocation = Owner->GetActorLocation();

		bIsMoving = LastLocation != CurrentLocation;
		LastLocation = CurrentLocation;
	}
}

void UHumanoidAnimInstance::SetAnimationState(EAnimationState NewState)
{
	AnimationState = NewState;
}

EAnimationState UHumanoidAnimInstance::GetAnimationState() const
{
	return AnimationState;
}

void UHumanoidAnimInstance::StartMeleeAttack()
{
	OnStartMeleeAttack.Broadcast();
}

void UHumanoidAnimInstance::EndMeleeAttack()
{
	OnEndMeleeAttack.Broadcast();

	AnimationState = EAnimationState::DEFAULT;
}

void UHumanoidAnimInstance::StartRangedAttack()
{
	OnStartRangedAttack.Broadcast();
}

void UHumanoidAnimInstance::EndRangedAttack()
{
	OnEndRangedAttack.Broadcast();

	AnimationState = EAnimationState::DEFAULT;
}

void UHumanoidAnimInstance::StartSpellCast()
{
	OnStartSpellCast.Broadcast();
}

void UHumanoidAnimInstance::EndSpellCast()
{
	OnEndSpellCast.Broadcast();

	AnimationState = EAnimationState::DEFAULT;
}
