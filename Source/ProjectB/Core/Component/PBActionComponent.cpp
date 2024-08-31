// Copyright © 2024, ProjectB. All rights reserved.


#include "PBActionComponent.h"
#include "EnhancedInputComponent.h"
#include "ProjectB/ProjectB.h"
#include "ProjectB/Core/Interface/Interactable.h"
#include "ProjectB/Core/Player/PBPlayerController.h"

#include "ProjectB/Core/Player/PBPlayerPawn.h"
#include "ProjectB/InspectionSystem/PBInspectItem.h"


UPBActionComponent::UPBActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// ---------- Default IA ----------
	static ConstructorHelpers::FObjectFinder<UInputAction> ClickDefaultRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProjectB/Core/Component/InputComponent/Default/IA_Click_Default.IA_Click_Default'"));
	if (ClickDefaultRef.Succeeded())
	{
		IA_Click_Default = ClickDefaultRef.Object;
	}
	// ------------------------------

	// ---------- Inspection system ----------
	static ConstructorHelpers::FObjectFinder<UInputAction> ClickInspectRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProjectB/Core/Component/InputComponent/ItemInspection/IA_Click_Inspect.IA_Click_Inspect'"));
	if (ClickInspectRef.Succeeded())
	{
		IA_Click_Inspection = ClickInspectRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> MouseXInspectRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProjectB/Core/Component/InputComponent/ItemInspection/IA_MouseX_Inspect.IA_MouseX_Inspect'"));
	if (MouseXInspectRef.Succeeded())
	{
		IA_MouseX_Inspection = MouseXInspectRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> MouseYInspectRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProjectB/Core/Component/InputComponent/ItemInspection/IA_MouseY_Inspect.IA_MouseY_Inspect'"));
	if (MouseYInspectRef.Succeeded())
	{
		IA_MouseY_Inspection = MouseYInspectRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> WheelUpInspectRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProjectB/Core/Component/InputComponent/ItemInspection/IA_WheelUp_Inspect.IA_WheelUp_Inspect'"));
	if (WheelUpInspectRef.Succeeded())
	{
		IA_WheelUp_Inspection = WheelUpInspectRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> WheelDownInspectRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProjectB/Core/Component/InputComponent/ItemInspection/IA_WheelDown_Inspect.IA_WheelDown_Inspect'"));
	if (WheelDownInspectRef.Succeeded())
	{
		IA_WheelDown_Inspection = WheelDownInspectRef.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UInputAction> QuitInspectRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProjectB/Core/Component/InputComponent/ItemInspection/IA_Quit_Inspect.IA_Quit_Inspect'"));
	if (QuitInspectRef.Succeeded())
	{
		IA_Quit_Inspection = QuitInspectRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> SpaceBarInspectRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProjectB/Core/Component/InputComponent/ItemInspection/IA_SpaceBar_Inspect.IA_SpaceBar_Inspect'"));
	if (SpaceBarInspectRef.Succeeded())
	{
		IA_SpaceBar_Inspection = SpaceBarInspectRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> HInspectRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProjectB/Core/Component/InputComponent/ItemInspection/IA_H_Inspect.IA_H_Inspect'"));
	if (HInspectRef.Succeeded())
	{
		IA_H_Inspection = HInspectRef.Object;
	}
	// ------------------------------

	// ---------- Communication system ----------
	static ConstructorHelpers::FObjectFinder<UInputAction> ClickCommunicationRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProjectB/Core/Component/InputComponent/Communication/IA_Click__Communication.IA_Click__Communication'"));
	if (ClickCommunicationRef.Succeeded())
	{
		IA_Click_Communication = ClickCommunicationRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> SpaceBarCommunicationRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProjectB/Core/Component/InputComponent/Communication/IA_SpaceBar__Communication.IA_SpaceBar__Communication'"));
	if (SpaceBarCommunicationRef.Succeeded())
	{
		IA_SpaceBar_Communication = SpaceBarCommunicationRef.Object;
	}
	// ------------------------------
	
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

				FName TraceTag = FName(TEXT("InteractTrace"));
				ECollisionChannel TraceChannel = UCollisionProfile::Get()->ConvertToCollisionChannel(false, 0);
				FHitResult HitResult;
				FCollisionQueryParams Params;
				Params.AddIgnoredActor(GetOwner());

				if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, TraceChannel, Params))
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

		EnhancedInputComponent->BindAction(IA_Click_Inspection, ETriggerEvent::Started, this, &UPBActionComponent::Press_Inspection);
		EnhancedInputComponent->BindAction(IA_Click_Inspection, ETriggerEvent::Completed, this, &UPBActionComponent::Release_Inspection);
		EnhancedInputComponent->BindAction(IA_MouseX_Inspection, ETriggerEvent::Triggered, this, &UPBActionComponent::MouseX_Inspection);
		EnhancedInputComponent->BindAction(IA_MouseY_Inspection, ETriggerEvent::Triggered, this, &UPBActionComponent::MouseY_Inspection);
		EnhancedInputComponent->BindAction(IA_WheelUp_Inspection, ETriggerEvent::Started, this, &UPBActionComponent::WheelUp_Inspection);
		EnhancedInputComponent->BindAction(IA_WheelDown_Inspection, ETriggerEvent::Started, this, &UPBActionComponent::WheelDown_Inspection);
		EnhancedInputComponent->BindAction(IA_Quit_Inspection, ETriggerEvent::Started, this, &UPBActionComponent::Quit_Inspection);
		EnhancedInputComponent->BindAction(IA_SpaceBar_Inspection, ETriggerEvent::Started, this, &UPBActionComponent::SpaceBar_Inspection);
		EnhancedInputComponent->BindAction(IA_H_Inspection, ETriggerEvent::Started, this, &UPBActionComponent::H_Inspection);
		
		EnhancedInputComponent->BindAction(IA_Click_Communication, ETriggerEvent::Started, this, &UPBActionComponent::Press_Communication);
		EnhancedInputComponent->BindAction(IA_SpaceBar_Communication, ETriggerEvent::Started, this, &UPBActionComponent::Press_Communication);
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
	OnDialogueAdvance.Broadcast(true);
}

void UPBActionComponent::Release_Inspection(const FInputActionValue& Value)
{
	bIsRotation = false;
}

void UPBActionComponent::MouseX_Inspection(const FInputActionValue& Value)
{
	if (bIsRotation && InspectItem)
	{
		UStaticMeshComponent* ItemMesh = InspectItem->GetStaticMeshComponent();
		
		FQuat CurrentRotation = ItemMesh->GetComponentQuat();
		FQuat DeltaRotation = FQuat(FRotator(0.f, Value.Get<float>() * -4.f, 0.f));
		FQuat NewRotation =  DeltaRotation * CurrentRotation;
		ItemMesh->SetWorldRotation(NewRotation);
	}
}

void UPBActionComponent::MouseY_Inspection(const FInputActionValue& Value)
{
	if (bIsRotation && InspectItem)
	{
		UStaticMeshComponent* ItemMesh = InspectItem->GetStaticMeshComponent();
		
		FQuat CurrentRotation = ItemMesh->GetComponentQuat();
		FQuat DeltaRotation = FQuat(FRotator(Value.Get<float>() * -4.f, 0.f, 0.f));
		FQuat NewRotation =  DeltaRotation * CurrentRotation;
		ItemMesh->SetWorldRotation(NewRotation);
	}
}

void UPBActionComponent::WheelUp_Inspection(const FInputActionValue& Value)
{
	if (InspectItem)
	{
		InspectItem->ZoomIn();
	}
}

void UPBActionComponent::WheelDown_Inspection(const FInputActionValue& Value)
{
	if (InspectItem)
	{
		InspectItem->ZoomOut();
	}
}

void UPBActionComponent::Quit_Inspection(const FInputActionValue& Value)
{
	PlayerController->ExitInspectWidget();
}

void UPBActionComponent::SpaceBar_Inspection(const FInputActionValue& Value)
{
	OnDialogueAdvance.Broadcast(true);
}

void UPBActionComponent::H_Inspection(const FInputActionValue& Value)
{
	PlayerController->VisibilityToggleDialogueInspectWidget();
}

void UPBActionComponent::SetInspectItem(APBInspectItem* InspectItemRef)
{
	InspectItem = InspectItemRef;
}

void UPBActionComponent::DeleteInspectItem()
{
	InspectItem = nullptr;
}

void UPBActionComponent::Press_Communication(const FInputActionValue& Value)
{
	OnDialogueAdvance.Broadcast(true);
}
