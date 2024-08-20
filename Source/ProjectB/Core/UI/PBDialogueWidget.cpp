// Copyright © 2024, ProjectB. All rights reserved.


#include "PBDialogueWidget.h"

#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectB/ProjectB.h"
#include "ProjectB/Core/Component/PBActionComponent.h"
#include "ProjectB/Core/Player/PBPlayerPawn.h"
#include "Sound/SoundCue.h"


void UPBDialogueWidget::NativeConstruct()
{
	Super::NativeConstruct();

	TypingSpeed = 0.05f;
	bIsDialogueComplete = false;
	DialogueTextBlock->SetAutoWrapText(true);

	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (APBPlayerPawn* PlayerPawn = Cast<APBPlayerPawn>(PlayerController->GetPawn()))
		{
			if (UPBActionComponent* ActionComponent = PlayerPawn->GetComponentByClass<UPBActionComponent>())
			{
				ActionComponent->OnDialogueAdvance.AddUObject(this, &UPBDialogueWidget::OnNextLineOrClose);
			}
		}
	}
}

void UPBDialogueWidget::ShowDialogue(FString DialogueText, FName Speaker)
{
	if (FadeInAnimation)
	{
		PlayAnimation(FadeInAnimation);
	}
	
	FullText = DialogueText;
	FullText.ParseIntoArray(DialogueLines, TEXT("/"), false);

	if (!Speaker.IsNone())
	{
		SpeakerBlock->SetText(FText::FromName(Speaker));
	}
	else
	{
		SpeakerBlock->SetText(FText::FromString(TEXT("")));
	}

	bIsDialogueComplete = false;
	CurrentLineIndex = 0;
	CurrentText = "";
	CurrentCharIndex = 0;
	GetWorld()->GetTimerManager().ClearTimer(TypingTimerHandle);

	GetWorld()->GetTimerManager().SetTimer(TypingTimerHandle, this, &UPBDialogueWidget::TypeNextChar, TypingSpeed, true);
}

void UPBDialogueWidget::OnNextLineOrClose(bool Value)
{
	PBLOG_S(Warning);
	
	if (bIsDialogueComplete)
	{
		if (CurrentLineIndex < DialogueLines.Num() - 1)
		{
			CurrentLineIndex++;
			CurrentText = "";
			CurrentCharIndex = 0;
			bIsDialogueComplete = false;

			GetWorld()->GetTimerManager().SetTimer(TypingTimerHandle, this, &UPBDialogueWidget::TypeNextChar, TypingSpeed, true);
		}
		// else
		// {
		// 	if (FadeOutAnimation)
		// 	{
		// 		PlayAnimation(FadeOutAnimation);
		// 	}
		// 	SetVisibility(ESlateVisibility::Hidden);
		// 	SpeakerBlock->SetText(FText::FromString(TEXT("")));
		// 	DialogueTextBlock->SetText(FText::FromString(TEXT("")));
		// }
	}
	else
	{
		CurrentText.Append(DialogueLines[CurrentLineIndex]);
		DialogueTextBlock->SetText(FText::FromString(CurrentText));

		if (TypingSound)
		{
			UGameplayStatics::PlaySound2D(this, TypingSound);
		}

		GetWorld()->GetTimerManager().ClearTimer(TypingTimerHandle);
		bIsDialogueComplete = true;
	}
}

void UPBDialogueWidget::TypeNextChar()
{
	PBLOG_S(Warning);
	
	if (CurrentCharIndex < DialogueLines[CurrentLineIndex].Len())
	{
		CurrentText.AppendChar(DialogueLines[CurrentLineIndex][CurrentCharIndex]);
		DialogueTextBlock->SetText(FText::FromString(CurrentText));

		if (TypingSound)
		{
			UGameplayStatics::PlaySound2D(this, TypingSound);
		}

		CurrentCharIndex++;
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(TypingTimerHandle);
		bIsDialogueComplete = true;
	}
}
