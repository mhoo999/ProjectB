// Copyright © 2024, ProjectB. All rights reserved.


#include "InspectWidget.h"

#include "Components/TextBlock.h"

void UInspectWidget::SetItemInfo(FText Name, FText Description)
{
	ItemName->SetText(Name);
	ItemDescription->SetText(Description);
}
