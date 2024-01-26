#pragma once
#include <iostream>
#include <string>

class Menu
{
public:
	Menu(); // constructer runs the function to initialize
	void exit();
	void print();
	int process_input();

	int getMenuState();
	void setMenuState(int val);
	void setfileError(int val, std::string path);
	
private:
	void clear();
	void init();

	//declaring class variables
	int fileError;
	std::string errorPath;
	int menu_state;

};

