// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShaderField.h"
#include <Misc/Paths.h>

//The definition of the custom LOG category
DEFINE_LOG_CATEGORY(LogShaderField);

#define LOCTEXT_NAMESPACE "FShaderFieldModule"



void FShaderFieldModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	//! The FPaths library grants us access to various core directories in UE.
	FString PluginsDir = FPaths::ProjectPluginsDir();
	//! It also contains useful functions, such as the 'Combine()' method, used for combining directories:
	FString ShaderDir = FPaths::Combine(PluginsDir, TEXT("ShaderField/Shaders"));

	//! This function (from ShaderCore.h) is taking a virtual directory for where shaders would be, and an actual directory of the shader:
	AddShaderSourceDirectoryMapping("/Plugin/ShaderField", ShaderDir);

	//! The same applied to a project directory, rather than a plugin:
	FString ProjectDir = FPaths::ProjectDir();
	FString ProjectShaderDir = FPaths::Combine(ProjectDir, TEXT("/MyShaders"));
	AddShaderSourceDirectoryMapping("/Project/MyShaders", ProjectShaderDir);

	//TODO ! Do Note, that `AddShaderSourceDirectoryMapping` is included in `ShaderCore.h` - however, including it would break the Plugin's compilation.
	//TODO ! Instead, It will need to be imported via the `RenderCore` Module as a private/public dependancy, in `PluginName.Build.cs`.

	
	//

	#ifdef MYPLUGIN_LOGGING_VERBOSE
		UE_LOG(LogShaderField, Verbose, TEXT("My Plugin has it's own LOG category! - Debug"));
	#endif

	#ifdef MYPLUGIN_LOGGING_MINIMAL
		UE_LOG(LogShaderField, Warning, TEXT("My Plugin has it's own LOG category! - Production"));
	#endif

	UE_LOG(LogShaderField, Log, TEXT("My Plugin has it's own LOG category! - log"));
	UE_LOG(LogShaderField, Warning, TEXT("My Plugin has it's own LOG category! - warning"));
	UE_LOG(LogShaderField, Verbose, TEXT("My Plugin has it's own LOG category! - Verbose"));
	UE_LOG(LogShaderField, VeryVerbose, TEXT("My Plugin has it's own LOG category! - VeryVerbose"));
}

void FShaderFieldModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FShaderFieldModule, ShaderField)