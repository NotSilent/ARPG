// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownPlayerController.h"

#include "DrawDebugHelpers.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "HealthComponent.h"
#include "PlayerSaveGame.h"
#include "BehaviorTree/BlackboardComponent.h"

ATopDownPlayerController::ATopDownPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	SaveInterval = 5.0f;
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
		PlayerCharacter->HealthComp->OnHealthChanged.
		                 AddDynamic(this, &ATopDownPlayerController::OnPlayerHealthChanged);

		const FString SlotName = UPlayerSaveGame::StaticClass()->GetFName().ToString();

		if (UPlayerSaveGame* Save = Cast<UPlayerSaveGame>(
			UGameplayStatics::LoadGameFromSlot(SlotName, 0)))
		{
			PlayerCharacter->SetActorLocation(Save->LastPlayerLocation);
		}
	}

	PlayerWidget = CreateWidget<UPlayerHUD>(this, PlayerWidgetClass);
	PlayerWidget->AddToViewport();

	SetViewTarget(PlayerCharacter);

	GetWorldTimerManager().SetTimer(SaveTimerHandle, this, &ATopDownPlayerController::Save, SaveInterval, true,
	                                SaveInterval);
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

void ATopDownPlayerController::OnPlayerHealthChanged(float PercentValue, float Value)
{
	PlayerWidget->SetTargetHealthValue(PercentValue);
}

void ATopDownPlayerController::Save()
{
	UPlayerSaveGame* Save = Cast<UPlayerSaveGame>(
		UGameplayStatics::CreateSaveGameObject(UPlayerSaveGame::StaticClass()));
	if (Save)
	{
		const FString SlotName = UPlayerSaveGame::StaticClass()->GetFName().ToString();

		Save->LastPlayerLocation = PlayerCharacter->GetActorLocation();

		UGameplayStatics::AsyncSaveGameToSlot(Save, SlotName, 0);
	}
}
