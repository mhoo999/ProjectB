// Copyright © 2024, ProjectB. All rights reserved.


#include "PBPlayerController.h"

#include "PBPlayerPawn.h"
#include "ProjectB/Core/Component/PBActionComponent.h"
#include "ProjectB/Core/Component/PBCameraComponent.h"
#include "ProjectB/Core/UI/PBHUD.h"


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

void APBPlayerController::ShowItemDetails(AItemBase* Item)
{
	if (APBHUD* PlayerHUD = Cast<APBHUD>(GetHUD()))
	{
		PlayerHUD->ShowItemDetailsWidget(Item);
	}
}
