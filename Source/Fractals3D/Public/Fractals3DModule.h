// Copyright PupSik, 2023. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Tools/Fractals3DInteractiveTool.h"
#include "Modules/ModuleInterface.h"

class IPropertyChangeListener;

class FFractals3DModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
