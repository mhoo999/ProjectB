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

	static ConstructorHelpers::FObjectFinder<UInputAction> ClickDefaultRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProjectB/Core/Component/InputComponent/Default/IA_Click_Default.IA_Click_Default'"));
	if (ClickDefaultRef.Succeeded())
	{
		IA_Click_Default = ClickDefaultRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> ClickItemRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProjectB/Core/Component/InputComponent/ItemInspection/IA_Click_Item.IA_Click_Item'"));
	if (ClickItemRef.Succeeded())
	{
		IA_Click_Item = ClickItemRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> MouseXItemRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProjectB/Core/Component/InputComponent/ItemInspection/IA_MouseX_Item.IA_MouseX_Item'"));
	if (MouseXItemRef.Succeeded())
	{
		IA_MouseX_Item = MouseXItemRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> MouseYItemRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProjectB/Core/Component/InputComponent/ItemInspection/IA_MouseY_Item.IA_MouseY_Item'"));
	if (MouseYItemRef.Succeeded())
	{
		IA_MouseY_Item = MouseYItemRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> WheelUpItemRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProjectB/Core/Component/InputComponent/ItemInspection/IA_WheelDown_Item.IA_WheelDown_Item'"));
	if (WheelUpItemRef.Succeeded())
	{
		IA_WheelUp_Item = WheelUpItemRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> WheelDownItemRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProjectB/Core/Component/InputComponent/ItemInspection/IA_WheelUp_Item.IA_WheelUp_Item'"));
	if (WheelDownItemRef.Succeeded())
	{
		IA_WheelDown_Item = WheelDownItemRef.Object;
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
		EnhancedInputComponent->BindAction(IA_Click_Default, ETriggerEvent::Started, this, &UPBActionComponent::Click_Default);

		EnhancedInputComponent->BindAction(IA_Click_Item, ETriggerEvent::Started, this, &UPBActionComponent::Press_Item);
		EnhancedInputComponent->BindAction(IA_Click_Item, ETriggerEvent::Completed, this, &UPBActionComponent::Release_Item);
		EnhancedInputComponent->BindAction(IA_MouseX_Item, ETriggerEvent::Triggered, this, &UPBActionComponent::MouseX_Item);
		EnhancedInputComponent->BindAction(IA_MouseY_Item, ETriggerEvent::Triggered, this, &UPBActionComponent::MouseY_Item);
		EnhancedInputComponent->BindAction(IA_WheelUp_Item, ETriggerEvent::Started, this, &UPBActionComponent::WheelUp_Item);
		EnhancedInputComponent->BindAction(IA_WheelDown_Item, ETriggerEvent::Started, this, &UPBActionComponent::WheelDown_Item);
	}
}

void UPBActionComponent::Click_Default(const FInputActionValue& Value)
{
	if (HitActor)
	{
		HitActor->Interact(PlayerController);
	}
}

void UPBActionComponent::Press_Item(const FInputActionValue& Value)
{
	bIsRotation = true;
}

void UPBActionComponent::Release_Item(const FInputActionValue& Value)
{
	bIsRotation = false;
}

void UPBActionComponent::MouseX_Item(const FInputActionValue& Value)
{
	if (bIsRotation)
	{
		
	}
}

void UPBActionComponent::MouseY_Item(const FInputActionValue& Value)
{
	if (bIsRotation)
	{
		
	}
}

void UPBActionComponent::WheelUp_Item(const FInputActionValue& Value)
{
	
}

void UPBActionComponent::WheelDown_Item(const FInputActionValue& Value)
{
	
}
