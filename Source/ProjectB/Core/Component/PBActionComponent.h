// Copyright © 2024, ProjectB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PBPlayerComponentBase.h"
#include "InputActionValue.h"
#include "PBActionComponent.generated.h"


class IInteractable;
class UInputAction;

UCLASS()
class PROJECTB_API UPBActionComponent : public UPBPlayerComponentBase
{
	GENERATED_BODY()

public:
	UPBActionComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void SetupPlayerInput(UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Settings", meta=(AllowPrivateAccess))
	UInputAction* IA_Click;
	
	void Click(const FInputActionValue& Value);

	IInteractable* HitActor;
	IInteractable* LastHitActor;
	
};
