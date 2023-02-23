// Copyright PupSik, 2023. All Rights Reserved.

using UnrealBuildTool;

public class Fractals3D : ModuleRules
{
	public Fractals3D(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
        new string[]
        {
                    "Core",
            // ... add other public dependencies that you statically link with here ...
        }
        );

#if UE_5_0_OR_LATER
        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Projects",
                "RenderCore",
                "ToolWidgets",
                "Slate",
                "Json",
                "JsonUtilities",
                "SlateCore",
                "InputCore",
                "EditorFramework",
                "EditorStyle",
                "UnrealEd",
                "LevelEditor",
                "InteractiveToolsFramework",
                "EditorInteractiveToolsFramework",
			}
            );

#elif UE_4_17_OR_LATER
        PrivateDependencyModuleNames.AddRange(
			new string[]
			{
                "CoreUObject",
                "Engine",
                "Projects",
                "RenderCore",
                "Slate",
                "Json",
                "JsonUtilities",
                "SlateCore",
                "InputCore",
                "EditorStyle",
                "UnrealEd",
                "LevelEditor",
                "UnrealEd",
                "InteractiveToolsFramework"
            }
			);
#endif
    }
}
