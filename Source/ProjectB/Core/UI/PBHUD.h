// Copyright © 2024, ProjectB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PBHUD.generated.h"

class AItemBase;
class UUIItemDetails;
/**
 * 
 */
UCLASS()
class PROJECTB_API APBHUD : public AHUD
{
	GENERATED_BODY()

	APBHUD();

	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="ItemUI", meta=(AllowPrivateAccess))
	TSubclassOf<UUIItemDetails> ItemDetailsClass;
	UUIItemDetails* ItemDetailsWidget;

public:
	void ShowItemDetailsWidget(AItemBase* Item);
};
