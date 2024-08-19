// Copyright © 2024, ProjectB. All rights reserved.


#include "PBPlayerPawn.h"

#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "ProjectB/Core/Component/PBActionComponent.h"
#include "ProjectB/Core/Component/PBCameraComponent.h"


APBPlayerPawn::APBPlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	SetRootComponent(PlayerCamera);

	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;

	ActionComponent = CreateDefaultSubobject<UPBActionComponent>(TEXT("Action Component"));
	CameraComponent = CreateDefaultSubobject<UPBCameraComponent>(TEXT("Camera Setting Component"));
}

void APBPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
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

