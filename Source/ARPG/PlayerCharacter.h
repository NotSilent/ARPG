// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


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

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	UAnimInstance* AnimInstance;

	UFUNCTION(BlueprintImplementableEvent)
	void SetSpeed(float Value);

	UFUNCTION(BlueprintImplementableEvent)
	void SetTurnAngle(float Value);

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComp;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UNiagaraSystem* ForceSystem;

	UPROPERTY(VisibleInstanceOnly)
	UHealthComponent* HealthComp;

	UPROPERTY(VisibleInstanceOnly)
	FVector PreviousLocation;

	void OnDead();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	                         class AController* EventInstigator, AActor* DamageCauser) override;
};
