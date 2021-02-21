// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "HumanoidAnimInstance.h"
#include "NiagaraSystem.h"
#include "Components/SceneComponent.h"
#include "Weapon.generated.h"

USTRUCT(BlueprintType)
struct FWeaponUseProperties
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	AController* Owner;

	UPROPERTY(BlueprintReadWrite)
	FVector Destination;
};


UCLASS()
class ARPG_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	AWeapon();

	virtual void Tick(float DeltaTime) override;

	void PrepareWeapon(const FWeaponUseProperties& Properties);

	virtual void StartWeapon();

	virtual void StopWeapon();

	UFUNCTION(BlueprintCallable)
	EAnimationState GetAnimationState() const;

	UFUNCTION(BlueprintCallable)
	float GetRange() const;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnStopWeapon();

	UFUNCTION(BlueprintImplementableEvent)
	void OnStartWeapon();

private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	UNiagaraSystem* NiagaraSystem;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	EAnimationState AnimationState;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	float Range;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FWeaponUseProperties NextUseProperties;
};
