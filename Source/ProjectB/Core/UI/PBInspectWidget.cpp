// Copyright © 2024, ProjectB. All rights reserved.


#include "PBInspectWidget.h"

#include "PBDialogueWidget.h"
#include "Components/TextBlock.h"


void UPBInspectWidget::ShowDialogueWidget(FString DialogueText, FName Speaker)
{
	DialogueWidget->ShowDialogue(DialogueText, Speaker);
	DialogueWidget->SetVisibility(ESlateVisibility::Visible);
}

void UPBInspectWidget::VisibilityToggleDialogue()
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
