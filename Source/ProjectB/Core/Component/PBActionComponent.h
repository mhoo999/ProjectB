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
	UInputAction* IA_Click_Default;

	void Click_Default(const FInputActionValue& Value);

	IInteractable* HitActor;
	IInteractable* LastHitActor;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Settings", meta=(AllowPrivateAccess))
	UInputAction* IA_Click_Item;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Settings", meta=(AllowPrivateAccess))
	UInputAction* IA_MouseX_Item;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Settings", meta=(AllowPrivateAccess))
	UInputAction* IA_MouseY_Item;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Settings", meta=(AllowPrivateAccess))
	UInputAction* IA_WheelUp_Item;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Settings", meta=(AllowPrivateAccess))
	UInputAction* IA_WheelDown_Item;

	void Press_Item(const FInputActionValue& Value);
	void Release_Item(const FInputActionValue& Value);
	void MouseX_Item(const FInputActionValue& Value);
	void MouseY_Item(const FInputActionValue& Value);
	void WheelUp_Item(const FInputActionValue& Value);
	void WheelDown_Item(const FInputActionValue& Value);

	bool bIsRotation;
};
