// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"

void UPlayerAnimInstance::StartCasting()
{
	bIsCasting = true;
}

void UPlayerAnimInstance::SetSpeed(float Value)
{
	Speed = Value;
}

void UPlayerAnimInstance::BroadcastOnStartCast()
{
	OnStartCast.Broadcast();
}
