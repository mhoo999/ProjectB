// Copyright © 2024, ProjectB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PBHUD.generated.h"

class APBItemBase;
class UPBInspectWidget;
/**
 * 
 */
UCLASS()
class PROJECTB_API APBHUD : public AHUD
{
	GENERATED_BODY()

	APBHUD();

	virtual void BeginPlay() override;

	// ---------- Inspection system ----------
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="InspectionSystem", meta=(AllowPrivateAccess))
	TSubclassOf<UPBInspectWidget> InspectClass;
	UPROPERTY()
	UPBInspectWidget* InspectWidget;

public:
	void ShowInspectWidget(FText Name, const FString& Description) const;
	
	void HiddenInspectWidget() const;
	
	void VisibilityToggleDialogueInspectWidget() const;
	// ------------------------------

	
};
