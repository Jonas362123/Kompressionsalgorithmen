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
int menu_index;
int menu_index_max;

static void init_variables() {
	exitProgram = false;
	fPath = "C:\\uncompressed.txt";
	fPath_comp = "C:\\compressed.txt";
	line = "";
	input = "";
	menu_index = 0;
	menu_index_max = 1;
}

static void init_filestream() { // same as in the other main file
	std::fstream fs;

	fs.open(fPath, std::ios_base::in); // Datei zur Auslesung öffnen
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
	std::cout << "Input file: " << fPath << "\nOutput file: " << fPath_comp;

}

static void init_menu() {
	print_menu();
}

int main()
{
	init_variables(); // defining starting variables
	init_filestream(); // opening target file and filling input string
	init_menu(); // printing menu once before the main loop starts

	while (!exitProgram) {



		if (GetAsyncKeyState(VK_F1)) exitProgram = true;
	}

	return 0; // end of program obviously
}