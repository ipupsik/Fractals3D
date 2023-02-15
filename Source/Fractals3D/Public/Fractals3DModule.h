// Copyright PupSik, 2023. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Tools/Fractals3DInteractiveTool.h"
#include "Modules/ModuleInterface.h"

class FFractals3DModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	static void TriggerTool(UClass* ToolClass);
	static void CreateToolListMenu(class FMenuBuilder& MenuBuilder);
	static void OnToolWindowClosed(const TSharedRef<SWindow>& Window, UFractals3DInteractiveTool* Instance);

	TSharedPtr<FUICommandList> CommandList;
};
