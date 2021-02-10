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

UCLASS()
class ARPG_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

public:
	APlayerAIController* GetAIController() const;

	UFUNCTION(BlueprintCallable)
	void CastSpell();

	void InitSpell(AController* Creator, const FVector& Destination);

	void SpawnProjectile(AController* Creator, const FVector& Destination);

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
	UHealthComponent* HealthComp;

	UPROPERTY(VisibleInstanceOnly)
	UPlayerAnimInstance* PlayerAnimInstance;

	UPROPERTY(VisibleInstanceOnly)
	FVector PreviousLocation;

	UPROPERTY(VisibleInstanceOnly)
	FVector DestinationOfNextSpell;

	UPROPERTY(VisibleInstanceOnly)
	AController* CreatorOfNextSpell;


	UFUNCTION()
	void OnDead();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	                         class AController* EventInstigator, AActor* DamageCauser) override;
};
