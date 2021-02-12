// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	MaxHealth = 100.0f;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	bHealthReachedZero = false;
	CurrentHealth = MaxHealth;
}

float UHealthComponent::ModifyHealth(float Value)
{
	if (bHealthReachedZero)
	{
		return 0.0f;
	}

	CurrentHealth += Value;

	OnHealthChanged.Broadcast(CurrentHealth / MaxHealth, CurrentHealth);

	if (CurrentHealth <= 0.0f)
	{
		bHealthReachedZero = true;

		OnHealthReachedZero.Broadcast();
	}

	return CurrentHealth;
}

float UHealthComponent::AddHealth(float Value)
{
	return ModifyHealth(Value);
}

float UHealthComponent::RemoveHealth(float Value)
{
	return ModifyHealth(-Value);
}
