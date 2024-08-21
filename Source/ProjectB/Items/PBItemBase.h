// Copyright © 2024, ProjectB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectB/Core/Interface/Interactable.h"
#include "PBItemBase.generated.h"

UCLASS()
class PROJECTB_API APBItemBase : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	APBItemBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void Interact(APlayerController* Controller) override;

	virtual void SetOutline(bool bOutlineEnabled) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Component", meta=(AllowPrivateAccess))
	UStaticMeshComponent* MeshComponent;

	// ---------- Inspection system ----------
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="InspectInfo", meta=(AllowPrivateAccess))
	UStaticMesh* ItemMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="InspectInfo", meta=(AllowPrivateAccess))
	FText ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="InspectInfo", meta=(AllowPrivateAccess))
	FString ItemDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="InspectInfo", meta=(AllowPrivateAccess))
	FVector ItemScale;
	// ------------------------------
	
};
