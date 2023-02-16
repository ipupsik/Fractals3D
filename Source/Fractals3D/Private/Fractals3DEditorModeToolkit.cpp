// Copyright PupSik, 2023. All Rights Reserved.

#include "Fractals3DEditorModeToolkit.h"
#include "Fractals3DEditorMode.h"
#include "Tools/Fractals3DInteractiveTool.h"
#include "Fractals3DEditorModeCommands.h"
#if ENGINE_MAJOR_VERSION == 5
#include "EdModeInteractiveToolsContext.h"
#endif
#include "Engine/Selection.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Fractals3DEditorModeCommands.h"
#if ENGINE_MAJOR_VERSION == 5
#include "SPrimaryButton.h"
#endif

#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"
#include "IDetailsView.h"
#include "EditorModeManager.h"

#define LOCTEXT_NAMESPACE "Fractals3DEditorModeToolkit"

FFractals3DEditorModeToolkit::FFractals3DEditorModeToolkit()
{
}

#if ENGINE_MAJOR_VERSION == 5
void FFractals3DEditorModeToolkit::Init(const TSharedPtr<IToolkitHost>& InitToolkitHost, TWeakObjectPtr<UEdMode> InOwningMode)
#elif ENGINE_MAJOR_VERSION == 4
void FFractals3DEditorModeToolkit::Init(const TSharedPtr<IToolkitHost>& InitToolkitHost)
#endif
{
#if ENGINE_MAJOR_VERSION == 5
	FModeToolkit::Init(InitToolkitHost, InOwningMode);
#elif ENGINE_MAJOR_VERSION == 4
	FModeToolkit::Init(InitToolkitHost);
#endif

	SAssignNew(ToolkitWidget, SHorizontalBox)

		+ SHorizontalBox::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Bottom)
		.Padding(FMargin(0.0f, 0.0f, 0.f, 15.f))
		[
			SNew(SBorder)
		#if ENGINE_MAJOR_VERSION == 5
			.BorderImage(FAppStyle::Get().GetBrush("EditorViewport.OverlayBrush"))
		#elif ENGINE_MAJOR_VERSION == 4
			.BorderImage(FEditorStyle::Get().GetBrush("EditorViewport.OverlayBrush"))
		#endif
			.Padding(8.f)
		[
			SNew(SHorizontalBox)

		+ SHorizontalBox::Slot()
		.AutoWidth()
		.Padding(FMargin(0.0, 0.f, 2.f, 0.f))
		[
		#if ENGINE_MAJOR_VERSION == 5
			SNew(SPrimaryButton)
		#elif ENGINE_MAJOR_VERSION == 4
			SNew(SButton)
		#endif
			.Text(LOCTEXT("OverlayGenerate", "Generate"))
		.ToolTipText(LOCTEXT("OverlayGenerateTooltip", "Generate 3d fractal by specified params"))
		.OnClicked(this, &FFractals3DEditorModeToolkit::OnFractalGenerateClicked)
		]
		]
		];
}

void FFractals3DEditorModeToolkit::OnToolStarted(UInteractiveToolManager* Manager, UInteractiveTool* Tool)
{
	FModeToolkit::OnToolStarted(Manager, Tool);

	// Add the accept/cancel overlay only if the tool is not the default tool.
#if ENGINE_MAJOR_VERSION == 5
	GetToolkitHost()->AddViewportOverlayWidget(ViewportOverlayWidget.ToSharedRef());
#endif
}

void FFractals3DEditorModeToolkit::OnToolEnded(UInteractiveToolManager* Manager, UInteractiveTool* Tool)
{
	FModeToolkit::OnToolEnded(Manager, Tool);

	if (IsHosted())
	{
	#if ENGINE_MAJOR_VERSION == 5
		GetToolkitHost()->RemoveViewportOverlayWidget(ViewportOverlayWidget.ToSharedRef());
	#endif
	}
}

FReply FFractals3DEditorModeToolkit::OnFractalGenerateClicked()
{
	FFractals3DEditorModeCommands::Get().UseFractalTool();

	return FReply::Handled();
}

bool FFractals3DEditorModeToolkit::CanExecuteFractalGenerate() const
{
	return true;
}

void FFractals3DEditorModeToolkit::GetToolPaletteNames(TArray<FName>& PaletteNames) const
{
	PaletteNames.Add(NAME_Default);
}


FName FFractals3DEditorModeToolkit::GetToolkitFName() const
{
	return FName("Fractals3DEditorMode");
}

FText FFractals3DEditorModeToolkit::GetBaseToolkitName() const
{
	return LOCTEXT("DisplayName", "Fractals3DEditorMode Toolkit");
}

#undef LOCTEXT_NAMESPACE