// Copyright © 2024, ProjectB. All rights reserved.


#include "PBPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "PBPlayerPawn.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectB/ProjectB.h"
#include "ProjectB/Core/Component/PBActionComponent.h"
#include "ProjectB/Core/Component/PBCameraComponent.h"
#include "ProjectB/Core/UI/PBInspectWidget.h"
#include "ProjectB/Core/UI/PBHUD.h"
#include "ProjectB/InspectionSystem/PBInspectItem.h"
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
	PlayerHUD = Cast<APBHUD>(GetHUD());
	
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

void APBPlayerController::ItemInspection(UStaticMesh* StaticMesh, FText ItemName, FText ItemDescription, FVector ItemScale)
{
	SetUIOpenTrue();
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->RemoveMappingContext(DefaultMappingContext);
		Subsystem->AddMappingContext(ItemInspectionContext, 0);
	}
	
	if (PlayerHUD)
	{
		PlayerHUD->ShowInspectWidget(ItemName, ItemDescription);
	}

	FVector NewLocation = FVector(100000000.f, 0.f, 0.f);
	FRotator NewRotation = FRotator(0.f, 0.f, 0.f);
	FTransform NewTransform = FTransform(NewRotation, NewLocation, ItemScale);
	FActorSpawnParameters SpawnInfo;

	SpawnInspectItem = GetWorld()->SpawnActor<APBInspectItem>(InspectItemFactory, NewTransform, SpawnInfo);
	if (SpawnInspectItem != nullptr)
	{
		SpawnInspectItem->GetStaticMeshComponent()->SetStaticMesh(StaticMesh);
		
		if (UPBActionComponent* ActionComponent = PlayerPawn->GetComponentByClass<UPBActionComponent>())
		{
			ActionComponent->SetInspectItem(SpawnInspectItem);
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
}

void APBPlayerController::ExitInspectWidget()
{
	if (PlayerHUD)
	{
		PlayerHUD->HiddenInspectWidget();
	}

	if (UPBActionComponent* ActionComponent = PlayerPawn->GetComponentByClass<UPBActionComponent>())
	{
		ActionComponent->DeleteInspectItem();
	}
	
	SpawnInspectItem->Destroy();
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->RemoveMappingContext(ItemInspectionContext);
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
	
	SetUIOpenFalse();
}
