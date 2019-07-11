// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <vector>

/**
 *
 */

class Button
{
public:

	Button()
	{
		button_name = NULL;
		command = NULL;
		button_label = NULL;
		order = 0;
	}
	~Button()
	{

	}

	void print_button()
	{
		UE_LOG(LogTemp, Warning, TEXT("NAME: %s    COMMAND: %s    LABEL: %s    ORDER: %i"), *button_name, *command, *button_label, order)
	}

	FString button_name;
	FString command;
	FString button_label;
	int32 order;
};

class EXTENDER_API Menu
{
public:
	Menu();
	~Menu();

	FString name;										// name of menu
	FString label;										// display label of menu
	int32 num;											// number of buttons in menu 

	void add_button(Button b);
	void print();

	std::vector<Button> menu_buttons;				// vector of buttons in menu

};


