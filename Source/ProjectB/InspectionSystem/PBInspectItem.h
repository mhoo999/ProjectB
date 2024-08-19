// Copyright © 2024, ProjectB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PBInspectItem.generated.h"

UCLASS()
class PROJECTB_API APBInspectItem : public AActor
{
	GENERATED_BODY()

public:
	APBInspectItem();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Component", meta=(AllowPrivateAccess))
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Component", meta=(AllowPrivateAccess))
	USceneCaptureComponent2D* SceneCaptureComponent;

public:
	UStaticMeshComponent* GetStaticMeshComponent();
};
