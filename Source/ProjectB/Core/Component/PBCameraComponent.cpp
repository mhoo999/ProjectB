// Copyright © 2024, ProjectB. All rights reserved.


#include "PBCameraComponent.h"

#include "ProjectB/ProjectB.h"
#include "ProjectB/Core/Player/PBPlayerController.h"
#include "ProjectB/Core/Player/PBPlayerPawn.h"


UPBCameraComponent::UPBCameraComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPBCameraComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPBCameraComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bPauseFunction == false)
	{
		if (PlayerController && GEngine)
		{
			PlayerController->GetMousePosition(MouseX, MouseY);
			GEngine->GameViewport->GetViewportSize(ViewportSize);
			
			float NormalizedX = MouseX / ViewportSize.X;
			float NormalizedY = MouseY / ViewportSize.Y;
			
			float YawAngle = FMath::Lerp(-MaxYawAngle, MaxYawAngle, NormalizedX);
			float PitchAngle = FMath::Lerp(-MaxPitchAngle, MaxPitchAngle, NormalizedY);

			FRotator CurrentRotation = PlayerController->GetControlRotation();
			FRotator TargetRotation = PlayerController->GetControlRotation();
			TargetRotation.Yaw = YawAngle;
			TargetRotation.Pitch = -PitchAngle;
			FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, 5.0f);
			PlayerController->SetControlRotation(NewRotation);
		}
	}
}

