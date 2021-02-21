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
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"
#include "HumanoidAnimInstance.h"
#include "Weapon.h"
#include "Engine/SkeletalMeshSocket.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComp->SetupAttachment(SpringArmComp);

	HealthComp = CreateDefaultSubobject<UHealthComponent>("Health");

	AIPerception = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>("AI Perception Stimuli");
	AIPerception->RegisterForSense(UAISense_Sight::StaticClass());
	AIPerception->bAutoRegister = true;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	USkeletalMeshComponent* MeshComp = GetMesh();
	const FName SocketName = TEXT("RightHandSocket");
	if (MeshComp && MeshComp->DoesSocketExist(SocketName))
	{
		const USkeletalMeshSocket* Socket = MeshComp->GetSocketByName(SocketName);
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		EquippedWeapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass, MeshComp->GetSocketLocation(SocketName),
		                                                 FRotator::ZeroRotator, SpawnParams);

		const FAttachmentTransformRules Rules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget,
		                                      EAttachmentRule::SnapToTarget, true);
		EquippedWeapon->AttachToComponent(MeshComp, Rules, SocketName);
		// Socket->AttachActor(EquippedWeapon, MeshComp);
		// EquippedWeapon->SetActorLocation(FVector::ZeroVector);
	}

	HealthComp = FindComponentByClass<UHealthComponent>();
	if (HealthComp)
	{
		HealthComp->OnHealthReachedZero.AddDynamic(this, &APlayerCharacter::OnDead);
	}

	HumanoidAnimInstance = Cast<UHumanoidAnimInstance>(GetMesh()->GetAnimInstance());
	if (HumanoidAnimInstance)
	{
		HumanoidAnimInstance->OnStartSpellCast.AddDynamic(this, &APlayerCharacter::StartWeapon);
	}

	SpawnDefaultController();
}

APlayerAIController* APlayerCharacter::GetAIController() const
{
	return Cast<APlayerAIController>(Controller);
}

void APlayerCharacter::StartWeapon()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->StartWeapon();
	}
}

void APlayerCharacter::PrepareWeapon(const FVector& Destination)
{
	if (EquippedWeapon)
	{
		FWeaponUseProperties Properties;
		Properties.Destination = Destination;
		Properties.Owner = Controller;
		EquippedWeapon->PrepareWeapon(Properties);
	}
}

void APlayerCharacter::StartWeaponAnimation()
{
	if (EquippedWeapon)
	{
		const EAnimationState State = EquippedWeapon->GetAnimationState();
		HumanoidAnimInstance->SetAnimationState(State);
	}
}

float APlayerCharacter::GetEquippedSpellRadius() const
{
	if (EquippedWeapon)
	{
		return EquippedWeapon->GetRange();
	}

	return TNumericLimits<float>::Max();
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
