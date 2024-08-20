// Copyright © 2024, ProjectB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PBInspectWidget.generated.h"

class UPBDialogueWidget;
class UTextBlock;
/**
 * 
 */
UCLASS()
class PROJECTB_API UPBInspectWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta=(BindWidget))
	UPBDialogueWidget* DialogueWidget;

public:
	void ShowDialogueWidget(FString DialogueText, FName Speaker);

	void VisibilityToggleDialogue();
};
