// Copyright © 2024, ProjectB. All rights reserved.


#include "PBHUD.h"

#include "Blueprint/UserWidget.h"
#include "ProjectB/Core/UI/PBCommunicationWidget.h"
#include "ProjectB/Core/UI/PBInspectWidget.h"
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

	if (IsValid(CommunicateClass))
	{
		CommunicateWidget = Cast<UPBCommunicationWidget>(CreateWidget(GetWorld(), CommunicateClass));

		if (IsValid(CommunicateWidget))
		{
			CommunicateWidget->AddToViewport();
			CommunicateWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void APBHUD::ShowInspectWidget(FText Name, const FString& Description) const
{
	if (IsValid(InspectWidget))
	{
		InspectWidget->SetVisibility(ESlateVisibility::Visible);
		InspectWidget->ShowInspectWidget(FName(""), Description);
	}
}

void APBHUD::HiddenInspectWidget() const
{
	if (IsValid(InspectWidget))
	{
		InspectWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void APBHUD::VisibilityToggleDialogueInspectWidget() const
{
	if (IsValid(InspectWidget))
	{
		InspectWidget->VisibilityToggleDialogue();
	}
}

void APBHUD::ShowCommunicateWidget(UMaterialInterface* CharacterTexture, FName CharacterName, FString Dialogue) const
{
	if (IsValid(CommunicateWidget))
	{
		CommunicateWidget->SetVisibility(ESlateVisibility::Visible);
		CommunicateWidget->ShowCommunicateWidget(CharacterTexture, CharacterName, Dialogue);
	}
}

void APBHUD::HiddenCommunicationWidget()
{
	if (IsValid(CommunicateWidget))
	{
		CommunicateWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}
