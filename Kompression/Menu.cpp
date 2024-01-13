#include "Menu.h"



void Menu::clear() {
	system("cls"); // clearing the screen
}

Menu::Menu()
{
	init();
}

void Menu::print() {
	clear();
	if (menu_state == 0) {
		std::cout << "Encoder by Jonas Ramrath | https://github.com/Jonas362123/Kompressionsalgorithmen\n\n";

		if (fileError != 0)
			std::cout << "Inputfilestream Error\n\n";

		if (menu_index == 0) std::cout << ">";
		std::cout << "\tLempel-Ziv-Welch\n\n";
		if (menu_index == 1) std::cout << ">";
		std::cout << "\tLempel-Ziv-77\n\n";
		if (menu_index == 2) std::cout << ">";
		std::cout << "\tShannon\n\n";
		if (menu_index == 3) std::cout << ">";
		std::cout << "\tHuffman\n\n";
		if (menu_index == 4) std::cout << ">";
		std::cout << "\tExit\n";
	}
	else if (menu_state == 1) {
		std::cout << "Encoder by Jonas Ramrath | https://github.com/Jonas362123/Kompressionsalgorithmen\n\n";

		if (fileError != 0)
			std::cout << "Outputfilestream Error\npress [<-] to go back";
		else
			std::cout << "Successfully encoded to output file\npress [<-] to go back";

	}
}

int Menu::process_input()
{
	int out = 5;

	if (menu_state == 0) {
		if (GetAsyncKeyState(VK_UP) && menu_index > 0) {
			menu_index--;
			out = 6;
		}
		else if (GetAsyncKeyState(VK_DOWN) && menu_index < menu_index_max) {
			menu_index++;
			out = 6;
		}
		else if (GetAsyncKeyState(VK_RIGHT)) {
			menu_state++;
			out = menu_index;
		}
	}
	else if (menu_state == 1) {
		if (GetAsyncKeyState(VK_LEFT)) {
			menu_state--;
			out = 6;
		}
	}

	return out;
}

int Menu::getMenuIndex()
{
	return menu_index;
}

void Menu::setMenuIndex(int val)
{
	menu_index = val;
}

int Menu::getMenuIndexMax()
{
	return menu_index_max;
}

void Menu::setMenuIndexMax(int val)
{
	menu_index_max = val;
}

int Menu::getMenuState()
{
	return menu_state;
}

void Menu::setMenuState(int val)
{
	menu_state = val;
}

void Menu::setfileError(int val)
{
	fileError = val;
}

void Menu::init()
{ // defining class variables
	fileError = 0;
	menu_index = 0;
	menu_index_max = 4;
	menu_state = 0;

	print(); // printing menu once before the main loop starts
}