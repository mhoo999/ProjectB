// Copyright © 2024, ProjectB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PBPlayerPawn.generated.h"

class UPBCameraComponent;
class UPBActionComponent;
class UCameraComponent;
class UInputMappingContext;

DECLARE_MULTICAST_DELEGATE_OneParam(FInputDelegate, UInputComponent*);

UCLASS()
class PROJECTB_API APBPlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	APBPlayerPawn();

	FInputDelegate OnSetupInputDelegate;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Settings", meta=(AllowPrivateAccess))
	UCameraComponent* PlayerCamera;
	
	UPROPERTY(EditDefaultsOnly)
	UPBActionComponent* ActionComponent;

	UPROPERTY(EditDefaultsOnly)
	UPBCameraComponent* CameraComponent;
};
