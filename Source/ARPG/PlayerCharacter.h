// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "PlayerAIController.h"
#include "Projectile.h"
#include "GameFramework/Character.h"


#include "PlayerCharacter.generated.h"

class AWeapon;
class USpringArmComponent;
class UCameraComponent;
class UNiagaraSystem;
class UHealthComponent;
class UAIPerceptionStimuliSourceComponent;
class UHumanoidAnimInstance;

UCLASS()
class ARPG_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	float GetEquippedSpellRadius() const;

protected:
	virtual void BeginPlay() override;

public:
	APlayerAIController* GetAIController() const;

	UFUNCTION(BlueprintCallable)
	void StartWeapon();

	void PrepareWeapon(const FVector& Destination);

	void StartWeaponAnimation();

	UPROPERTY(VisibleInstanceOnly)
	UHealthComponent* HealthComp;

	UPROPERTY(VisibleInstanceOnly)
	UHumanoidAnimInstance* HumanoidAnimInstance;

private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AWeapon> WeaponClass;

	UPROPERTY(VisibleInstanceOnly, meta = (AllowPrivateAccess = "true"))
	AWeapon* EquippedWeapon;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComp;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComp;

	UPROPERTY(EditDefaultsOnly)
	UBehaviorTree* BehaviorTree;

	UPROPERTY(EditDefaultsOnly)
	UAIPerceptionStimuliSourceComponent* AIPerception;

	UFUNCTION()
	void OnDead();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	                         class AController* EventInstigator, AActor* DamageCauser) override;
};
