// Copyright © 2024, ProjectB. All rights reserved.


#include "PBCommunicationWidget.h"

#include "PBDialogueWidget.h"
#include "Components/Image.h"

void UPBCommunicationWidget::ShowCommunicateWidget(UMaterialInterface* CharacterTexture, FName Speaker, const FString& DialogueText)
{
	if (FadeInAnimation)
	{
		PlayAnimation(FadeInAnimation);
	}
	
	CharacterFrame->SetBrushFromMaterial(CharacterTexture);
	ShowDialogueWidget(Speaker, DialogueText);
}

void UPBCommunicationWidget::ShowDialogueWidget(FName Speaker, const FString& DialogueText) const
{
	DialogueWidget->ShowDialogue(Speaker, DialogueText);
	DialogueWidget->SetVisibility(ESlateVisibility::Visible);
}
