// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class work1 : ModuleRules
{
	public work1(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
