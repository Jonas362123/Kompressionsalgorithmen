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
			std::cout << "Filestream Error value: " << std::to_string(fileError) << " path: " << errorPath << "\n\n";

		if (menu_index == 0) std::cout << ">";
		std::cout << "\tLZW\t\t";

		if (menu_index == 0) std::cout << "Lempel-Ziv-Welch-Algorithm (working as intended)\n\n";
		else if (menu_index == 1) std::cout << "Lempel-Ziv 77 Algorithm (not implemented yet)\n\n";
		else if (menu_index == 2) std::cout << "Shannon-Fano coding (not implemented yet)\n\n";
		else if (menu_index == 3) std::cout << "Huffman coding (not implemented yet)\n\n";
		else if (menu_index == 4) std::cout << "Exit the program\n\n";

		if (menu_index == 1) std::cout << ">";
		std::cout << "\tLZ77\n\n";
		if (menu_index == 2) std::cout << ">";
		std::cout << "\tShannon\n\n";
		if (menu_index == 3) std::cout << ">";
		std::cout << "\tHuffman\n\n";
		if (menu_index == 4) std::cout << ">";
		std::cout << "\tX\n";
	}
	else if (menu_state == 1) {
		std::cout << "Encoder by Jonas Ramrath | https://github.com/Jonas362123/Kompressionsalgorithmen\n\n";

		if (fileError != 0)
			std::cout << "Filestream Error" << std::to_string(fileError) << " path: " << errorPath << "\npress [<-] to go back";
		else {
			switch (menu_index) {
			case 0:
				std::cout << "Successfully encoded to output file\npress [<-] to go back";
				break;
			case 1:
				std::cout << "Not implemented yet\npress [<-] to go back";
				break;
			case 2:
				std::cout << "Not implemented yet\npress [<-] to go back";
				break;
			case 3:
				std::cout << "Not implemented yet\npress [<-] to go back";
				break;
			}
		}
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

void Menu::setfileError(int val, std::string path)
{
	fileError = val;
	errorPath = path;
}

void Menu::init()
{ // defining class variables
	fileError = 0;
	menu_index = 0;
	menu_index_max = 4;
	menu_state = 0;

	print(); // printing menu once before the main loop starts
}