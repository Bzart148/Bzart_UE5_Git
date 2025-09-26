// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Homework7 : ModuleRules
{
	public Homework7(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
