// Copyright © 2024, ProjectB. All rights reserved.


#include "PBNPCBase.h"

#include "Components/WidgetComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "ProjectB/ProjectB.h"
#include "ProjectB/Core/Component/PBCameraComponent.h"
#include "ProjectB/Core/Player/PBPlayerController.h"
#include "ProjectB/Core/Player/PBPlayerPawn.h"


APBNPCBase::APBNPCBase()
{
	PrimaryActorTick.bCanEverTick = true;

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget Component"));
	SetRootComponent(WidgetComponent);
	WidgetComponent->SetCollisionProfileName(TEXT("InteractActor"));
}

void APBNPCBase::BeginPlay()
{
	Super::BeginPlay();

	// Code that looks at the player when it starts
	// FRotator LookAtRotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), FVector(0.f, 0.f, 0.f));
	// SetActorRotation(LookAtRotator);
	
	APBPlayerPawn* Player = Cast<APBPlayerPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	PreviousPlayerCameraRotation = Player->GetCameraRotation();
}

void APBNPCBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FaceToPlayerCamera();
}

void APBNPCBase::Interact(APlayerController* Controller)
{
	if (APBPlayerController* PlayerController = Cast<APBPlayerController>(Controller))
	{
		PlayerController->Communication(CharacterTexture, CharacterName, Dialogue);
	}
}

void APBNPCBase::SetOutline(bool bOutlineEnabled)
{
	WidgetComponent->SetRenderCustomDepth(bOutlineEnabled);
}

void APBNPCBase::CheckActorPosition()
{
	const AActor* Player = GetWorld()->GetFirstPlayerController()->GetPawn();
	const FVector PlayerLocation = Player->GetActorLocation();
	const FVector TargetLocation = GetActorLocation();

	const FVector PlayerRight = Player->GetActorRightVector();

	const FVector DirectionToTarget = TargetLocation - PlayerLocation;

	const float DotProductResult = FVector::DotProduct(PlayerRight, DirectionToTarget);

	if (DotProductResult > 0)
	{
		bIsPlaceOnRight = true;
	}
	else
	{
		bIsPlaceOnRight = false;
	}
}

void APBNPCBase::FaceToPlayerCamera()
{
	APBPlayerPawn* Player = Cast<APBPlayerPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	FRotator CurrentPlayerCameraRotation = Player->GetCameraRotation();

	FRotator RotationChange = CurrentPlayerCameraRotation - PreviousPlayerCameraRotation;
	
	FRotator ActorRotation = FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw + RotationChange.Yaw, GetActorRotation().Roll);
	SetActorRotation(ActorRotation);

	PreviousPlayerCameraRotation = CurrentPlayerCameraRotation;
}

