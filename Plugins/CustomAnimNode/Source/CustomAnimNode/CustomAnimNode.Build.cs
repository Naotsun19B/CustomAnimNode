// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CustomAnimNode : ModuleRules
{
	public CustomAnimNode(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
                "CoreUObject",
                "Engine",
                "AnimGraph",
                "AnimGraphRuntime",
                "BlueprintGraph",
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
                "AnimGraph",
                "AnimGraphRuntime",
                "BlueprintGraph",
            }
			);
	}
}
