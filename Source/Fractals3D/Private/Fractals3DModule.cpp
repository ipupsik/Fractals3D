// Copyright PupSik, 2023. All Rights Reserved.

#include "Fractals3DModule.h"
#include "Interfaces/IPluginManager.h"
#include "IPropertyChangeListener.h"
#include "LevelEditor.h"
#include "BaseEditorToolCustomization.h"

#define LOCTEXT_NAMESPACE "Fractals3DModule"

void FFractals3DModule::StartupModule()
{
#if ENGINE_MAJOR_VERSION == 4
	// Register the details customization
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
		PropertyModule.RegisterCustomClassLayout("Fractals3DInteractiveTool", FOnGetDetailCustomizationInstance::CreateStatic(&FBaseEditorToolCustomization::MakeInstance));
		
		PropertyChangeListener = PropertyModule.CreatePropertyChangeListener();

		PropertyModule.NotifyCustomizationModuleChanged();
	}
#endif
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	FString PluginShaderDir = FPaths::Combine(IPluginManager::Get().FindPlugin(TEXT("Fractals3D"))->GetBaseDir(), TEXT("Shaders"));
	AddShaderSourceDirectoryMapping(TEXT("/PluginShaders"), PluginShaderDir);

#if ENGINE_MAJOR_VERSION == 4
	CommandList = MakeShareable(new FUICommandList);

	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

	struct Local
	{
		static void AddMenuCommands(FMenuBuilder& MenuBuilder)
		{
			MenuBuilder.AddSubMenu(LOCTEXT("Fractals3D", "Fractals3D"),
				LOCTEXT("Fractals3DTooltip", "List of tools"),
				FNewMenuDelegate::CreateStatic(&FFractals3DModule::CreateToolListMenu)
				);
		}
	};

	TSharedRef<FExtender> MenuExtender(new FExtender());
	MenuExtender->AddMenuExtension(
		"EditMain",
		EExtensionHook::After,
		CommandList.ToSharedRef(),
		FMenuExtensionDelegate::CreateStatic(&Local::AddMenuCommands));
	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
#endif
}

#if ENGINE_MAJOR_VERSION == 4

void FFractals3DModule::OnToolWindowClosed(const TSharedRef<SWindow>& Window, UFractals3DInteractiveTool4* Instance)
{
	Instance->RemoveFromRoot();
}

void FFractals3DModule::TriggerTool(UClass* ToolClass)
{
	UFractals3DInteractiveTool4* ToolInstance = NewObject<UFractals3DInteractiveTool4>(GetTransientPackage(), ToolClass);
	ToolInstance->AddToRoot();

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	TArray<UObject*> ObjectsToView;
	ObjectsToView.Add(ToolInstance);
	TSharedRef<SWindow> Window = PropertyModule.CreateFloatingDetailsView(ObjectsToView, false);

	Window->SetOnWindowClosed(FOnWindowClosed::CreateStatic(&FFractals3DModule::OnToolWindowClosed, ToolInstance));
}

void FFractals3DModule::CreateToolListMenu(class FMenuBuilder& MenuBuilder)
{
	for (TObjectIterator<UClass> ClassIt; ClassIt; ++ClassIt)
	{
		UClass* Class = *ClassIt;
		if (!Class->HasAnyClassFlags(CLASS_Deprecated | CLASS_NewerVersionExists | CLASS_Abstract))
		{
			if (Class->IsChildOf(UFractals3DInteractiveTool4::StaticClass()))
			{
				FString FriendlyName = Class->GetName();
				FText MenuDescription = FText::Format(LOCTEXT("ToolMenuiDescription", "{0}"), FText::FromString(FriendlyName));
				FText MenuTooltip = FText::Format(LOCTEXT("ToolMenuTooltip", "Execute the {0} tool"), FText::FromString(FriendlyName));

				FUIAction Action(FExecuteAction::CreateStatic(&FFractals3DModule::TriggerTool, Class));

				MenuBuilder.AddMenuEntry(
					MenuDescription,
					MenuTooltip,
					FSlateIcon(),
					Action
					);
			}
		}
	}
}
#endif

void FFractals3DModule::ShutdownModule()
{
	
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FFractals3DModule, Fractals3DEditorMode)