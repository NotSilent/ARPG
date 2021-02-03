// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownPlayerController.h"


#include "DrawDebugHelpers.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/GameplayStatics.h"

void ATopDownPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("LMB", IE_Pressed, this, &ATopDownPlayerController::OnLeftMouseButtonClicked);
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
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Hit.ImpactPoint);

				DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 5.0f, 8, FColor::Red, false, 5.0f, 0, 1.0f);
			}
		}
	}
}
