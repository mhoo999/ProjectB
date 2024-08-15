// Copyright © 2024, ProjectB. All rights reserved.


#include "PBActionComponent.h"
#include "EnhancedInputComponent.h"

#include "ProjectB/Core/Player/PBPlayerPawn.h"


UPBActionComponent::UPBActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_LookRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProjectB/Core/Component/InputComponent/IA_Look.IA_Look'"));
	if (IA_LookRef.Succeeded())
	{
		IA_Look = IA_LookRef.Object;
	}
}

void UPBActionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPBActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPBActionComponent::SetupPlayerInput(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInput(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered, this, &UPBActionComponent::Look);
	}
}

void UPBActionComponent::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	LookAxisVector *= Sensitivity;

	if (PlayerPawn->Controller != nullptr)
	{
		FRotator CurrentRotation = PlayerPawn->Controller->GetControlRotation();
		float NewYaw = CurrentRotation.Yaw + LookAxisVector.X;
		float NewPitch = CurrentRotation.Pitch + LookAxisVector.Y;

		NewYaw = FMath::Clamp(NewYaw, MinAngle, MaxAngle);
		NewPitch = FMath::Clamp(NewPitch, MinAngle, MaxAngle);
		
		PlayerPawn->Controller->SetControlRotation(FRotator(NewPitch, NewYaw, CurrentRotation.Roll));
	}
}
