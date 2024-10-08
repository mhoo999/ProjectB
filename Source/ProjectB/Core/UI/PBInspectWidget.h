﻿// Copyright © 2024, ProjectB. All rights reserved.

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

private:
	UPROPERTY(meta=(BindWidget))
	UPBDialogueWidget* DialogueWidget;

	UPROPERTY(meta=(BindWidgetAnim), Transient)
	UWidgetAnimation* FadeInAnimation;

	UPROPERTY(meta=(BindWidgetAnim), Transient)
	UWidgetAnimation* FadeOutAnimation;

public:
	void ShowInspectWidget(FName Speaker, const FString& DialogueText);
	
	void ShowDialogueWidget(FName Speaker, const FString& DialogueText) const;

	void VisibilityToggleDialogue() const;
};
