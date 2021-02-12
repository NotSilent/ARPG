// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"

#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void SetTargetHealthValue(float Value);

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UProgressBar* HealthWidget;

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	UPROPERTY(VisibleInstanceOnly)
	float HealthValue;

	UPROPERTY(VisibleInstanceOnly)
	float ShownHealthValue;

	UPROPERTY(EditAnywhere)
	float MaxVisiblePercentRateChangePerSecond;
};
