// Copyright © 2024, ProjectB. All rights reserved.


#include "PBPlayerPawn.h"

#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "ProjectB/Core/Component/PBActionComponent.h"


APBPlayerPawn::APBPlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	SetRootComponent(PlayerCamera);

	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;

	ActionComponent = CreateDefaultSubobject<UPBActionComponent>(TEXT("Action Component"));
}

void APBPlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void APBPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APBPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	OnSetupInputDelegate.Broadcast(PlayerInputComponent);
}

