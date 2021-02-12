// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownPlayerController.h"

#include "DrawDebugHelpers.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

ATopDownPlayerController::ATopDownPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATopDownPlayerController::Tick(float DeltaTime)
{
	if (bLMBDown)
	{
		MovePlayerToMousePosition();
	}
}

void ATopDownPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("LMB", IE_Pressed, this, &ATopDownPlayerController::OnLeftMouseButtonPressed);
	InputComponent->BindAction("LMB", IE_Released, this, &ATopDownPlayerController::OnLeftMouseButtonReleased);

	InputComponent->BindAction("RMB", IE_Pressed, this, &ATopDownPlayerController::OnRightMouseButtonClicked);
}

void ATopDownPlayerController::BeginPlay()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	PlayerCharacter = GetWorld()->SpawnActor<APlayerCharacter>(
		PlayerCharacterClass, FVector(0.0f, 0.0f, 112.0f), FRotator::ZeroRotator, SpawnParams);

	if (PlayerCharacter)
	{
		PlayerAIController = PlayerCharacter->GetAIController();
	}

	SetViewTarget(PlayerCharacter);
}

void ATopDownPlayerController::MovePlayerToMousePosition()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit && PlayerAIController)
	{
		PlayerAIController->Move(Hit.ImpactPoint);
	}
}

void ATopDownPlayerController::OnLeftMouseButtonPressed()
{
	bLMBDown = true;
}

void ATopDownPlayerController::OnLeftMouseButtonReleased()
{
	bLMBDown = false;
}

void ATopDownPlayerController::OnRightMouseButtonClicked()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		PlayerAIController->InitSpell(Hit.ImpactPoint);
	}
}
