#pragma once
#include "SlateBasics.h"
#include "EditorStyleSet.h"


class FExtenderCommands : public TCommands<FExtenderCommands>
{
public:

	FExtenderCommands()
		: TCommands<FExtenderCommands>
		(
			TEXT("ExtenderEditor"),
			NSLOCTEXT("Contexts", "ExtenderEditor", "ExtenderEditor Plugin"),
			NAME_None,
			FEditorStyle::GetStyleSetName()
			) {}

	virtual void RegisterCommands() override;

public:

	TSharedPtr<FUICommandInfo> TestCommand;
};