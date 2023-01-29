// Copyright Epic Games, Inc. All Rights Reserved.

#include "Fractals3DEditorModeToolkit.h"
#include "Fractals3DEditorMode.h"
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

	float Padding = 4.0f;
	FMargin MorePadding = FMargin(10.0f, 2.0f);
	SAssignNew(ToolkitWidget, SBox)
		[
			SNew(SVerticalBox)

			+ SVerticalBox::Slot()
		[

			SNew(SSplitter)
			.Orientation(Orient_Vertical)
		+ SSplitter::Slot()
		.Value(1.f)
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot()
				.FillHeight(1.0)
				[
					SNew(SScrollBox)
					+ SScrollBox::Slot()
				[
					DetailsView.ToSharedRef()
				]
				]
			+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
				[
					SNew(SSpacer)
				]

			+ SHorizontalBox::Slot()
				.Padding(4.0)
				.AutoWidth()
				[
					SNew(SPrimaryButton)
					.OnClicked(this, &FFractals3DEditorModeToolkit::OnFractalGenerateClicked)
				.IsEnabled(this, &FFractals3DEditorModeToolkit::CanExecuteFractalGenerate)
				.Text_Lambda([this]() -> FText { return LOCTEXT("FractalGenerateButton", "Generate Fractal"); })
				]

			+ SHorizontalBox::Slot()
				.Padding(4.0)
				.AutoWidth()
				[
					SNew(SButton)
				.Text(FText(LOCTEXT("FractalGenerateButton", "Generate Fractal")))
				]
				]
				]
		]
		];
}

FReply FFractals3DEditorModeToolkit::OnFractalGenerateClicked()
{
	//FFractals3DEditorModeCommands::Get().InteractiveTool->(StaticCastSharedRef<FFractals3DEditorModeToolkit>(AsShared()));

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
