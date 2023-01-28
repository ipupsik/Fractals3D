// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveToolBuilder.h"
#include "BaseTools/ClickDragTool.h"
#include "Fractals3DInteractiveTool.generated.h"


/**
 * Builder for UFractals3DInteractiveTool
 */
UCLASS()
class FRACTALS3D_API UFractals3DInteractiveToolBuilder : public UInteractiveToolBuilder
{
	GENERATED_BODY()

public:
	virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override { return true; }
	virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;
};

UENUM()
enum class FractalConfigSDF {
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
	Tree,
	Sierpinski,
	Menger,
	SnowStadium,
	Mausoleum,
	ButterweedHiils,
	Mandelbox
};

/**
 * Property set for the UFractals3DInteractiveTool
 */
UCLASS(Transient)
class FRACTALS3D_API UFractals3DInteractiveToolProperties : public UInteractiveToolPropertySet
{
	GENERATED_BODY()

public:
	UFractals3DInteractiveToolProperties();

	/** First point of measurement */
	UPROPERTY(EditAnywhere, Category = Options)
		FString FractalName;

	/** Second point of measurement */
	UPROPERTY(EditAnywhere, Category = Options)
		TArray<FractalConfigSDF> FractalConfig;
	
	/** Current distance measurement */
	UPROPERTY(EditAnywhere, Category = Options)
		FractalConfigSDF LastSDF;
};



/**
 * UFractals3DInteractiveTool is an example Tool that allows the user to measure the 
 * distance between two points. The first point is set by click-dragging the mouse, and
 * the second point is set by shift-click-dragging the mouse.
 */
UCLASS()
class FRACTALS3D_API UFractals3DInteractiveTool : public UInteractiveTool, public IClickDragBehaviorTarget
{
	GENERATED_BODY()

public:
	/** UInteractiveTool overrides */
	virtual void Setup() override;
	virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;

	/** IClickDragBehaviorTarget implementation */
	virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& PressPos) override;
	virtual void OnClickPress(const FInputDeviceRay& PressPos) override;
	virtual void OnClickDrag(const FInputDeviceRay& DragPos) override;
	// these are not used in this Tool
	virtual void OnClickRelease(const FInputDeviceRay& ReleasePos) override {}
	virtual void OnTerminateDragSequence() override {}

	/** IModifierToggleBehaviorTarget implementation (inherited via IClickDragBehaviorTarget) */
	virtual void OnUpdateModifierState(int ModifierID, bool bIsOn) override;

protected:
	/** Properties of the tool are stored here */
	UPROPERTY()
	TObjectPtr<UFractals3DInteractiveToolProperties> Properties;

	void GenerateFractal();
};
