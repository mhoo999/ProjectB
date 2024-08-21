// Copyright © 2024, ProjectB. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PBPlayerController.generated.h"

class APBHUD;
class UPBInspectWidget;
class APBInspectItem;
class UInputMappingContext;
class APBItemBase;
class APBPlayerPawn;
class UCameraComponent;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPauseDefaultFunctionDelegate, bool, bIsUIOpen);

UCLASS()
class PROJECTB_API APBPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	APBPlayerController();

	// Basic interaction, camera motion stop function. Delegate from controller
	FPauseDefaultFunctionDelegate UPauseDefaultFunctionDelegate;
	
	void PauseBasicFunction();
	void ResumeBasicFunction();
	
private:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY()
	APBPlayerPawn* PlayerPawn;

	UPROPERTY()
	APBHUD* PlayerHUD;
	
	bool bIsUIOpen;

	// ---------- IMC ----------
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="IMC", meta=(AllowPrivateAccess))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="IMC", meta=(AllowPrivateAccess))
	UInputMappingContext* ItemInspectionContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="IMC", meta=(AllowPrivateAccess))
	UInputMappingContext* CommunicationContext;
	// ------------------------------

	// ---------- Inspection system ----------
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="InspectionSystem", meta=(AllowPrivateAccess))
	TSubclassOf<APBInspectItem> InspectItemFactory;

	UPROPERTY()
	APBInspectItem* SpawnInspectItem;

public:
	void ItemInspection(UStaticMesh* StaticMesh, FText ItemName, FString ItemDescription, FVector ItemScale);
	
	void ExitInspectWidget();
	
	void VisibilityToggleDialogueInspectWidget() const;
	// ------------------------------

	// ---------- Communication ----------
public:
	void Communication(UMaterialInterface* CharacterTexture, FName CharacterName, FString Dialogue);

	void ExitCommunicationWidget();
	// ------------------------------
};
