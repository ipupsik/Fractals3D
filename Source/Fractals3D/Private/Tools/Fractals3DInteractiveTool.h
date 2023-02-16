// Copyright PupSik, 2023. All Rights Reserved.

#pragma once

#if ENGINE_MAJOR_VERSION == 5
#include "CoreMinimal.h"
#include "InteractiveToolBuilder.h"
#include "BaseTools/ClickDragTool.h"
#elif ENGINE_MAJOR_VERSION == 4
#include "BaseEditorToolCustomization.h"
#endif
#include "Fractals3DInteractiveTool.generated.h"

#if ENGINE_MAJOR_VERSION == 5
UCLASS()
class FRACTALS3D_API UFractals3DInteractiveToolBuilder : public UInteractiveToolBuilder
{
	GENERATED_BODY()
public:
	virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override { return true; }
	virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;
};
#endif

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

#if ENGINE_MAJOR_VERSION == 5
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
#endif

#if ENGINE_MAJOR_VERSION == 5
/**
 * UFractals3DInteractiveTool is an example Tool that allows the user to measure the
 * distance between two points. The first point is set by click-dragging the mouse, and
 * the second point is set by shift-click-dragging the mouse.
 */
UCLASS()
class FRACTALS3D_API UFractals3DInteractiveTool : public UInteractiveTool
#elif ENGINE_MAJOR_VERSION == 4
UCLASS(Blueprintable)
class UFractals3DInteractiveTool : public UObject
#endif
{
	GENERATED_BODY()

public:
#if ENGINE_MAJOR_VERSION == 5
	virtual void Setup() override;
	virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;
#endif

private:
#if ENGINE_MAJOR_VERSION == 5
	/** Properties of the tool are stored here */
	UPROPERTY()
		TObjectPtr<UFractals3DInteractiveToolProperties> Properties;
#elif ENGINE_MAJOR_VERSION == 4
	UPROPERTY(EditAnywhere, Category = Settings)
		FString FractalName;

	UPROPERTY(EditAnywhere, Category = Settings)
		TArray<FractalFoldConfig> FractalConfig;

	UPROPERTY(EditAnywhere, Category = Settings)
		FractalConfigSDF LastSDF;
#endif
	/** UInteractiveTool overrides */

	UFUNCTION(Exec)
	void GenerateFractal();

	void TypedFractalName();
};
