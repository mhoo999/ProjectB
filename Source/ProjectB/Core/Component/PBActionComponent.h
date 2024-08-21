// Copyright © 2024, ProjectB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PBPlayerComponentBase.h"
#include "InputActionValue.h"
#include "PBActionComponent.generated.h"


class APBInspectItem;
class IInteractable;
class UInputAction;

// Dialogue skip delegate
DECLARE_MULTICAST_DELEGATE_OneParam(FOnDialogueAdvance, bool);

UCLASS()
class PROJECTB_API UPBActionComponent : public UPBPlayerComponentBase
{
	GENERATED_BODY()

public:
	UPBActionComponent();

	// Dialogue skip delegate
	FOnDialogueAdvance OnDialogueAdvance;

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void SetupPlayerInput(UInputComponent* PlayerInputComponent) override;

	// ---------- Default IMC ----------
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Default", meta=(AllowPrivateAccess))
	UInputAction* IA_Click_Default;

	void Click_Default(const FInputActionValue& Value);

	IInteractable* HitActor;
	IInteractable* LastHitActor;
	// ------------------------------

	// ---------- Inspection system IMC ----------
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Inspection", meta=(AllowPrivateAccess))
	UInputAction* IA_Click_Inspection;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Inspection", meta=(AllowPrivateAccess))
	UInputAction* IA_MouseX_Inspection;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Inspection", meta=(AllowPrivateAccess))
	UInputAction* IA_MouseY_Inspection;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Inspection", meta=(AllowPrivateAccess))
	UInputAction* IA_WheelUp_Inspection;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Inspection", meta=(AllowPrivateAccess))
	UInputAction* IA_WheelDown_Inspection;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Inspection", meta=(AllowPrivateAccess))
	UInputAction* IA_Quit_Inspection;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Inspection", meta=(AllowPrivateAccess))
	UInputAction* IA_SpaceBar_Inspection;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Inspection", meta=(AllowPrivateAccess))
	UInputAction* IA_H_Inspection;

	void Press_Inspection(const FInputActionValue& Value);
	void Release_Inspection(const FInputActionValue& Value);
	void MouseX_Inspection(const FInputActionValue& Value);
	void MouseY_Inspection(const FInputActionValue& Value);
	void WheelUp_Inspection(const FInputActionValue& Value);
	void WheelDown_Inspection(const FInputActionValue& Value);
	void Quit_Inspection(const FInputActionValue& Value);
	void SpaceBar_Inspection(const FInputActionValue& Value);
	void H_Inspection(const FInputActionValue& Value);
	
	bool bIsRotation;

	UPROPERTY()
	APBInspectItem* InspectItem;

public:
	void SetInspectItem(APBInspectItem* InspectItemRef);
	void DeleteInspectItem();
	// ------------------------------
	
};
