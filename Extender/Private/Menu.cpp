// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu.h"

Menu::Menu()
{
	name = NULL;
	num = 0;
}

Menu::~Menu()
{
	menu_buttons.clear();
	num = 0;
}


void Menu::add_button(Button b)
{
	menu_buttons.push_back(b);
	num++;
}

void Menu::print()
{
	UE_LOG(LogTemp, Warning, TEXT("Menu name: %s"), *name);
	for (int32 i = 0; i < num; i++)
	{
		menu_buttons[i].print_button();
	}
}