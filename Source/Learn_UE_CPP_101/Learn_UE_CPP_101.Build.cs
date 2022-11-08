// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Learn_UE_CPP_101 : ModuleRules
{
	public Learn_UE_CPP_101(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay","UMG" });

		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		PublicDependencyModuleNames.AddRange(new string[] { "UnrealEd" });

	}
}
