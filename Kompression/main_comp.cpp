/*
Programmiert von Jonas Ramrath
Teile des Codes sind inspiriert von:

https://www2.cs.duke.edu/csed/curious/compression/lzw.html (07.01.2024)
http://web.mit.edu/6.02/www/s2012/handouts/3.pdf (07.01.2024)

https://learn.microsoft.com/en-us/previous-versions/87zae4a3(v=vs.140)?redirectedfrom=MSDN (14.01.2024)
https://learn.microsoft.com/de-de/windows/win32/api/shlobj_core/nf-shlobj_core-shgetspecialfolderpathw (14.01.2024)

https://courses.cs.duke.edu/spring03/cps296.5/papers/ziv_lempel_1977_universal_algorithm.pdf (15.01.2024)
https://www5.in.tum.de/lehre/vorlesungen/wipro/ws10/uebung/blatt11.pdf (15.01.2024)
https://learn.microsoft.com/en-us/openspecs/windows_protocols/ms-wusp/fb98aa28-5cd7-407f-8869-a6cef1ff1ccb (15.01.2024)
https://www.wikiwand.com/de/LZ77 (15.01.2024)

https://einstein.informatik.uni-oldenburg.de/rechnernetze/huffmann.htm (21.01.2024)
https://hwlang.de/algorithmen/code/huffman/huffman.htm (21.01.2024)
*/



#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Menu.h"
#include "LZW.h"
#include "LZ77.h"
#include "Huffman.h"

// declaring starting variables
bool exitProgram;
std::string filePath;
std::string filePath_c;
std::string input;

static void init_variables(char **argv) { // defining starting variables
	exitProgram = false;
	filePath = argv[1];
	filePath_c = argv[2];
	input = "";
}

static void init_filestream(Menu* m) {
	std::ifstream fs;

	fs.open(filePath, std::ifstream::in); // Datei zur Auslesung �ffnen
	if (!fs.is_open()) {
		m->setfileError(1, filePath); // Falls der Pfad nicht existiert oder die Datei nicht ge�ffnet werden kann
		m->print();
	}
	std::stringstream ss;
	ss << fs.rdbuf(); // write the file buffer into the stringstream
	input = ss.str(); // write the string into input

	fs.close(); // Important :)
}

static void outputbin(Menu* m, std::vector<int> out) { // output the vector to binary
	std::ofstream ofs(filePath_c, std::ofstream::binary | std::ofstream::out); // outputfilestream for writing encoded data to a file
	if (ofs.is_open()) {
		for (size_t i = 0; i < out.size(); i++) {
			ofs << (char*)&out[i];
		}
	}
	else
		m->setfileError(2, filePath_c); // dont need another m->print(); because the menu is already being updated after the function
	ofs.close(); // closing file
}

static void lzw(Menu* m) {
	LZW enc(input); // calls the lzw constructor
	std::vector<int> out = enc.getOutput(); // get the output

	outputbin(m, out);
}

static void lz77(Menu* m) {
	LZ77 enc(input, filePath_c); // calls the lz77 constructor
}

static void huffman(Menu* m) {
	Huffman enc(input); // calls the huffman constructor
	std::map<char, std::string> out = enc.getOutput(); // get the output
	std::string str;
	for (char c : input) {
		std::map<char, std::string>::iterator it = out.find(c);
		str += it->second;
	}
	
	std::vector<unsigned char> byte_array;

	std::cout << str.length() << " ";

	while (str.length() % 8 > 0)
		str += "0";

	std::cout << str.length() << " ";

	for (int i = 0; i < str.length(); i += 8) {
		std::string byte_str = str.substr(i, 8);
		unsigned char byte = std::stoi(byte_str, nullptr, 2);
		byte_array.push_back(byte);
	}

	std::ofstream ofs(filePath_c, std::ofstream::binary | std::ofstream::out); // outputfilestream for writing encoded data to a file
	if (ofs.is_open()) {
		for (size_t i = 0; i < byte_array.size(); i++) {
			ofs << byte_array[i];
		}
	}
	else
		m->setfileError(2, filePath_c); // dont need another m->print(); because the menu is already being updated after the function
	ofs.close(); // closing file
}

static bool main_loop(Menu* m) { // runs every frame the program is not sleeping
	bool menu_update = false;
	switch (m->process_input()) { // different output based on what key you press
	case 0: // first menu option
		m->print();
		m->setMenuState(2);
		lzw(m); // encode using lzw
		menu_update = true;
		break;
	case 1: // second menu option
		m->print();
		m->setMenuState(2);
		lz77(m); // encode using lz77
		menu_update = true;
		break;
	case 2: // third menu option
		m->print();
		m->setMenuState(2);
		huffman(m);
		menu_update = true;
		break;
	case 3: // fourth menu option
		//m->print();
		m->setMenuState(2);
		// shannon(m);
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

int main(int argc, char **argv)
{
	if (argc < 2) {
		std::cout << "not enough arguments: [Inputfile] [Outputfile]";
		return 0;
	}

	Menu* m = new Menu();
	init_variables(argv); // defining starting variables
	init_filestream(m); // opening target file and filling input string

	while (!exitProgram) { // keeping the program open
		if (main_loop(m)) { // returns true if a menu update is supposed to happen
			m->print(); // print menu
		}
	}

	m->exit();
	delete m; // deleting the menu object
	return 0; // end of program obviously
}