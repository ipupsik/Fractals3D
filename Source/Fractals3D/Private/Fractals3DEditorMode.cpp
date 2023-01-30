// Copyright Epic Games, Inc. All Rights Reserved.

#include "Fractals3DEditorMode.h"
#include "Fractals3DEditorModeToolkit.h"
#include "EdModeInteractiveToolsContext.h"
#include "InteractiveToolManager.h"
#include "Fractals3DEditorModeCommands.h"


//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////// 
// AddYourTool Step 1 - include the header file for your Tools here
//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////// 
#include "Tools/Fractals3DInteractiveTool.h"

// step 2: register a ToolBuilder in FFractals3DEditorMode::Enter() below


#define LOCTEXT_NAMESPACE "Fractals3DEditorMode"

const FEditorModeID UFractals3DEditorMode::EM_Fractals3DEditorModeId = TEXT("EM_Fractals3DEditorMode");

FString UFractals3DEditorMode::InteractiveToolName = TEXT("Fractals3D_GenerateFractalTool");


UFractals3DEditorMode::UFractals3DEditorMode()
{
	FModuleManager::Get().LoadModule("EditorStyle");

	// appearance and icon in the editing mode ribbon can be customized here
	Info = FEditorModeInfo(UFractals3DEditorMode::EM_Fractals3DEditorModeId,
		LOCTEXT("ModeName", "Fractals3D"),
		FSlateIcon(),
		true);
}


UFractals3DEditorMode::~UFractals3DEditorMode()
{
}


void UFractals3DEditorMode::ActorSelectionChangeNotify()
{
}

void UFractals3DEditorMode::Enter()
{
	UEdMode::Enter();

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	// AddYourTool Step 2 - register the ToolBuilders for your Tools here.
	// The string name you pass to the ToolManager is used to select/activate your ToolBuilder later.
	//////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////// 
	const FFractals3DEditorModeCommands& SampleToolCommands = FFractals3DEditorModeCommands::Get();

	RegisterTool(SampleToolCommands.InteractiveTool, InteractiveToolName, NewObject<UFractals3DInteractiveToolBuilder>(this));

	// active tool type is not relevant here, we just set to default
	GetToolManager()->SelectActiveToolType(EToolSide::Left, InteractiveToolName);
}

void UFractals3DEditorMode::CreateToolkit()
{
	Toolkit = MakeShareable(new FFractals3DEditorModeToolkit);
}

TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> UFractals3DEditorMode::GetModeCommands() const
{
	return FFractals3DEditorModeCommands::Get().GetCommands();
}

#undef LOCTEXT_NAMESPACE
