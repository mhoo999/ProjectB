// Copyright © 2024, ProjectB. All rights reserved.


#include "PBInspectWidget.h"

#include "PBDialogueWidget.h"
#include "Components/TextBlock.h"


void UPBInspectWidget::ShowInspectWidget(FName Speaker, const FString& DialogueText)
{
	if (FadeInAnimation)
	{
		PlayAnimation(FadeInAnimation);
	}

	ShowDialogueWidget(Speaker, DialogueText);
}

void UPBInspectWidget::ShowDialogueWidget(FName Speaker, const FString& DialogueText) const
{
	DialogueWidget->ShowDialogue(Speaker, DialogueText);
	DialogueWidget->SetVisibility(ESlateVisibility::Visible);
}

void UPBInspectWidget::VisibilityToggleDialogue() const
{
	if (DialogueWidget->GetVisibility() == ESlateVisibility::Visible)
	{
		DialogueWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		DialogueWidget->SetVisibility(ESlateVisibility::Visible);
	}
}
