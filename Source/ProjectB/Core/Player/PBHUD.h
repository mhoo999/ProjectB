// Copyright © 2024, ProjectB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PBHUD.generated.h"

class UPBCommunicationWidget;
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

	// ---------- Communication System ----------
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="CommunicationSystem", meta=(AllowPrivateAccess))
	TSubclassOf<UPBCommunicationWidget> CommunicateClass;
	UPROPERTY()
	UPBCommunicationWidget* CommunicateWidget;

public:
	void ShowCommunicateWidget(UMaterialInterface* CharacterTexture, FName CharacterName, FString Dialogue) const;

	void HiddenCommunicationWidget();
	// ------------------------------
};
