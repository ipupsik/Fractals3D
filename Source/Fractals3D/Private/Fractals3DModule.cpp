// Copyright Epic Games, Inc. All Rights Reserved.

#include "Fractals3DModule.h"
#include "Interfaces/IPluginManager.h"
#include "Fractals3DEditorModeCommands.h"

#define LOCTEXT_NAMESPACE "Fractals3DModule"

void FFractals3DModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	FString PluginShaderDir = FPaths::Combine(IPluginManager::Get().FindPlugin(TEXT("Fractals3D"))->GetBaseDir(), TEXT("Shaders"));
	AddShaderSourceDirectoryMapping(TEXT("/PluginShaders"), PluginShaderDir);

	FFractals3DEditorModeCommands::Register();
}

void FFractals3DModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	FFractals3DEditorModeCommands::Unregister();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FFractals3DModule, Fractals3DEditorMode)