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
#include "ProjectB/Core/Player/PBHUD.h"
#include "ProjectB/InspectionSystem/PBInspectItem.h"
#include "ProjectB/Items/PBItemBase.h"


APBPlayerController::APBPlayerController()
{
}

void APBPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Initialize game mode
	bShowMouseCursor = true;
	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	InputMode.SetHideCursorDuringCapture(false);
	SetInputMode(InputMode);

	PlayerPawn = Cast<APBPlayerPawn>(GetPawn());
	PlayerHUD = Cast<APBHUD>(GetHUD());

	// Add player controller value to each component
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

void APBPlayerController::ItemInspection(UStaticMesh* StaticMesh, FText ItemName, FString ItemDescription, FVector ItemScale)
{
	PauseBasicFunction();
	
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

void APBPlayerController::PauseBasicFunction()
{
	bIsUIOpen = true;
	UPauseDefaultFunctionDelegate.Broadcast(bIsUIOpen);
}

void APBPlayerController::ResumeBasicFunction()
{
	bIsUIOpen = false;
	UPauseDefaultFunctionDelegate.Broadcast(bIsUIOpen);
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
	
	ResumeBasicFunction();
}

void APBPlayerController::VisibilityToggleDialogueInspectWidget() const
{
	if (PlayerHUD)
	{
		PlayerHUD->VisibilityToggleDialogueInspectWidget();
	}
}

void APBPlayerController::Communication(UMaterialInterface* CharacterTexture, FName CharacterName, FString Dialogue)
{
	PauseBasicFunction();
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->RemoveMappingContext(DefaultMappingContext);
		Subsystem->AddMappingContext(CommunicationContext, 0);
	}
	
	if (PlayerHUD)
	{
		PlayerHUD->ShowCommunicateWidget(CharacterTexture, CharacterName, Dialogue);
	}
}

void APBPlayerController::ExitCommunicationWidget()
{
	if (PlayerHUD)
	{
		PlayerHUD->HiddenCommunicationWidget();
	}
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->RemoveMappingContext(CommunicationContext);
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
	
	ResumeBasicFunction();
}
