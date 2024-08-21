// Copyright © 2024, ProjectB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PBPlayerComponentBase.h"
#include "PBCameraComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTB_API UPBCameraComponent : public UPBPlayerComponentBase
{
	GENERATED_BODY()

public:
	UPBCameraComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// Get the maximum angle for each level when loading the level
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Settings", meta=(AllowPrivateAccess))
	float MaxYawAngle = 20.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Settings", meta=(AllowPrivateAccess))
	float MaxPitchAngle = 20.0f;
	
	FVector2D ViewportSize;
	float MouseX;
	float MouseY;
	
};
