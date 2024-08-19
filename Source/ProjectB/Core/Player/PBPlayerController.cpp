// Copyright © 2024, ProjectB. All rights reserved.


#include "PBPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "PBPlayerPawn.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectB/ProjectB.h"
#include "ProjectB/Core/Component/PBActionComponent.h"
#include "ProjectB/Core/Component/PBCameraComponent.h"
#include "ProjectB/Core/UI/PBHUD.h"
#include "ProjectB/Items/PBItemBase.h"


APBPlayerController::APBPlayerController()
{
}

void APBPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	bShowMouseCursor = true;
	
	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	InputMode.SetHideCursorDuringCapture(false);
	SetInputMode(InputMode);

	PlayerPawn = Cast<APBPlayerPawn>(GetPawn());
	if (UPBCameraComponent* CameraComponent =  PlayerPawn->GetComponentByClass<UPBCameraComponent>())
	{
		CameraComponent->InitPlayerController();
	}
	if (UPBActionComponent* ActionComponent = PlayerPawn->GetComponentByClass<UPBActionComponent>())
	{
		ActionComponent->InitPlayerController();
	}
}

void APBPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void APBPlayerController::ItemInspection(APBItemBase* Item)
{
	SetUIOpenTrue();
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->RemoveMappingContext(DefaultMappingContext);
		Subsystem->AddMappingContext(ItemInspectionContext, 0);
	}
	
	if (APBHUD* PlayerHUD = Cast<APBHUD>(GetHUD()))
	{
		PlayerHUD->ShowBlurUI();
	}

	if (Item && Item->GetStaticMeshComponent())
	{
		FVector NewLocation = FVector(200.f, 0.f, 0.f);
		FRotator NewRotation = FRotator(0.f, 0.f, 0.f);
		FTransform NewTransform = FTransform(NewRotation, NewLocation);
		FActorSpawnParameters SpawnInfo;

		if (APBItemBase* SpawnItem = GetWorld()->SpawnActor<APBItemBase>(Item->GetClass(), NewTransform, SpawnInfo))
		{
			SpawnItem->GetStaticMeshComponent()->SetStaticMesh(Item->GetStaticMeshComponent()->GetStaticMesh());
			PBLOG_S(Warning);
		}
	}
}

void APBPlayerController::SetUIOpenTrue()
{
	bIsUIOpen = true;
	UIOpenDelegate.Broadcast(bIsUIOpen);
}

void APBPlayerController::SetUIOpenFalse()
{
	bIsUIOpen = false;
	UIOpenDelegate.Broadcast(bIsUIOpen);

	// if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	// {
	// 	Subsystem->RemoveMappingContext(ItemInspectionContext);
	// 	Subsystem->AddMappingContext(DefaultMappingContext, 0);
	// }
}
