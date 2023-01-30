// Copyright Epic Games, Inc. All Rights Reserved.

#include "Fractals3DEditorModeToolkit.h"
#include "Fractals3DEditorMode.h"
#include "Tools/Fractals3DInteractiveTool.h"
#include "Fractals3DEditorModeCommands.h"
#include "EdModeInteractiveToolsContext.h"
#include "Engine/Selection.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Fractals3DEditorModeCommands.h"
#include "SPrimaryButton.h"

#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"
#include "IDetailsView.h"
#include "EditorModeManager.h"

#define LOCTEXT_NAMESPACE "Fractals3DEditorModeToolkit"

FFractals3DEditorModeToolkit::FFractals3DEditorModeToolkit()
{
}

void FFractals3DEditorModeToolkit::Init(const TSharedPtr<IToolkitHost>& InitToolkitHost, TWeakObjectPtr<UEdMode> InOwningMode)
{
	FModeToolkit::Init(InitToolkitHost, InOwningMode);


	SAssignNew(ViewportOverlayWidget, SHorizontalBox)

		+ SHorizontalBox::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Bottom)
		.Padding(FMargin(0.0f, 0.0f, 0.f, 15.f))
		[
			SNew(SBorder)
			.BorderImage(FAppStyle::Get().GetBrush("EditorViewport.OverlayBrush"))
		.Padding(8.f)
		[
			SNew(SHorizontalBox)

		+ SHorizontalBox::Slot()
		.AutoWidth()
		.Padding(FMargin(0.0, 0.f, 2.f, 0.f))
		[
			SNew(SPrimaryButton)
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
	GetToolkitHost()->AddViewportOverlayWidget(ViewportOverlayWidget.ToSharedRef());
}

void FFractals3DEditorModeToolkit::OnToolEnded(UInteractiveToolManager* Manager, UInteractiveTool* Tool)
{
	FModeToolkit::OnToolEnded(Manager, Tool);

	if (IsHosted())
	{
		GetToolkitHost()->RemoveViewportOverlayWidget(ViewportOverlayWidget.ToSharedRef());
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
