// Copyright PupSik, 2023. All Rights Reserved.

#pragma once

#if ENGINE_MAJOR_VERSION == 5

#include "CoreMinimal.h"
#include "Toolkits/BaseToolkit.h"
#include "Fractals3DEditorMode.h"

class FFractals3DEditorModeToolkit : public FModeToolkit
{
public:
	FFractals3DEditorModeToolkit();

	/** FModeToolkit interface */
	virtual void Init(const TSharedPtr<IToolkitHost>& InitToolkitHost, TWeakObjectPtr<UEdMode> InOwningMode) override;
	virtual void GetToolPaletteNames(TArray<FName>& PaletteNames) const override;

	// FModeToolkit
	virtual void OnToolStarted(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;
	virtual void OnToolEnded(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;

	// Modal Command Callback
	FReply OnFractalGenerateClicked();
	bool CanExecuteFractalGenerate() const;

	/** Contains the widget container for the Accept/Cancel buttons for tools. */
	TSharedPtr<SWidget> ViewportOverlayWidget;

	/** IToolkit interface */
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;


};

#endif