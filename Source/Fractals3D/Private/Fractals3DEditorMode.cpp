// Copyright PupSik, 2023. All Rights Reserved.

#include "Fractals3DEditorMode.h"
#include "Fractals3DEditorModeToolkit.h"
#include "EdModeInteractiveToolsContext.h"
#include "InteractiveToolManager.h"
#include "Fractals3DEditorModeCommands.h"

#include "Tools/Fractals3DInteractiveTool.h"

#define LOCTEXT_NAMESPACE "Fractals3DEditorMode"

const FEditorModeID UFractals3DEditorMode::EM_Fractals3DEditorModeId = TEXT("EM_Fractals3DEditorMode");

FString UFractals3DEditorMode::InteractiveToolName = TEXT("Fractals3D_GenerateFractalTool");


UFractals3DEditorMode::UFractals3DEditorMode()
{
#if ENGINE_MAJOR_VERSION == 5
	FModuleManager::Get().LoadModule("EditorStyle");

	// appearance and icon in the editing mode ribbon can be customized here
	Info = FEditorModeInfo(UFractals3DEditorMode::EM_Fractals3DEditorModeId,
		LOCTEXT("ModeName", "Fractals3D"),
		FSlateIcon(),
		true);
#endif
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
#if ENGINE_MAJOR_VERSION == 5
	const FFractals3DEditorModeCommands& SampleToolCommands = FFractals3DEditorModeCommands::Get();

	RegisterTool(SampleToolCommands.InteractiveTool, InteractiveToolName, NewObject<UFractals3DInteractiveToolBuilder>(this));

	// active tool type is not relevant here, we just set to default
	GetToolManager()->SelectActiveToolType(EToolSide::Left, InteractiveToolName);
#endif
}

void UFractals3DEditorMode::CreateToolkit()
{
#if ENGINE_MAJOR_VERSION == 5
	Toolkit = MakeShareable(new FFractals3DEditorModeToolkit);
#endif
}

TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> UFractals3DEditorMode::GetModeCommands() const
{
	return FFractals3DEditorModeCommands::Get().GetCommands();
}

#undef LOCTEXT_NAMESPACE