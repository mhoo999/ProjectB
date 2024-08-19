﻿// Copyright © 2024, ProjectB. All rights reserved.


#include "PBHUD.h"

#include "UIItemDetails.h"
#include "Blueprint/UserWidget.h"
#include "ProjectB/Items/ItemBase.h"

APBHUD::APBHUD()
{
	
}

void APBHUD::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(ItemDetailsClass))
	{
		ItemDetailsWidget = Cast<UUIItemDetails>(CreateWidget(GetWorld(), ItemDetailsClass));

		if (IsValid(ItemDetailsWidget))
		{
			ItemDetailsWidget->AddToViewport();
			ItemDetailsWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	
}

void APBHUD::ShowItemDetailsWidget(AItemBase* Item)
{
	ItemDetailsWidget->SetVisibility(ESlateVisibility::Visible);
	
}
