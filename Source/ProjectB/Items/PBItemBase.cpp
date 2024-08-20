// Copyright © 2024, ProjectB. All rights reserved.


#include "PBItemBase.h"

#include "ProjectB/Core/Player/PBPlayerController.h"


APBItemBase::APBItemBase()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	SetRootComponent(MeshComponent);
	MeshComponent->SetRenderCustomDepth(false);
	MeshComponent->SetCustomDepthStencilValue(1);

	ItemMesh = MeshComponent->GetStaticMesh();
	ItemScale = FVector(1.f, 1.f, 1.f);
}

void APBItemBase::BeginPlay()
{
	Super::BeginPlay();

	if (ItemMesh == nullptr)
	{
		ItemMesh = MeshComponent->GetStaticMesh();
	}
}

void APBItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APBItemBase::Interact(APlayerController* Controller)
{
	if (APBPlayerController* PlayerController = Cast<APBPlayerController>(Controller))
	{
		PlayerController->ItemInspection(ItemMesh, ItemName, ItemDescription, ItemScale);
	}
}

void APBItemBase::SetOutline(bool bOutlineEnabled)
{
	MeshComponent->SetRenderCustomDepth(bOutlineEnabled);
}

