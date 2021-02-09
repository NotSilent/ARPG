// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"



#include "PlayerAIController.h"
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
