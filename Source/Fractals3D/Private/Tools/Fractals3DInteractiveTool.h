// Copyright PupSik, 2023. All Rights Reserved.

#pragma once

#include "BaseEditorToolCustomization.h"
#include "Fractals3DInteractiveTool.generated.h"

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

/**
 * UFractals3DInteractiveTool is an example Tool that allows the user to measure the 
 * distance between two points. The first point is set by click-dragging the mouse, and
 * the second point is set by shift-click-dragging the mouse.
 */
UCLASS(Blueprintable)
class UFractals3DInteractiveTool : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = Settings)
		FString FractalName;

	UPROPERTY(EditAnywhere, Category = Settings)
		TArray<FractalFoldConfig> FractalConfig;

	UPROPERTY(EditAnywhere, Category = Settings)
		FractalConfigSDF LastSDF;
	/** UInteractiveTool overrides */

	UFUNCTION(Exec)
	void GenerateFractal();
};
