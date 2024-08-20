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

	static ConstructorHelpers::FObjectFinder<UInputAction> ClickInspectRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProjectB/Core/Component/InputComponent/ItemInspection/IA_Click_Inspect.IA_Click_Inspect'"));
	if (ClickInspectRef.Succeeded())
	{
		IA_Click_Ispection = ClickInspectRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> MouseXInspectRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProjectB/Core/Component/InputComponent/ItemInspection/IA_MouseX_Inspect.IA_MouseX_Inspect'"));
	if (MouseXInspectRef.Succeeded())
	{
		IA_MouseX_Ispection = MouseXInspectRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> MouseYInspectRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProjectB/Core/Component/InputComponent/ItemInspection/IA_MouseY_Inspect.IA_MouseY_Inspect'"));
	if (MouseYInspectRef.Succeeded())
	{
		IA_MouseY_Ispection = MouseYInspectRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> WheelUpInspectRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProjectB/Core/Component/InputComponent/ItemInspection/IA_WheelUp_Inspect.IA_WheelUp_Inspect'"));
	if (WheelUpInspectRef.Succeeded())
	{
		IA_WheelUp_Ispection = WheelUpInspectRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> WheelDownInspectRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProjectB/Core/Component/InputComponent/ItemInspection/IA_WheelDown_Inspect.IA_WheelDown_Inspect'"));
	if (WheelDownInspectRef.Succeeded())
	{
		IA_WheelDown_Ispection = WheelDownInspectRef.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UInputAction> QuitInspectRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProjectB/Core/Component/InputComponent/ItemInspection/IA_Quit_Inspect.IA_Quit_Inspect'"));
	if (QuitInspectRef.Succeeded())
	{
		IA_Quit_Ispection = QuitInspectRef.Object;
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

		EnhancedInputComponent->BindAction(IA_Click_Ispection, ETriggerEvent::Started, this, &UPBActionComponent::Press_Inspection);
		EnhancedInputComponent->BindAction(IA_Click_Ispection, ETriggerEvent::Completed, this, &UPBActionComponent::Release_Inspection);
		EnhancedInputComponent->BindAction(IA_MouseX_Ispection, ETriggerEvent::Triggered, this, &UPBActionComponent::MouseX_Inspection);
		EnhancedInputComponent->BindAction(IA_MouseY_Ispection, ETriggerEvent::Triggered, this, &UPBActionComponent::MouseY_Inspection);
		EnhancedInputComponent->BindAction(IA_WheelUp_Ispection, ETriggerEvent::Started, this, &UPBActionComponent::WheelUp_Inspection);
		EnhancedInputComponent->BindAction(IA_WheelDown_Ispection, ETriggerEvent::Started, this, &UPBActionComponent::WheelDown_Inspection);
		EnhancedInputComponent->BindAction(IA_Quit_Ispection, ETriggerEvent::Started, this, &UPBActionComponent::Quit_Inspection);
	}
}

void UPBActionComponent::Click_Default(const FInputActionValue& Value)
{
	if (HitActor)
	{
		HitActor->Interact(PlayerController);
		HitActor->SetOutline(false);
	}
}

void UPBActionComponent::Press_Inspection(const FInputActionValue& Value)
{
	bIsRotation = true;
}

void UPBActionComponent::Release_Inspection(const FInputActionValue& Value)
{
	bIsRotation = false;
}

void UPBActionComponent::MouseX_Inspection(const FInputActionValue& Value)
{
	if (bIsRotation)
	{
		
	}
}

void UPBActionComponent::MouseY_Inspection(const FInputActionValue& Value)
{
	if (bIsRotation)
	{
		
	}
}

void UPBActionComponent::WheelUp_Inspection(const FInputActionValue& Value)
{
	
}

void UPBActionComponent::WheelDown_Inspection(const FInputActionValue& Value)
{
	
}

void UPBActionComponent::Quit_Inspection(const FInputActionValue& Value)
{
	PlayerController->ExitInspectWidget();
	PBLOG_S(Warning);
}
