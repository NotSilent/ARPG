// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"


#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh Comp");
	RootComponent = MeshComp;
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	if (NiagaraSystem)
	{
		UNiagaraComponent* NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(
			NiagaraSystem, MeshComp, NAME_None, FVector::ZeroVector, FRotator::ZeroRotator,
			EAttachLocation::SnapToTargetIncludingScale, false, true);

		NiagaraComponent->SetupAttachment(RootComponent);
	}
}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeapon::PrepareWeapon(const FWeaponUseProperties& Properties)
{
	NextUseProperties = Properties;
}

void AWeapon::StartWeapon()
{
	OnStartWeapon();
}

void AWeapon::StopWeapon()
{
	OnStopWeapon();
}

EAnimationState AWeapon::GetAnimationState() const
{
	return AnimationState;
}

float AWeapon::GetRange() const
{
	return Range;
}
