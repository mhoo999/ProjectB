// Copyright © 2024, ProjectB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PBPlayerController.generated.h"

class UInputMappingContext;
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

	virtual void OnPossess(APawn* InPawn) override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Settings", meta=(AllowPrivateAccess))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Settings", meta=(AllowPrivateAccess))
	UInputMappingContext* ItemInspectionContext;
	
	UPROPERTY(EditDefaultsOnly)
	APBPlayerPawn* PlayerPawn;

	bool bIsUIOpen;

public:
	void ItemInspection(AItemBase* Item);

	void SetUIOpenTrue();
	void SetUIOpenFalse();
};
