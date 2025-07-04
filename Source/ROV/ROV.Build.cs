// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ROV : ModuleRules
{
	public ROV(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "NavigationSystem", 
                "AIModule", "Niagara", "EnhancedInput", "HTTP", "Json", "JsonUtilities", "Slate", "SlateCore", });
        PrivateDependencyModuleNames.AddRange(new string[] { "VgCore", "RovData", "VgFlMngmnt" });
    }
}
