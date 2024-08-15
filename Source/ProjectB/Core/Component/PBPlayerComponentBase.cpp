// Copyright © 2024, ProjectB. All rights reserved.


#include "PBPlayerComponentBase.h"

#include "ProjectB/Core/Player/PBPlayerPawn.h"


UPBPlayerComponentBase::UPBPlayerComponentBase()
{
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;
}

void UPBPlayerComponentBase::BeginPlay()
{
	Super::BeginPlay();
}

void UPBPlayerComponentBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPBPlayerComponentBase::InitializeComponent()
{
	Super::InitializeComponent();
	
	PlayerPawn = Cast<APBPlayerPawn>(GetOwner());
	PlayerPawn->OnSetupInputDelegate.AddUObject(this, &UPBPlayerComponentBase::SetupPlayerInput);
}

void UPBPlayerComponentBase::SetupPlayerInput(UInputComponent* PlayerInputComponent)
{
	// virtual function
}

