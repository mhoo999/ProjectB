// Copyright © 2024, ProjectB. All rights reserved.


#include "PBInspectItem.h"

#include "Components/SceneCaptureComponent2D.h"


APBInspectItem::APBInspectItem()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	SetRootComponent(SceneComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMeshComponent->SetupAttachment(RootComponent);
	
	SceneCaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Scene Capture Component"));
	SceneCaptureComponent->SetupAttachment(RootComponent);
	SceneCaptureComponent->SetRelativeLocation(FVector(-110.f, 0.f, 0.f));
	SceneCaptureComponent->FOVAngle = 50.f;
	SceneCaptureComponent->PrimitiveRenderMode = ESceneCapturePrimitiveRenderMode::PRM_UseShowOnlyList;
	SceneCaptureComponent->ShowOnlyComponent(StaticMeshComponent);
}

void APBInspectItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void APBInspectItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UStaticMeshComponent* APBInspectItem::GetStaticMeshComponent() const
{
	return StaticMeshComponent;
}

void APBInspectItem::ZoomOut() const
{
	const float CurrentValue = SceneCaptureComponent->FOVAngle;
	const float NewValue = FMath::Clamp(CurrentValue + 10.0f, 30.f, 80.f);
	SceneCaptureComponent->FOVAngle = NewValue;
}

void APBInspectItem::ZoomIn() const
{
	const float CurrentValue = SceneCaptureComponent->FOVAngle;
	const float NewValue = FMath::Clamp(CurrentValue - 10.0f, 30.f, 80.f);
	SceneCaptureComponent->FOVAngle = NewValue;
}

