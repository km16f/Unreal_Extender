#include "ExtenderCommands.h"
#include "Extender.h"



#define LOCTEXT_NAMESPACE "FExtenderModule"

void FExtenderCommands::RegisterCommands()
{
	UI_COMMAND(TestCommand, "ExtenderCommands", "Hover Text", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE