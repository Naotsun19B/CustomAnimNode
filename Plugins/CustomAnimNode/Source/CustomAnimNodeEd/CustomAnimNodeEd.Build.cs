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
                "CustomAnimNode",
                "Core",
                "CoreUObject",
                "Engine",
                "BlueprintGraph",
                "AnimGraph",
			}
			);
			
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"UnrealEd",
                "GraphEditor",
                "PropertyEditor",
                "EditorStyle",
			}
			);
	}
}
