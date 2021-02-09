// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownPlayerController.h"

#include "AIController.h"
#include "DrawDebugHelpers.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

ATopDownPlayerController::ATopDownPlayerController()
{
	AcceptanceRadius = 0.5f;
}

void ATopDownPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("LMB", IE_Pressed, this, &ATopDownPlayerController::OnLeftMouseButtonClicked);
}

void ATopDownPlayerController::BeginPlay()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	APlayerCharacter* PlayerCharacter = GetWorld()->SpawnActor<APlayerCharacter>(
		PlayerCharacterClass, FVector(0.0f, 0.0f, 112.0f), FRotator::ZeroRotator, SpawnParams);

	if (PlayerCharacter)
	{
		PlayerAIController = PlayerCharacter->GetAIController();
	}

	SetViewTarget(PlayerCharacter);
}


void ATopDownPlayerController::OnLeftMouseButtonClicked()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		APawn* const MyPawn = GetPawn();
		if (MyPawn)
		{
			float const Distance = FVector::Dist(Hit.ImpactPoint, MyPawn->GetActorLocation());

			if (Distance > 100.0f)
			{
				if (PlayerAIController)
				{
					PlayerAIController->Move(Hit.ImpactPoint, AcceptanceRadius);
				}

				DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 5.0f, 8, FColor::Red, false, 5.0f, 0, 1.0f);
			}
		}
	}
}
