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
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUIOpenDelegate, bool, bIsUIOpen);

UCLASS()
class PROJECTB_API APBPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	APBPlayerController();

	FUIOpenDelegate UIOpenDelegate;

private:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	APBPlayerPawn* PlayerPawn;

	bool bIsUIOpen;

public:
	void ShowItemDetails(AItemBase* Item);

	void SetUIOpenTrue();
	void SetUIOpenFalse();
};
