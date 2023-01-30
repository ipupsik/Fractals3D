// Copyright Epic Games, Inc. All Rights Reserved.

#include "Fractals3DInteractiveTool.h"
#include "InteractiveToolManager.h"
#include "Interfaces/IPluginManager.h"
#include "Fractals3DEditorModeCommands.h"
#include "ToolBuilderUtil.h"
#include "Serialization/JsonSerializer.h"
#include "JsonObjectConverter.h"
#include "Misc/FileHelper.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include "BaseBehaviors/ClickDragBehavior.h"
#include "SourceControlHelpers.h"

#include "SceneManagement.h"

// localization namespace
#define LOCTEXT_NAMESPACE "UFractals3DInteractiveTool"

/*
 * ToolBuilder
 */

UInteractiveTool* UFractals3DInteractiveToolBuilder::BuildTool(const FToolBuilderState & SceneState) const
{
	UFractals3DInteractiveTool* NewTool = NewObject<UFractals3DInteractiveTool>(SceneState.ToolManager);
	return NewTool;
}


UFractals3DInteractiveToolProperties::UFractals3DInteractiveToolProperties()
{
	// initialize the points and distance to reasonable values
	FractalName = "Default";
	LastSDF = FractalConfigSDF::Mandelbrot;
}


void UFractals3DInteractiveTool::Setup()
{
	UInteractiveTool::Setup();

	const_cast<FFractals3DEditorModeCommands&>(FFractals3DEditorModeCommands::Get()).SetFractalTool(this);

	// Create the property set and register it with the Tool
	Properties = NewObject<UFractals3DInteractiveToolProperties>(this, "Measurement");
	AddToolPropertySource(Properties);

	Properties->WatchProperty(Properties->FractalName,
		[this](FString FractalName) {
			FString PluginShaderDir = FPaths::Combine(IPluginManager::Get().FindPlugin(TEXT("Fractals3D"))->GetBaseDir(), TEXT("Shaders"));
			FString GeneratedShadersDir = FPaths::Combine(PluginShaderDir, TEXT("GeneratedSDF"));
			FString CurrentShaderDir = FPaths::Combine(GeneratedShadersDir, Properties->FractalName);

			if (std::filesystem::exists(std::filesystem::path(TCHAR_TO_ANSI(*CurrentShaderDir)))) {
				FString FileData = "";
				FJsonFractalProperties FractalJSON;
				FFileHelper::LoadFileToString(FileData, *FPaths::Combine(CurrentShaderDir, "Conf.json"));

				if (FJsonObjectConverter::JsonObjectStringToUStruct(FileData, &FractalJSON, 0, 0))
				{
					Properties->FractalConfig = FractalJSON.FractalConfig;
					Properties->LastSDF = FractalJSON.LastSDF;
				}
			}
		}
	);

	
}

void UFractals3DInteractiveTool::OnPropertyModified(UObject* PropertySet, FProperty* Property)
{

}

FString FunctionNameByFoldType(FractalFoldConfig Type)
{
	switch (Type)
	{
		case FractalFoldConfig::PlaneFold: return "planeFold";
		case FractalFoldConfig::AbsFold: return "absFold";
		case FractalFoldConfig::SierpinskiFold: return "sierpinskiFold";
		case FractalFoldConfig::MengerFold: return "mengerFold";
		case FractalFoldConfig::SphereFold: return "sphereFold";
		case FractalFoldConfig::BoxFold: return "boxFold";
		case FractalFoldConfig::RotXFold: return "rotXFold";
		case FractalFoldConfig::RotYFold: return "rotYFold";
		case FractalFoldConfig::RotZFold: return "rotZFold";
		case FractalFoldConfig::ScaleTranslateFold: return "scaleTranslateFold";
		case FractalFoldConfig::ScaleOriginFold: return "scaleOriginFold";
		case FractalFoldConfig::OrbitColoring: return "orbitByType";
	}

	return "Error";
}

FString FunctionArgumentsByFoldType(FractalFoldConfig Type)
{
	switch (Type)
	{
		case FractalFoldConfig::PlaneFold: return "(new_p, float3(0, 0, -1), -1)";
		case FractalFoldConfig::AbsFold: return "(new_p, float3(0.0f, 0.0f, 0.0f))";
		case FractalFoldConfig::SierpinskiFold: return "(new_p)";
		case FractalFoldConfig::MengerFold: return "(new_p)";
		case FractalFoldConfig::SphereFold: return "(new_p, 0.5, 1.0f)";
		case FractalFoldConfig::BoxFold: return "(new_p, library.FoldSize)";
		case FractalFoldConfig::RotXFold: return "(new_p, library.FoldAngles.x)";
		case FractalFoldConfig::RotYFold: return "(new_p, library.FoldAngles.y)";
		case FractalFoldConfig::RotZFold: return "(new_p, library.FoldAngles.z)";
		case FractalFoldConfig::ScaleTranslateFold: return "(new_p, library.FoldingScale, library.Power * library.FoldOffset)";
		case FractalFoldConfig::ScaleOriginFold: return "(new_p, library.FoldingScale)";
		case FractalFoldConfig::OrbitColoring: return "(orbit, new_p)";
	}
	return "Error";
}

FString FunctionNameBySDFType(FractalConfigSDF Type)
{
	switch (Type)
	{
	case FractalConfigSDF::Cone: return "sdCone";
	case FractalConfigSDF::HexPrism: return "sdHexPrism";
	case FractalConfigSDF::Sphere: return "sdSphere";
	case FractalConfigSDF::Capsule: return "sdCapsule";
	case FractalConfigSDF::Torus: return "sdTorus";
	case FractalConfigSDF::Box: return "sdBox";
	case FractalConfigSDF::Tetrahedron: return "sdTetrahedron";
	case FractalConfigSDF::InfCross: return "sdInfCross";
	case FractalConfigSDF::InfCrossXY: return "sdInfCrossXY";
	case FractalConfigSDF::InfLine: return "sdInfLine";
	case FractalConfigSDF::Julia2: return "sdJulia2";
	case FractalConfigSDF::Julia: return "sdJulia";
	case FractalConfigSDF::Mandelbrot: return "sdMondelbrot";
	}
	return "Error";
}

FString FunctionArgumentsBySDFType(FractalConfigSDF Type)
{
	switch (Type)
	{
	case FractalConfigSDF::Cone: return "(new_p, float2(0.0f, 0.0f), library.Offset)";
	case FractalConfigSDF::HexPrism: return "(new_p, float2(library.Offset, library.Offset))";
	case FractalConfigSDF::Sphere: return "(new_p, library.Offset)";
	case FractalConfigSDF::Capsule: return "(new_p, library.FoldingScale, library.Offset)";
	case FractalConfigSDF::Torus: return "(new_p, float2(library.Offset, library.Offset))";
	case FractalConfigSDF::Box: return "(new_p, float3(library.Offset, library.Offset, library.Offset))";
	case FractalConfigSDF::Tetrahedron: return "(new_p, library.Offset)";
	case FractalConfigSDF::InfCross: return "(new_p, library.Offset)";
	case FractalConfigSDF::InfCrossXY: return "(new_p, library.Offset)";
	case FractalConfigSDF::InfLine: return "(new_p, library.Offset)";
	case FractalConfigSDF::Julia2: return "(new_p, outputColor).x";
	case FractalConfigSDF::Julia: return "(new_p, outputColor).x";
	case FractalConfigSDF::Mandelbrot: return "(new_p, outputColor).x";
	}
	return "Error";
}



bool IsOrbit(FractalFoldConfig Type)
{
	return Type == FractalFoldConfig::OrbitColoring;
}

void UFractals3DInteractiveTool::GenerateFractal() const {
	FString PluginShaderDir = FPaths::Combine(IPluginManager::Get().FindPlugin(TEXT("Fractals3D"))->GetBaseDir(), TEXT("Shaders"));
	FString GeneratedShadersDir = FPaths::Combine(PluginShaderDir, TEXT("GeneratedSDF"));
	FString CurrentShaderDir = FPaths::Combine(GeneratedShadersDir, Properties->FractalName);

	std::filesystem::remove_all(std::filesystem::path(TCHAR_TO_ANSI(*CurrentShaderDir)));
	std::filesystem::create_directory(std::filesystem::path(TCHAR_TO_ANSI(*CurrentShaderDir)));

	// Fill MainShader
	FString MainShaderFilename = Properties->FractalName;
	MainShaderFilename += ".ush";
	FString MainShader = "#include \"/PluginShaders/SDFractalLibrary.ush\"\n"
		"\n"
		"struct SDF {\n"
		"SDFractal library;\n"
		"float3 outputColor;\n"
		"\n"
		"#include \"/PluginShaders/GeneratedSDF/";
	MainShader += Properties->FractalName;
	MainShader += "/";
	MainShader += Properties->FractalName;
	MainShader += "SDF.ush\"\n"
		"};\n"
		"\n"
		"#include \"/PluginShaders/RayMarchingFractal.ush\"\n"
		;

	// Fill SDF Shader
	FString SdfShaderFilename = Properties->FractalName;
	SdfShaderFilename += "SDF.ush";
	FString SdfShader = "float2 sdf(float3 p) {\n"
		"	outputColor = library.orbitInitInf();\n"
		"	float4 new_p = float4(p, 1.0f);\n"
		"	float d = 1e20;\n"
		"	for (int i = 0; i < library.Iterations; i++) {\n"
		"";

	for (int i = 0; i < Properties->FractalConfig.Num(); ++i)
	{
		if (IsOrbit(Properties->FractalConfig[i]))
			SdfShader += "		outputColor = library.orbitByType(outputColor, new_p);\n";
		else
		{
			SdfShader += "		new_p = library.";
			SdfShader += FunctionNameByFoldType(Properties->FractalConfig[i]);
			SdfShader += FunctionArgumentsByFoldType(Properties->FractalConfig[i]);
			SdfShader += ";\n";
		}
	}

	SdfShader += "\n"
		"	}\n";

	SdfShader += "\n	d = min(d, library.";
	SdfShader += FunctionNameBySDFType(Properties->LastSDF);
	SdfShader += FunctionArgumentsBySDFType(Properties->LastSDF);
	SdfShader += ");\n";

	SdfShader += "	return float2(d, length(new_p));\n"
		"}\n";

	std::ofstream foutMainShader(*FPaths::Combine(CurrentShaderDir, MainShaderFilename));
	foutMainShader << std::string(TCHAR_TO_ANSI(* MainShader));
	std::ofstream foutSdfShader(*FPaths::Combine(CurrentShaderDir, SdfShaderFilename));
	foutSdfShader << std::string(TCHAR_TO_ANSI(* SdfShader));

	FString Buffer;
	FJsonFractalProperties Fractal;
	Fractal.FractalConfig = Properties->FractalConfig;
	Fractal.LastSDF = Properties->LastSDF;

	FJsonObjectConverter::UStructToJsonObjectString(Fractal, Buffer);

	std::ofstream foutShaderJson(*FPaths::Combine(CurrentShaderDir, "Conf.json"));
	foutShaderJson << std::string(TCHAR_TO_ANSI(*Buffer));

}


#undef LOCTEXT_NAMESPACE
