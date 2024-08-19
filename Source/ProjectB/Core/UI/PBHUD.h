// Copyright © 2024, ProjectB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PBHUD.generated.h"

class AItemBase;
class UUIBlur;
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
	TSubclassOf<UUIBlur> BlurUIClass;
	UUIBlur* BlurUIWidget;

public:
	void ShowBlurUI();
};
