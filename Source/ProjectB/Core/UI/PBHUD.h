// Copyright © 2024, ProjectB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PBHUD.generated.h"

class APBItemBase;
class UInspectWidget;
/**
 * 
 */
UCLASS()
class PROJECTB_API APBHUD : public AHUD
{
	GENERATED_BODY()

	APBHUD();

	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="InspectionSystem", meta=(AllowPrivateAccess))
	TSubclassOf<UInspectWidget> InspectClass;
	UInspectWidget* InspectWidget;

public:
	void ShowInspectWidget(FText Name, FText Description);
	void HiddenInspectWidget();
};
