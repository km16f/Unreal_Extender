// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
#include "Extender.h"
#include <vector>
#include "Json.h"
#include "Menu.h"
#include "ExtenderCommands.h"
#include "LevelEditor.h"
#include <fstream>
#include <iostream>



#define LOCTEXT_NAMESPACE "FExtenderModule"

static const FName TabName("ClapTab");
FString menu_label = "CGLumberjack";
FString button_label = "New Button :)";

void FExtenderModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	addMenuBarMenu();
	addToolBar();
	addSubMenu();


	TSharedPtr<FJsonObject> json_obj;
	std::vector<Menu> main_menus;
	TArray<FString> txt_result, temp, buttons;

	FString filename = "C:\\Users\\Molta\\PycharmProjects\\json_tests\\menu.json";
	FString txt_file = "C:\\Users\\Molta\\PycharmProjects\\json_tests\\menu_key.txt";
	FString result;


	FFileHelper::LoadANSITextFileToStrings(*txt_file, NULL, txt_result);
	int32 test = txt_result.Num();


	for (int32 i = 0; i < test; i++)
	{
		Menu test_menu = Menu();

		txt_result[i].ParseIntoArray(temp, TEXT(":"), true);

		test_menu.name = temp[0];

		temp[1].ParseIntoArray(buttons, TEXT(","), true);

		for (int32 p = 0; p < buttons.Num(); p++)
		{
			Button test_button = Button();
			test_button.button_name = buttons[p];
			test_menu.add_button(test_button);
		}
		main_menus.push_back(test_menu);
	}




	FFileHelper::LoadFileToString(result, *filename);
	UE_LOG(LogTemp, Warning, TEXT("Type is %s"), *result);

	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(result);

	if (FJsonSerializer::Deserialize(JsonReader, json_obj))
	{
		TSharedPtr<FJsonObject> new_obj = json_obj->GetObjectField("unreal");

		for (int32 i = 0; i < main_menus.size(); i++)
		{
			TSharedPtr<FJsonObject> menu_obj;
			menu_obj = new_obj->GetObjectField("CGLumberjack");

			
			for (int32 j = 0; j < main_menus[i].num; j++)
			{
				UE_LOG(LogTemp, Warning, TEXT("BUTTON is %s"), *main_menus[i].menu_buttons[j].button_name);
				const FString & temp = main_menus[i].menu_buttons[j].button_name;
				//UE_LOG(LogTemp, Warning, TEXT("FIELD STRING: %s"), *t);
				TSharedPtr<FJsonObject> button_obj = menu_obj->GetObjectField(temp);
				main_menus[i].menu_buttons[j].command = button_obj->GetStringField("command");
				main_menus[i].menu_buttons[j].button_label = button_obj->GetStringField("label");
				main_menus[i].menu_buttons[j].order = button_obj->GetIntegerField("order");
			}
		}
	}

	for (int32 i = 0; i < main_menus.size(); i++)
	{
		main_menus[i].print();
	}

}

void FExtenderModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.


}

void FExtenderModule::addMenuBarMenu()
{
	TSharedPtr<FExtender> Extend = MakeShareable(new FExtender);

	// Param 1: Name of the hook to add to 
	// Param 2: Position relative to the hook,
	// Param 3: The commands for filling the menu, 
	// Param 4: Function to call to fill UI
	Extend->AddMenuBarExtension("Help", EExtensionHook::After, NULL, FMenuBarExtensionDelegate::CreateRaw(this, &FExtenderModule::AddMenuExtension));
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(Extend);
}


void FExtenderModule::addToolBar()
{
	FExtenderCommands::Register();

	TSharedPtr<FUICommandList> Commands = MakeShareable(new FUICommandList);

	// Maps a function to the command list object that will be called by the toolbarbuilder
	Commands->MapAction(
		FExtenderCommands::Get().TestCommand,
		FExecuteAction::CreateRaw(this, &FExtenderModule::Print2)
	);


	TSharedPtr<FExtender> tool = MakeShareable(new FExtender);

	/*
	Param 1: Name of the hook to add to
	Param 2: Position Relative to the hook
	Param 3: Commands attached to the toolbar object
	Param 4: Function to call to fill ui toolbar object
	*/
	tool->AddToolBarExtension("Content", EExtensionHook::After, NULL, FToolBarExtensionDelegate::CreateRaw(this, &FExtenderModule::AddToolExtension));
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(tool);

}


void FExtenderModule::addSubMenu()
{
	TSharedPtr<FExtender> Sub = MakeShareable(new FExtender);

	Sub->AddMenuExtension("Custom", EExtensionHook::After, NULL, FMenuExtensionDelegate::CreateRaw(this, &FExtenderModule::AddSubEntry));
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(Sub);

}


void FExtenderModule::AddMenuExtension(FMenuBarBuilder& MenuBuilder)
{

	FNewMenuDelegate temp;

	// Creates the menu object to be added
	// Param 1: Name of Menu Displayed in Editor
	// Param 2: Name that shows when hovered over
	// Param 3: Function to call to add commands to pulldown menu
	// Param 4: Name of Hook this menu is attached to
	MenuBuilder.AddPullDownMenu(
		FText::FromString(menu_label),
		FText::FromString("Testerino"),
		FNewMenuDelegate::CreateRaw(this, &FExtenderModule::AddMenuButton),
		"NewHook"
	);

}

void FExtenderModule::AddToolExtension(FToolBarBuilder& ToolBuilder)
{
	ToolBuilder.BeginSection("Custom");
	{
		ToolBuilder.AddToolBarButton(FExtenderCommands::Get().TestCommand);
	}
	ToolBuilder.EndSection();

}

void FExtenderModule::AddSubEntry(FMenuBuilder & MenuBuilder)
{
	MenuBuilder.BeginSection("SubSection");
	{
		MenuBuilder.AddSubMenu(
			FText::FromString("SubButton"),
			FText::FromString("Hover Text"),
			FNewMenuDelegate::CreateRaw(this, &FExtenderModule::AddSubMenuButton),
			"Newest"
		);
	}MenuBuilder.EndSection();
}

void FExtenderModule::AddMenuButton(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.BeginSection("Custom");
	{
		MenuBuilder.AddMenuEntry(
			FText::FromString("Open"),
			FText::FromString("Menu tootlip"),
			FSlateIcon(),
			FUIAction(FExecuteAction::CreateRaw(this, &FExtenderModule::Print))
		);
	}
	MenuBuilder.EndSection();

}

void FExtenderModule::AddSubMenuButton(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.BeginSection("NewSub");
	{
		MenuBuilder.AddMenuEntry(
			FText::FromString("NewSubMenu"),
			FText::FromString("Hovering Sub Text"),
			FSlateIcon(),
			FUIAction(FExecuteAction::CreateRaw(this, &FExtenderModule::Print2))
		);
	}
	MenuBuilder.EndSection();

}

void FExtenderModule::Print()
{
	UE_LOG(LogTemp, Warning, TEXT("Hello World!"));
	UE_LOG(LogTemp, Warning, TEXT("Path is %s"), *FPaths::GetProjectFilePath());

}

void FExtenderModule::Print2()
{
	UE_LOG(LogTemp, Warning, TEXT("Button Created!"));
}
#undef LOCTEXT_NAMESPACE



IMPLEMENT_MODULE(FExtenderModule, Extender)