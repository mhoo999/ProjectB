// Copyright © 2024, ProjectB. All rights reserved.


#include "PBNPCBase.h"

#include "Components/WidgetComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "ProjectB/Core/Player/PBPlayerController.h"
#include "ProjectB/Core/Player/PBPlayerPawn.h"


APBNPCBase::APBNPCBase()
{
	PrimaryActorTick.bCanEverTick = true;

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget Component"));
	SetRootComponent(WidgetComponent);
}

void APBNPCBase::BeginPlay()
{
	Super::BeginPlay();
	
	FRotator LookAtRotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), FVector(0.f, 0.f, 0.f));
	SetActorRotation(LookAtRotator);
}

void APBNPCBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
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

