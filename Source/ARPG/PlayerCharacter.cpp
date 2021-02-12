// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"


#include "HealthComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Niagara/Public/NiagaraComponent.h"
#include "Niagara/Public/NiagaraFunctionLibrary.h"
#include "PlayerAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComp->SetupAttachment(SpringArmComp);

	HealthComp = CreateDefaultSubobject<UHealthComponent>("Health");
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	const USkeletalMeshComponent* MeshComp = GetMesh();
	const FName SocketName = TEXT("RightHandSocket");
	if (MeshComp && MeshComp->DoesSocketExist(SocketName))
	{
		UNiagaraFunctionLibrary::SpawnSystemAttached(ForceSystem, GetMesh(), SocketName, FVector::ZeroVector,
		                                             FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset, false);
	}

	PreviousLocation = GetActorLocation();

	HealthComp = FindComponentByClass<UHealthComponent>();
	if (HealthComp)
	{
		HealthComp->OnHealthReachedZero.AddDynamic(this, &APlayerCharacter::OnDead);
	}

	PlayerAnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	if (PlayerAnimInstance)
	{
		PlayerAnimInstance->OnStartCast.AddDynamic(this, &APlayerCharacter::CastSpell);
	}

	SpawnDefaultController();
}

APlayerAIController* APlayerCharacter::GetAIController() const
{
	return Cast<APlayerAIController>(Controller);
}

void APlayerCharacter::CastSpell()
{
	SpawnProjectile(DestinationOfNextSpell);
}

void APlayerCharacter::InitSpell(const FVector& Destination)
{
	DestinationOfNextSpell = Destination;
}

void APlayerCharacter::StartCasting()
{
	PlayerAnimInstance->StartCasting();
}

void APlayerCharacter::SpawnProjectile(const FVector& Destination)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;
	SpawnParams.Owner = this;

	USkeletalMeshComponent* MeshComp = GetMesh();
	const FName SocketName = TEXT("RightHandSocket");
	const FVector SocketLocation = MeshComp->GetSocketLocation(SocketName);

	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SocketLocation,
	                                                              FRotator::ZeroRotator, SpawnParams);

	FVector Direction = Destination - SocketLocation;

	if (Projectile)
	{
		Direction.Normalize();
		Projectile->Init(Direction);
	}
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerAnimInstance)
	{
		if (FMath::IsNearlyZero(FVector::Distance(PreviousLocation, GetActorLocation())))
		{
			PlayerAnimInstance->SetSpeed(0.0f);
		}
		else
		{
			PlayerAnimInstance->SetSpeed(1.0f);
		}

		PreviousLocation = GetActorLocation();
	}
}

float APlayerCharacter::GetEquippedSpellRadius() const
{
	return ProjectileClass->GetDefaultObject<AProjectile>()->GetRadius();
}

void APlayerCharacter::OnDead()
{
	UE_LOG(LogTemp, Warning, TEXT("YOU DIED"));
}

float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                                   AActor* DamageCauser)
{
	if (HealthComp)
	{
		return HealthComp->RemoveHealth(DamageAmount);
	}

	return 0.0f;
}
