// Copyright © 2024, ProjectB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PBPlayerPawn.generated.h"

class UPBItemInspectionComponent;
class UPBCameraComponent;
class UPBActionComponent;
class UCameraComponent;
class UInputMappingContext;

// Input delegate
DECLARE_MULTICAST_DELEGATE_OneParam(FInputDelegate, UInputComponent*);

UCLASS()
class PROJECTB_API APBPlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	APBPlayerPawn();

	// Input delegate
	FInputDelegate OnSetupInputDelegate;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Settings", meta=(AllowPrivateAccess))
	UCameraComponent* PlayerCamera;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Settings", meta=(AllowPrivateAccess))
	UPBActionComponent* ActionComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Settings", meta=(AllowPrivateAccess))
	UPBCameraComponent* CameraComponent;
};
