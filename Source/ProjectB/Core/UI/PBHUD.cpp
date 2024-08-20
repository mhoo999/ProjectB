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

void APBHUD::ShowInspectWidget(FText Name, FString Description)
{
	if (IsValid(InspectWidget))
	{
		InspectWidget->SetVisibility(ESlateVisibility::Visible);

		if (!Description.IsEmpty())
		{
			InspectWidget->ShowDialogueWidget(Description, FName(""));
		}
	}
}

void APBHUD::HiddenInspectWidget()
{
	if (IsValid(InspectWidget))
	{
		InspectWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void APBHUD::VisibilityToggleDialogueInspectWidget()
{
	if (IsValid(InspectWidget))
	{
		InspectWidget->VisibilityToggleDialogue();
	}
}
