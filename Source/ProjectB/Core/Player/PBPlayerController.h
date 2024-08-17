// Copyright © 2024, ProjectB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PBPlayerController.generated.h"

class AItemBase;
class APBPlayerPawn;
class UCameraComponent;
/**
 * 
 */
UCLASS()
class PROJECTB_API APBPlayerController : public APlayerController
{
	GENERATED_BODY()

	APBPlayerController();

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	APBPlayerPawn* PlayerPawn;

public:
	void ShowItemDetails(AItemBase* Item);
};
