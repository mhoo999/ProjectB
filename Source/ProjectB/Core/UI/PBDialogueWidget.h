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
	// show dialogue function
	UFUNCTION(BlueprintCallable, Category="Dialogue")
	void ShowDialogue(FString DialogueText, FName Speaker);

	// Next line output or skip function
	UFUNCTION(BlueprintCallable, Category="Dialogue")
	void OnNextLineOrClose(bool Value);
	
protected:
	virtual void NativeConstruct() override;
	
private:
	// a character-by-character function
	void TypeNextChar();
	
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
	
	UPROPERTY(EditAnywhere, Category="Sound")
	USoundCue* TypingSound;
	
	FTimerHandle TypingTimerHandle;
	FString FullText;
	FString CurrentText;
	int32 CurrentCharIndex;
	int32 CurrentLineIndex;
	TArray<FString> DialogueLines;
	bool bIsDialogueComplete;

};
