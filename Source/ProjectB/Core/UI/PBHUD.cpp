// Copyright © 2024, ProjectB. All rights reserved.


#include "PBHUD.h"

#include "PBInspectWidget.h"
#include "Blueprint/UserWidget.h"
#include "ProjectB/Items/PBItemBase.h"

APBHUD::APBHUD()
{
	
}

void APBHUD::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(InspectClass))
	{
		InspectWidget = Cast<UPBInspectWidget>(CreateWidget(GetWorld(), InspectClass));

		if (IsValid(InspectWidget))
		{
			InspectWidget->AddToViewport();
			InspectWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void APBHUD::ShowInspectWidget(FText Name, FText Description)
{
	if (IsValid(InspectWidget))
	{
		InspectWidget->SetVisibility(ESlateVisibility::Visible);
		InspectWidget->SetItemInfo(Name, Description);
	}
}

void APBHUD::HiddenInspectWidget()
{
	if (IsValid(InspectWidget))
	{
		InspectWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}
