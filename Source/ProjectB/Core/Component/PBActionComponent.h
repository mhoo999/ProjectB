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
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Default", meta=(AllowPrivateAccess))
	UInputAction* IA_Click_Default;

	void Click_Default(const FInputActionValue& Value);

	IInteractable* HitActor;
	IInteractable* LastHitActor;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Inspection", meta=(AllowPrivateAccess))
	UInputAction* IA_Click_Ispection;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Inspection", meta=(AllowPrivateAccess))
	UInputAction* IA_MouseX_Ispection;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Inspection", meta=(AllowPrivateAccess))
	UInputAction* IA_MouseY_Ispection;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Inspection", meta=(AllowPrivateAccess))
	UInputAction* IA_WheelUp_Ispection;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Inspection", meta=(AllowPrivateAccess))
	UInputAction* IA_WheelDown_Ispection;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Inspection", meta=(AllowPrivateAccess))
	UInputAction* IA_Quit_Ispection;

	void Press_Inspection(const FInputActionValue& Value);
	void Release_Inspection(const FInputActionValue& Value);
	void MouseX_Inspection(const FInputActionValue& Value);
	void MouseY_Inspection(const FInputActionValue& Value);
	void WheelUp_Inspection(const FInputActionValue& Value);
	void WheelDown_Inspection(const FInputActionValue& Value);
	void Quit_Inspection(const FInputActionValue& Value);

	bool bIsRotation;
};
