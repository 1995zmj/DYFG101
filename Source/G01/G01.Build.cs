// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class G01 : ModuleRules
{
	public G01(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
            new string[] {
                "G01"
            }
        );

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "EnhancedInput",
            "AIModule",
            "NavigationSystem",
            "StateTreeModule",
            "GameplayStateTreeModule",
            "Niagara",
            "UMG",
            "Slate",
            "ModularGameplay",
            "ModularGameplayActors",
            "DataRegistry",
            "GameFeatures",
            "GameplayTags",
            "GameplayTasks",
            "GameplayAbilities",
        });

        PrivateDependencyModuleNames.AddRange(new string[]
        {
            "NetCore",
            "CommonUI",
	        "CommonGame",
            "CommonUser",
            "UIExtension",
            "DeveloperSettings",
        });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
