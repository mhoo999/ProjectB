// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogCategory, Log, All);

#define PBLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define PBLOG_S(Verbosity) UE_LOG(LogCategory, Verbosity, TEXT("%s"), *PBLOG_CALLINFO)
#define PBLOG(Verbosity, Format, ...) UE_LOG(LogCategory, Verbosity, TEXT("%s %s"), *PBLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))