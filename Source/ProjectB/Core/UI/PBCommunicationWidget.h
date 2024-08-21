// Copyright © 2024, ProjectB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PBCommunicationWidget.generated.h"

class UImage;
class UPBDialogueWidget;
/**
 * 
 */
UCLASS()
class PROJECTB_API UPBCommunicationWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta=(BindWidget))
	UImage* CharacterFrame;
	
	UPROPERTY(meta=(BindWidget))
	UPBDialogueWidget* DialogueWidget;

	UPROPERTY(meta=(BindWidgetAnim), Transient)
	UWidgetAnimation* FadeInAnimation;

	UPROPERTY(meta=(BindWidgetAnim), Transient)
	UWidgetAnimation* FadeOutAnimation;

public:
	void ShowCommunicateWidget(UMaterialInterface* CharacterTexture, FName Speaker, const FString& DialogueText);
	
	void ShowDialogueWidget(FName Speaker, const FString& DialogueText) const;
	
};
