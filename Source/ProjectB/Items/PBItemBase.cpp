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
}

void APBItemBase::BeginPlay()
{
	Super::BeginPlay();
}

void APBItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APBItemBase::Interact(APlayerController* Controller)
{
	// PlayerController에 this를 전달하고
	// this를 인수로 HUD ItemUI를 출력한다
	// this는 메시와 출력 문장, 선택 UI
	if (APBPlayerController* PlayerController = Cast<APBPlayerController>(Controller))
	{
		PlayerController->ItemInspection(this);
	}
}

void APBItemBase::SetOutline(bool bOutlineEnabled)
{
	MeshComponent->SetRenderCustomDepth(bOutlineEnabled);
}

UStaticMeshComponent* APBItemBase::GetStaticMeshComponent()
{
	return MeshComponent;
}

