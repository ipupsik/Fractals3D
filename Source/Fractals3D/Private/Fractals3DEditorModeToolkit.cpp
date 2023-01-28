// Copyright Epic Games, Inc. All Rights Reserved.

#include "Fractals3DEditorModeToolkit.h"
#include "Fractals3DEditorMode.h"
#include "Engine/Selection.h"

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
