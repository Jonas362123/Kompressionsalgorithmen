/*
Programmiert von Jonas Ramrath
Teile des Codes sind inspiriert von:

https://www2.cs.duke.edu/csed/curious/compression/lzw.html (07.01.2024)
http://web.mit.edu/6.02/www/s2012/handouts/3.pdf (07.01.2024)

*/



#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include "LZW.h"

// declaring starting variables
bool exitProgram;
std::string fPath;
std::string fPath_comp;
std::string line;
std::string input;
std::string output;
int menu_index;
int menu_index_max;
int menu_state;

static void init_variables() {
	exitProgram = false;
	fPath = "C:\\uncompressed.txt";
	fPath_comp = "C:\\compressed.txt";
	line = "";
	input = "";
	output = "";
	menu_index = 0;
	menu_index_max = 1;
	menu_state = 0;
}

static void init_filestream() { // same as in the other main file
	std::ifstream fs;

	fs.open(fPath, std::fstream::in); // Datei zur Auslesung öffnen
	if (!fs.is_open())
		std::cout << "failed to open file\n"; // Falls der Pfad nicht existiert oder die Datei nicht geöffnet werden kann

	while (std::getline(fs, line)) { // fill content line by line
		input += line += "\n";
	}

	fs.close(); // Important :)
}

static void clear() {
	system("cls");
}

static void print_menu() {
	clear();
	if (menu_state == 0) {
		std::cout << "Input file: " << fPath
			<< "\nOutput file: " << fPath_comp << "\n\n";

		if (menu_index == 0) std::cout << ">";
		std::cout << "\tLempel-Ziv-Welch\n\n";
		if (menu_index == 1) std::cout << ">";
		std::cout << "\tExit\n";
	}
	else if (menu_state == 1) {
		std::cout << output;
	}
}

static void init_menu() {
	print_menu();
}

static void lzw() {
	LZW e(input);
	for (int v : e.output) {
		output += std::to_string(v) += " ";
	}
	std::fstream ofs;
	ofs.open(fPath_comp, std::fstream::out);
	ofs.write(output.c_str(), output.size());
	ofs.close();
}

static bool process_input() {
	bool update_menu = false;
	if (menu_state == 0) {
		if (GetAsyncKeyState(VK_UP) && menu_index > 0) {
			menu_index--;
			update_menu = true;
		}
		else if (GetAsyncKeyState(VK_DOWN) && menu_index < menu_index_max) {
			menu_index++;
			update_menu = true;
		}
		else if (GetAsyncKeyState(VK_RIGHT)) {
			switch (menu_index) {
			case 0:
				lzw();
				menu_state++;
				update_menu = true; 
				break;
			case 1:
				exitProgram = true;
				break;
			}
		}
	}
	else if (menu_state == 1) {
		if (GetAsyncKeyState(VK_LEFT)) {
			menu_state = 0;
			update_menu = true;
		}
	}
	return update_menu;
}

int main()
{
	init_variables(); // defining starting variables
	init_filestream(); // opening target file and filling input string
	init_menu(); // printing menu once before the main loop starts

	while (!exitProgram) {

		if (process_input()) // processes the input and returns true for updating the menu
			print_menu();

	}

	return 0; // end of program obviously
}