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
};
