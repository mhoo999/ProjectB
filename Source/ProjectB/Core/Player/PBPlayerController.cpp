// Copyright © 2024, ProjectB. All rights reserved.


#include "PBPlayerController.h"

#include "PBPlayerPawn.h"
#include "ProjectB/Core/Component/PBCameraComponent.h"


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
}
