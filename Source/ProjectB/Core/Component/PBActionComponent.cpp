// Copyright © 2024, ProjectB. All rights reserved.


#include "PBActionComponent.h"
#include "EnhancedInputComponent.h"

#include "ProjectB/Core/Player/PBPlayerPawn.h"


UPBActionComponent::UPBActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_ClickRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProjectB/Core/Component/InputComponent/IA_Click.IA_Click'"));
	if (IA_ClickRef.Succeeded())
	{
		IA_Click = IA_ClickRef.Object;
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
		EnhancedInputComponent->BindAction(IA_Click, ETriggerEvent::Triggered, this, &UPBActionComponent::Click);
	}
}

void UPBActionComponent::Click(const FInputActionValue& Value)
{
	// Click Event
}
