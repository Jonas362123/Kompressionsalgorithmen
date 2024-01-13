#pragma once
#include <Windows.h>
#include <iostream>

class Menu
{
public:
	Menu(); // constructer runs the function to initialize
	void print();
	int process_input();

	int getMenuIndex();
	void setMenuIndex(int val);
	int getMenuIndexMax();
	void setMenuIndexMax(int val);
	int getMenuState();
	void setMenuState(int val);
	void setfileError(int val);
	
private:
	void clear();
	void init();

	//declaring class variables
	int fileError;
	int menu_index;
	int menu_index_max;
	int menu_state;

};

