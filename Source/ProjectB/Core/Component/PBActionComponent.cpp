// Copyright © 2024, ProjectB. All rights reserved.


#include "PBActionComponent.h"
#include "EnhancedInputComponent.h"
#include "ProjectB/ProjectB.h"
#include "ProjectB/Core/Interface/Interactable.h"
#include "ProjectB/Core/Player/PBPlayerController.h"

#include "ProjectB/Core/Player/PBPlayerPawn.h"


UPBActionComponent::UPBActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_ClickRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProjectB/Core/Component/InputComponent/IA_Click.IA_Click'"));
	if (IA_ClickRef.Succeeded())
	{
		IA_Click = IA_ClickRef.Object;
	}

	LastHitActor = nullptr;
}

void UPBActionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPBActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bPauseFunction == false)
	{
		if (PlayerController)
		{
			FVector2d MousePosition;
			PlayerController->GetMousePosition(MousePosition.X, MousePosition.Y);
			FVector WorldLocation, WorldDirection;

			if (PlayerController->DeprojectScreenPositionToWorld(MousePosition.X, MousePosition.Y, WorldLocation, WorldDirection))
			{
				FVector TraceStart = WorldLocation;
				FVector TraceEnd = TraceStart + (WorldDirection * 1000.0f);

				FHitResult HitResult;
				FCollisionQueryParams Params;
				Params.AddIgnoredActor(GetOwner());

				if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, Params))
				{
					HitActor = Cast<IInteractable>(HitResult.GetActor());
					
					if (HitActor)
					{
						HitActor->SetOutline(true);
						
						if (LastHitActor && LastHitActor != HitActor)
						{
							LastHitActor->SetOutline(false);
						}
						LastHitActor = HitActor;
					}
					else if (LastHitActor)
					{
						LastHitActor->SetOutline(false);
						LastHitActor = nullptr;
					}
				}

				DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Green, false, 1.0f, 0, 0.1f);
			}
		}
	}
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
	if (HitActor)
	{
		HitActor->Interact(PlayerController);
	}
}
