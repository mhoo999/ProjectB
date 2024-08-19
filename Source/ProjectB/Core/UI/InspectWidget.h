// Copyright © 2024, ProjectB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InspectWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class PROJECTB_API UInspectWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta=(BindWidget), meta=(AllowPrivateAccess))
	UTextBlock* ItemName;

	UPROPERTY(meta=(BindWidget), meta=(AllowPrivateAccess))
	UTextBlock* ItemDescription;

public:
	void SetItemInfo(FText Name, FText Description);
};
