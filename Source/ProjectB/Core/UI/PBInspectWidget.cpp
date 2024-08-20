// Copyright © 2024, ProjectB. All rights reserved.


#include "PBInspectWidget.h"

#include "Components/TextBlock.h"

void UPBInspectWidget::SetItemInfo(FText Name, FText Description)
{
	ItemName->SetText(Name);
	ItemDescription->SetText(Description);
}
