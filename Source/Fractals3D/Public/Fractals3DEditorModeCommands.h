// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"

class UFractals3DInteractiveTool;

/**
 * This class contains info about the full set of commands used in this editor mode.
 */
class FFractals3DEditorModeCommands : public TCommands<FFractals3DEditorModeCommands>
{
public:
	FFractals3DEditorModeCommands();

	virtual void RegisterCommands() override;
	static TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> GetCommands();

	TSharedPtr<FUICommandInfo> InteractiveTool;

	void SetFractalTool(UFractals3DInteractiveTool* Tool);

	void UseFractalTool() const;

protected:
	UFractals3DInteractiveTool* FractalTool;

	TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> Commands;
};
