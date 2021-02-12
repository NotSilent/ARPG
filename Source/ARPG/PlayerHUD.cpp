// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"

void UPlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();

	HealthValue = 1.0f;
	ShownHealthValue = 1.0f;

	HealthWidget->SetPercent(ShownHealthValue);
}

void UPlayerHUD::SetTargetHealthValue(float Value)
{
	HealthValue = Value;
}

void UPlayerHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	const float Difference = ShownHealthValue - HealthValue;
	const float ClampedDifference = FMath::Clamp(Difference, -MaxVisiblePercentRateChangePerSecond * InDeltaTime,
	                                             MaxVisiblePercentRateChangePerSecond * InDeltaTime);

	ShownHealthValue -= ClampedDifference;

	HealthWidget->SetPercent(ShownHealthValue);
}
