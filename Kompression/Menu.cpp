#include "Menu.h"
#include "os.h"


void Menu::clear() {
	if (os::get_system() == os::system::win)
		system("cls"); // clearing the screen
	else if (os::get_system() == os::system::lin){
		system("clear");
	}
}

Menu::Menu()
{
	init();
}

void Menu::exit()
{
	clear();
	std::cout << "Successfully exited";
}

void Menu::print() {
	clear();
	if (menu_state == 0) {
		std::cout << "Written by Jonas Ramrath | https://github.com/Jonas362123/Kompressionsalgorithmen\n\n";

		if (fileError != 0)
			std::cout << "Filestream Error value: " << std::to_string(fileError) << " path: " << errorPath << "\n\n";

		std::cout << "1:\tLempel-Ziv-Welch-Algorithm (working as intended)\n\n";
		std::cout << "2:\tLempel-Ziv 77 Algorithm (working as intended)\n\n";
		std::cout << "3:\tHuffman coding (working as intended)\n\n";
		std::cout << "4:\tShannon-Fano coding (not implemented yet)\n\n";
		std::cout << "5:\tExit the program\n";
		std::cout << "Select: ";
	}
	else if (menu_state == 1) {
		std::cout << "Written by Jonas Ramrath | https://github.com/Jonas362123/Kompressionsalgorithmen\n\n";

		std::cout << "Encoding...\n";
	}
	else if (menu_state == 2) {
		std::cout << "Written by Jonas Ramrath | https://github.com/Jonas362123/Kompressionsalgorithmen\n\n";

		if (fileError != 0) {
			std::cout << "Filestream Error" << std::to_string(fileError) << " path: " << errorPath << "\nEnter [9] to go back\n";
			std::cout << "Select: ";
		}
		else {
			std::cout << "Successfully encoded to output file\nEnter [9] to go back\n";
			std::cout << "Select: ";
		}
	}
}

int Menu::process_input()
{
	int out = 5;
	int in = 0;
	std::cin >> in;

	if (menu_state == 0) {
		if (in < 6 && in > 0) {
			menu_state++;
			out = in - 1;
		}
	}
	else if (menu_state == 2) {
		if (in == 9) {
			menu_state = 0;
			out = 6;
		}
	}

	return out;
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
	menu_state = 0;

	print(); // printing menu once before the main loop starts
}