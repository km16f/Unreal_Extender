// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"




class FExtenderModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	//Wrapper functions for adding certain type of menu to the editor
	void addMenuBarMenu();
	void addToolBar();
	void addSubMenu();

	//Functions called by Extension object to fill extension with menus/toolbars
	void AddMenuExtension(FMenuBarBuilder & temp);
	void AddToolExtension(FToolBarBuilder& temp);
	void AddSubEntry(FMenuBuilder& temp);

	//Functions that add the menu entries to the specific menu/submenu object
	void AddMenuButton(FMenuBuilder& MenuBuilder);
	void AddSubMenuButton(FMenuBuilder& MenuBuilder);

	//Functions mapped to specific buttons to print to LOG when clicked
	void Print();
	void Print2();

	TSharedPtr<class FUICommandList> PluginCommands;

};