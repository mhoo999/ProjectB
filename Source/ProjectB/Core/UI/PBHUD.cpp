// Copyright © 2024, ProjectB. All rights reserved.


#include "PBHUD.h"

#include "UIBlur.h"
#include "Blueprint/UserWidget.h"
#include "ProjectB/Items/PBItemBase.h"

APBHUD::APBHUD()
{
	
}

void APBHUD::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(BlurUIClass))
	{
		BlurUIWidget = Cast<UUIBlur>(CreateWidget(GetWorld(), BlurUIClass));

		if (IsValid(BlurUIWidget))
		{
			BlurUIWidget->AddToViewport();
			BlurUIWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	
}

void APBHUD::ShowBlurUI()
{
	BlurUIWidget->SetVisibility(ESlateVisibility::Visible);
}
