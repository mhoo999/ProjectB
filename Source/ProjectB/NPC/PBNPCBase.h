// Copyright © 2024, ProjectB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectB/Core/Interface/Interactable.h"
#include "PBNPCBase.generated.h"

class UWidgetComponent;

UCLASS()
class PROJECTB_API APBNPCBase : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	APBNPCBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Component", meta=(AllowPrivateAccess))
	UWidgetComponent* WidgetComponent;

protected:
	virtual void Interact(APlayerController* Controller) override;

	virtual void SetOutline(bool bOutlineEnabled) override;

	// ---------- Communication system ----------
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CharaterInfo", meta=(AllowPrivateAccess))
	UMaterialInterface* CharacterTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CharaterInfo", meta=(AllowPrivateAccess))
	FName CharacterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CharacterInfo", meta=(AllowPrivateAccess))
	FString Dialogue;
	// ------------------------------

	// ---------- Rotate With Player ----------
private:
	bool bIsPlaceOnRight;
	
	FRotator PreviousPlayerCameraRotation;

	// A function that determines a position on the screen based on the player
	void CheckActorPosition();

	// Function to move the actor along the player camera
	void FaceToPlayerCamera();
	// ------------------------------

	
};
