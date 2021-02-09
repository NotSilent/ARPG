// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"


#include "HealthComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Niagara/Public/NiagaraComponent.h"
#include "Niagara/Public/NiagaraFunctionLibrary.h"

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

	AnimInstance = GetMesh()->GetAnimInstance();

	PreviousLocation = GetActorLocation();

	HealthComp = FindComponentByClass<UHealthComponent>();
	if (HealthComp)
	{
		HealthComp->OnHealthReachedZero.AddDynamic(this, &APlayerCharacter::OnDead);
	}

	SpawnDefaultController();
}

APlayerAIController* APlayerCharacter::GetAIController() const
{
	return Cast<APlayerAIController>(Controller);
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (AnimInstance)
	{
		if (FMath::IsNearlyZero(FVector::Distance(PreviousLocation, GetActorLocation())))
		{
			SetSpeed(0.0f);
		}
		else
		{
			SetSpeed(1.0f);

			//TODO: Rewrite UAIBlueprintHelperLibrary::SimpleMoveToLocation to store current target and turn it's way

			const FVector TargetForward = GetActorLocation() - PreviousLocation;

			SetActorRotation(TargetForward.Rotation());

			PreviousLocation = GetActorLocation();
		}
	}
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
