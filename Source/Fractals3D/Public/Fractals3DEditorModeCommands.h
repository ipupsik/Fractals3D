// Copyright PupSik, 2023. All Rights Reserved.

#pragma once

#if ENGINE_MAJOR_VERSION == 5

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"

class UFractals3DInteractiveTool5;

class FFractals3DEditorModeCommands : public TCommands<FFractals3DEditorModeCommands>
{
public:
	FFractals3DEditorModeCommands();

	virtual void RegisterCommands() override;
	static TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> GetCommands();

	TSharedPtr<FUICommandInfo> InteractiveTool;

	void SetFractalTool(UFractals3DInteractiveTool5* Tool);

	void UseFractalTool() const;

protected:
	UFractals3DInteractiveTool5* FractalTool;

	TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> Commands;
};

#endif