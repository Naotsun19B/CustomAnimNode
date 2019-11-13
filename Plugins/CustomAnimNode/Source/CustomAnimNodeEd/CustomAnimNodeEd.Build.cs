// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CustomAnimNodeEd : ModuleRules
{
	public CustomAnimNodeEd(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
                "Core",
                "CoreUObject",
                "Engine",
                "CustomAnimNode",
            }
			);
			
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
                "AnimGraph",
                "BlueprintGraph",
                "Persona",
				"UnrealEd",
                "AnimGraphRuntime",
                "SlateCore",
			}
			);
	}
}
