// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "HumanoidAnimInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartMeleeAttack);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndMeleeAttack);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartRangedAttack);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndRangedAttack);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartSpellCast);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndSpellCast);

UENUM(BlueprintType)
enum class EAnimationState : uint8
{
	DEFAULT UMETA(DisplayName = "Default"),
	DEAD UMETA(DisplayName = "Dead"),
	MELEE_ATTACK UMETA(DisplayName = "Melee attack"),
	RANGED_ATTACK UMETA(DisplayName = "Ranged attack"),
	SPELL_CAST UMETA(DisplayName = "Spell cast"),
};

/**
 * 
 */
UCLASS()
class ARPG_API UHumanoidAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnStartMeleeAttack OnStartMeleeAttack;

	UPROPERTY(BlueprintAssignable)
	FOnEndMeleeAttack OnEndMeleeAttack;

	UPROPERTY(BlueprintAssignable)
	FOnStartRangedAttack OnStartRangedAttack;

	UPROPERTY(BlueprintAssignable)
	FOnEndRangedAttack OnEndRangedAttack;

	UPROPERTY(BlueprintAssignable)
	FOnStartSpellCast OnStartSpellCast;

	UPROPERTY(BlueprintAssignable)
	FOnEndSpellCast OnEndSpellCast;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	void SetAnimationState(EAnimationState NewState);

	UFUNCTION(BlueprintCallable)
	EAnimationState GetAnimationState() const;

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EAnimationState AnimationState;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FVector LastLocation;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bIsMoving;

	UFUNCTION(BlueprintCallable)
	void StartMeleeAttack();

	UFUNCTION(BlueprintCallable)
	void EndMeleeAttack();

	UFUNCTION(BlueprintCallable)
	void StartRangedAttack();

	UFUNCTION(BlueprintCallable)
	void EndRangedAttack();

	UFUNCTION(BlueprintCallable)
	void StartSpellCast();

	UFUNCTION(BlueprintCallable)
	void EndSpellCast();
};
