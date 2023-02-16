// Copyright PupSik, 2023. All Rights Reserved.

#include "BaseEditorToolCustomization.h"
#include "PropertyEditing.h"

#define LOCTEXT_NAMESPACE "DemoTools"

TSharedRef<IDetailCustomization> FBaseEditorToolCustomization::MakeInstance()
{
	return MakeShareable(new FBaseEditorToolCustomization);
}

void FBaseEditorToolCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	TSet<UClass*> Classes;

	TArray<TWeakObjectPtr<UObject>> ObjectsBeingCustomized;
	DetailBuilder.GetObjectsBeingCustomized(/*out*/ ObjectsBeingCustomized);

	for (auto WeakObject : ObjectsBeingCustomized)
	{
		if (UObject* Instance = WeakObject.Get())
		{
			Classes.Add(Instance->GetClass());
		}
	}

	// Create a commands category
	IDetailCategoryBuilder& Category = DetailBuilder.EditCategory("Commands");

	// Create a button for each element
	for (UClass* Class : Classes)
	{
		for (TFieldIterator<UFunction> FuncIt(Class); FuncIt; ++FuncIt)
		{
			UFunction* Function = *FuncIt;
			if (Function->HasAnyFunctionFlags(FUNC_Exec) && (Function->NumParms == 0))
			{
				const FString FunctionName = Function->GetName();
				const FText ButtonCaption = FText::FromString(FunctionName);

				Category.AddCustomRow(ButtonCaption)
					.ValueContent()
					[
						SNew(SButton)
						.Text(ButtonCaption)
						.OnClicked(FOnClicked::CreateStatic(&FBaseEditorToolCustomization::ExecuteToolCommand, &DetailBuilder, Function))
					];
			}
		}
	}
}

FReply FBaseEditorToolCustomization::ExecuteToolCommand(IDetailLayoutBuilder* DetailBuilder, UFunction* MethodToExecute)
{
	TArray<TWeakObjectPtr<UObject>> ObjectsBeingCustomized;
	DetailBuilder->GetObjectsBeingCustomized(/*out*/ ObjectsBeingCustomized);

	for (auto WeakObject : ObjectsBeingCustomized)
	{
		if (UObject* Instance = WeakObject.Get())
		{
			Instance->CallFunctionByNameWithArguments(*MethodToExecute->GetName(), *GLog, nullptr, true);
		}
	}

	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE