// Copyright PupSik, 2023. All Rights Reserved.

#include "Fractals3DModule.h"
#include "Interfaces/IPluginManager.h"
#include "Fractals3DEditorModeCommands.h"
#include "IPropertyChangeListener.h"
#include "LevelEditor.h"

#define LOCTEXT_NAMESPACE "Fractals3DModule"

void FFractals3DModule::StartupModule()
{
	FString PluginShaderDir = FPaths::Combine(IPluginManager::Get().FindPlugin(TEXT("Fractals3D"))->GetBaseDir(), TEXT("Shaders"));
	AddShaderSourceDirectoryMapping(TEXT("/PluginShaders"), PluginShaderDir);

	FFractals3DEditorModeCommands::Register();

}

void FFractals3DModule::ShutdownModule()
{
	FFractals3DEditorModeCommands::Unregister();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FFractals3DModule, Fractals3DEditorMode)