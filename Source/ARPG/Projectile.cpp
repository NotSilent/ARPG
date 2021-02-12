// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Mesh Comp");
	RootComponent = MeshComp;

	Speed = 500.0f;
	Radius = 500.0f;
}

float AProjectile::GetRadius() const
{
	return Radius;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + MovementDirection * Speed * DeltaTime);
}

void AProjectile::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (GetInstigator() == OtherActor)
	{
		return;
	}

	if (Cast<AProjectile>(OtherActor))
	{
		return;
	}

	MeshComp->SetVisibility(false);
	OnCollided(GetActorLocation());
}

void AProjectile::Init(const FVector& Direction)
{
	MovementDirection = Direction;

	SetLifeSpan(5.0f);
}
