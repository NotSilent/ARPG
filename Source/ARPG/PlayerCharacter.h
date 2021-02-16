// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "PlayerAIController.h"
#include "PlayerAnimInstance.h"
#include "Projectile.h"
#include "GameFramework/Character.h"


#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UNiagaraSystem;
class UHealthComponent;
class UAIPerceptionStimuliSourceComponent;

UCLASS()
class ARPG_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	virtual void Tick(float DeltaTime) override;

	float GetEquippedSpellRadius() const;

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void CastSpell();

	APlayerAIController* GetAIController() const;

	void InitSpell(const FVector& Destination);

	void StartCasting();

	void SpawnProjectile(const FVector& Destination);

	UPROPERTY(VisibleInstanceOnly)
	UHealthComponent* HealthComp;

	UPROPERTY(VisibleInstanceOnly)
	UPlayerAnimInstance* PlayerAnimInstance;

private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComp;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UNiagaraSystem* ForceSystem;

	UPROPERTY(VisibleInstanceOnly)
	FVector PreviousLocation;

	UPROPERTY(VisibleInstanceOnly)
	FVector DestinationOfNextSpell;

	UPROPERTY(VisibleInstanceOnly)
	AController* CreatorOfNextSpell;

	UPROPERTY(EditDefaultsOnly)
	UBehaviorTree* BehaviorTree;

	UPROPERTY(EditDefaultsOnly)
	UAIPerceptionStimuliSourceComponent* AIPerception;

	UFUNCTION()
	void OnDead();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	                         class AController* EventInstigator, AActor* DamageCauser) override;
};
