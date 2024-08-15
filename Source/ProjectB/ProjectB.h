// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogCategory, Log, All);

#define PBLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define PBLOG_S(Verbosity) UE_LOG(UE5Practice, Verbosity, TEXT("%s"), *ABLOG_CALLINFO)
#define PBLOG(Verbosity, Format, ...) UE_LOG(UE5Practice, Verbosity, TEXT("%s %s"), *ABLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))