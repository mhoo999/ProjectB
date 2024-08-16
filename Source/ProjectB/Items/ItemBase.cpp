// Copyright © 2024, ProjectB. All rights reserved.


#include "ItemBase.h"


AItemBase::AItemBase()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	SetRootComponent(MeshComponent);
	MeshComponent->SetRenderCustomDepth(false);
	MeshComponent->SetCustomDepthStencilValue(1);
}

void AItemBase::BeginPlay()
{
	Super::BeginPlay();
}

void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AItemBase::Interact()
{
	
}

void AItemBase::SetOutline(bool bOutlineEnabled)
{
	MeshComponent->SetRenderCustomDepth(bOutlineEnabled);
}

