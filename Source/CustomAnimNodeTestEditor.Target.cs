// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class CustomAnimNodeTestEditorTarget : TargetRules
{
	public CustomAnimNodeTestEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		ExtraModuleNames.Add("CustomAnimNodeTest");
	}
}
