// Copyright PupSik, 2023. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Tools/UEdMode.h"
#include "Fractals3DEditorMode.generated.h"

UCLASS()
class UFractals3DEditorMode : public UEdMode
{
	GENERATED_BODY()

public:
	const static FEditorModeID EM_Fractals3DEditorModeId;

	static FString InteractiveToolName;

	UFractals3DEditorMode();
	virtual ~UFractals3DEditorMode();

	/** UEdMode interface */
	virtual void Enter() override;
	virtual void ActorSelectionChangeNotify() override;
	virtual void CreateToolkit() override;
	virtual TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> GetModeCommands() const override;
};