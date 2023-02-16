// Copyright PupSik, 2023. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveToolBuilder.h"
#if ENGINE_MAJOR_VERSION == 5
#include "BaseTools/ClickDragTool.h"
#elif ENGINE_MAJOR_VERSION == 4
#include "BaseEditorToolCustomization.h"
#endif
#include "Fractals3DInteractiveTool.generated.h"

UCLASS()
class FRACTALS3D_API UFractals3DInteractiveToolBuilder : public UInteractiveToolBuilder
{
	GENERATED_BODY()

public:
	virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override { return true; }
	virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;
};

UENUM()
enum class FractalFoldConfig {
	PlaneFold,
	AbsFold,
	SierpinskiFold,
	MengerFold,
	SphereFold,
	BoxFold,
	RotXFold,
	RotYFold,
	RotZFold,
	ScaleTranslateFold,
	ScaleOriginFold,
	OrbitColoring,
};

UENUM()
enum class FractalConfigSDF {
	Cone,
	HexPrism,
	Sphere,
	Capsule,
	Torus,
	Box,
	Tetrahedron,
	InfCross,
	InfCrossXY,
	InfLine,
	Mandelbrot,
	Julia,
	Julia2,
};

USTRUCT()
struct FJsonFractalProperties
{
	GENERATED_BODY()

public:
	UPROPERTY()
		TArray<FractalFoldConfig> FractalConfig;

	UPROPERTY()
		FractalConfigSDF LastSDF;
};

UCLASS(Transient)
class FRACTALS3D_API UFractals3DInteractiveToolProperties : public UInteractiveToolPropertySet
{
	GENERATED_BODY()
public:
UFractals3DInteractiveToolProperties();
UPROPERTY(EditAnywhere, Category = Options)
	FString FractalName;
UPROPERTY(EditAnywhere, Category = Options)
	TArray<FractalFoldConfig> FractalConfig;
UPROPERTY(EditAnywhere, Category = Options)
	FractalConfigSDF LastSDF;
};

UCLASS(Blueprintable)
class UFractals3DInteractiveTool4 : public UInteractiveTool
{
	GENERATED_BODY()
public:
	/** UInteractiveTool overrides */
	UFUNCTION(Exec)
		void GenerateFractal();

	void TypedFractalName();
private:

	UPROPERTY(EditAnywhere, Category = Settings)
		FString FractalName;

	UPROPERTY(EditAnywhere, Category = Settings)
		TArray<FractalFoldConfig> FractalConfig;

	UPROPERTY(EditAnywhere, Category = Settings)
		FractalConfigSDF LastSDF;
};

UCLASS()
class FRACTALS3D_API UFractals3DInteractiveTool5 : public UInteractiveTool

{
	GENERATED_BODY()
public:
#if ENGINE_MAJOR_VERSION == 5
	virtual void Setup() override;

	void GenerateFractal();

	void TypedFractalName();
#endif

private:
	UPROPERTY()
		UFractals3DInteractiveToolProperties* Properties;
};
