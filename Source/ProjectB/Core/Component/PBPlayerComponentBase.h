// Copyright © 2024, ProjectB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PBPlayerComponentBase.generated.h"


class APBPlayerController;
class APBPlayerPawn;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTB_API UPBPlayerComponentBase : public UActorComponent
{
	GENERATED_BODY()

public:
	UPBPlayerComponentBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void InitPlayerController();
	
protected:
	virtual void InitializeComponent() override;
	
	virtual void SetupPlayerInput(UInputComponent* PlayerInputComponent);

	UPROPERTY()
	APBPlayerPawn* PlayerPawn;

	UPROPERTY()
	APBPlayerController* PlayerController;
	
	bool bPauseFunction;

	// Basic interaction, camera motion stop function. Delegate from controller
	UFUNCTION()
	void ChangePauseFunctionFromController(bool bIsUIOpen);
	
};
