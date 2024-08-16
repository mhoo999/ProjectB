// Copyright © 2024, ProjectB. All rights reserved.

#pragma once

#include "CoreMinimal.h"

#include "Interactable.generated.h"

UINTERFACE()
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTB_API IInteractable
{
	GENERATED_BODY()

public:
	virtual void Interact() = 0;

	virtual void SetOutline(bool bOutlineEnabled) = 0;
};
