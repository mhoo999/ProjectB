// Copyright © 2024, ProjectB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PBDialogueWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class PROJECTB_API UPBDialogueWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Dialogue")
	void ShowDialogue(FString DialogueText, FName Speaker);

	UFUNCTION(BlueprintCallable, Category="Dialogue")
	void OnNextLineOrClose(bool Value);
	
protected:
	virtual void NativeConstruct() override;
	
private:
	void TypeNextChar();
	
	FTimerHandle TypingTimerHandle;
	FString FullText;
	FString CurrentText;
	int32 CurrentCharIndex;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Dialogue", meta=(AllowPrivateAccess))
	float TypingSpeed;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* SpeakerBlock;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* DialogueTextBlock;

	UPROPERTY(meta=(BindWidgetAnim), Transient)
	UWidgetAnimation* FadeInAnimation;

	UPROPERTY(meta=(BindWidgetAnim), Transient)
	UWidgetAnimation* FadeOutAnimation;

	int32 CurrentLineIndex;
	TArray<FString> DialogueLines;
	bool bIsDialogueComplete;

	UPROPERTY(EditAnywhere, Category="Sound")
	USoundCue* TypingSound;
};
