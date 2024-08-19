// Copyright © 2024, ProjectB. All rights reserved.


#include "PBInspectItem.h"

#include "Components/SceneCaptureComponent2D.h"


APBInspectItem::APBInspectItem()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	SetRootComponent(StaticMeshComponent);

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

UStaticMeshComponent* APBInspectItem::GetStaticMeshComponent()
{
	return StaticMeshComponent;
}

