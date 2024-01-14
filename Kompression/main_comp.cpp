/*
Programmiert von Jonas Ramrath
Teile des Codes sind inspiriert von:

https://www2.cs.duke.edu/csed/curious/compression/lzw.html (07.01.2024)
http://web.mit.edu/6.02/www/s2012/handouts/3.pdf (07.01.2024)

https://learn.microsoft.com/en-us/previous-versions/87zae4a3(v=vs.140)?redirectedfrom=MSDN (14.01.2024)
https://learn.microsoft.com/de-de/windows/win32/api/shlobj_core/nf-shlobj_core-shgetspecialfolderpathw (14.01.2024)

*/



#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <Windows.h>
#include <atlstr.h>
#include <ShlObj_core.h>
#include "LZW.h"
#include "Menu.h"

// declaring starting variables
bool exitProgram;
std::string filePath;
std::string filePath_c;
std::string input;

static void wait() {
	Sleep(150);
}

static void init_variables() { // defining starting variables
	exitProgram = false;
	TCHAR path_c[MAX_PATH];
	std::string path;
	SHGetSpecialFolderPathW(0, path_c, CSIDL_DESKTOP, false); // get Desktop folder path into char array
	path = CW2A(path_c); // convert char array to string
	filePath = path + "\\uncompressed.txt";
	filePath_c = path + "\\compressed.bin";
	input = "";
}

static void init_filestream(Menu* m) {
	std::ifstream fs;

	fs.open(filePath, std::ifstream::in); // Datei zur Auslesung öffnen
	if (!fs.is_open()) {
		m->setfileError(1, filePath); // Falls der Pfad nicht existiert oder die Datei nicht geöffnet werden kann
		m->print();
	}
	std::stringstream ss;
	ss << fs.rdbuf(); // write the file buffer into the stringstream
	input = ss.str(); // write the string into input

	fs.close(); // Important :)
}

static void lzw(Menu* m) {
	LZW enc(input); // calls the lzw constructor
	std::vector<int> vec = enc.output; // set the output to a local variable
	std::ofstream ofs(filePath_c, std::ofstream::binary | std::ofstream::out); // outputfilestream for writing encoded data to a file
	if (ofs.is_open()) {
		for (size_t i = 0; i < vec.size(); i++)
			ofs << (char*)&vec[i];
		//ofs.write((char*)&vec[0], vec.size() * sizeof(int)); // resultet in 3 NULL characters being written after every symbol, increasing file size a lot
	}
	else
		m->setfileError(2, filePath_c); // dont need another m->print(); because the menu is already being updated after the function
	ofs.close(); // closing file
}

static bool main_loop(Menu* m) { // runs every frame the program is not sleeping
	bool menu_update = false;
	switch (m->process_input()) { // different output based on what key you press
	case 0: // first menu option
		lzw(m); // encode using lzw
		menu_update = true;
		break;
	case 1: // second menu option
		// lz77();
		menu_update = true;
		break;
	case 2: // third menu option
		// shannon();
		menu_update = true;
		break;
	case 3: // fourth menu option
		// huffman();
		menu_update = true;
		break;
	case 4: // fifth menu option to exit
		exitProgram = true; // breaks the main loop to terminate the program
		break;
	case 5: // no menu update (nothing happens)
		break;
	case 6: // only menu update nothing else
		menu_update = true;
		break;
	}
	return menu_update;
}

int main()
{
	Menu* m = new Menu();
	init_variables(); // defining starting variables
	init_filestream(m); // opening target file and filling input string

	while (!exitProgram) { // keeping the program open
		if (main_loop(m)) { // returns true if a menu update is supposed to happen
			m->print(); // print menu
			wait(); // waiting after every input for stable control in menu
		}
	}

	delete m; // deleting the menu object
	return 0; // end of program obviously
}