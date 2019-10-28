// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Gonet : ModuleRules
{
	public Gonet(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core",  "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay"});
        bEnableShadowVariableWarnings = false;
        bEnableUndefinedIdentifierWarnings = false;
        bEnableExceptions = true;

        Definitions.Add("_CRT_SECURE_NO_WARNINGS");
    }
}
