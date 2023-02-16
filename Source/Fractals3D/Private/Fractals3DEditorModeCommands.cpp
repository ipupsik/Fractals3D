// Copyright PupSik, 2023. All Rights Reserved.

#if ENGINE_MAJOR_VERSION == 5

#include "Fractals3DEditorModeCommands.h"
#include "Fractals3DEditorMode.h"
#include "Tools/Fractals3DInteractiveTool.h"
#include "EditorStyleSet.h"

#define LOCTEXT_NAMESPACE "Fractals3DEditorModeCommands"

FFractals3DEditorModeCommands::FFractals3DEditorModeCommands()
	: TCommands<FFractals3DEditorModeCommands>("Fractals3DEditorMode",
		NSLOCTEXT("Fractals3DEditorMode", "Fractals3DEditorModeCommands", "Fractals3D Editor Mode"),
		NAME_None,
		FAppStyle::GetAppStyleSetName())
{
}

void FFractals3DEditorModeCommands::RegisterCommands()
{
	TArray <TSharedPtr<FUICommandInfo>>& ToolCommands = Commands.FindOrAdd(NAME_Default);

	UI_COMMAND(InteractiveTool, "Generate 3D Fractal", "Generates new Material from various fractal settings", EUserInterfaceActionType::ToggleButton, FInputChord());
	ToolCommands.Add(InteractiveTool);
}

TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> FFractals3DEditorModeCommands::GetCommands()
{
	return FFractals3DEditorModeCommands::Get().Commands;
}

void FFractals3DEditorModeCommands::SetFractalTool(UFractals3DInteractiveTool* Tool)
{
	FractalTool = Tool;
}

void FFractals3DEditorModeCommands::UseFractalTool() const
{
	if (FractalTool)
		FractalTool->GenerateFractal();
}

#undef LOCTEXT_NAMESPACE

#endif