// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

//! Custom LOG categories must be declared in the header file (and defined in the source file)
DECLARE_LOG_CATEGORY_EXTERN(LogShaderField, Log, All);

class FShaderFieldModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	//DECLARE_LOG_CATEGORY_EXTERN(LogShaderField, All, FLogCategoryBase::SetVerbosity(ELogVerbosity::All));
	
	//DECLARE_LOG_CATEGORY_EXTERN(LogMyGame, Log, All);
};
