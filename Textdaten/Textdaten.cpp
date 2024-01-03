#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

/*
- Anzahl Wörter :)
- Anzahl Buchstaben :)
- Anzahl unterschiedlicher Wörter
- durchschnitl. Länge/Wort
*/

bool exitProgram;
bool showContent;
int w_count;
int b_count;

int main()
{
    exitProgram = false;
    showContent = true;
    w_count = 0;
    b_count = 0;

    std::fstream fs;
    std::string fPath = "C:\\test.txt"; // Pfad zur Datei
    std::string content = "";
    std::string line = "";

    fs.open(fPath, std::ios_base::in); // Datei zur Auslesung öffnen
    if (!fs.is_open())
        std::cout << "failed to open file"; // Falls der Pfad nicht existiert oder die Datei nicht geöffnet werden kann

    while (std::getline(fs, line)) { // fill content line by line
        content += line += "\n";
    }
    fs.close(); // Importante :)


    //TODO: Sonderzeichen in content entfernen
    //std::isalnum()

    for (int i = 0; i < content.size(); i++) { // loop through every character
        if (content[i] == ' ' || content[i] == '\n') // check if character is a space or absatz thing
            w_count += 1;
        else
            b_count += 1;
    }

    if (showContent)
        std::cout << content << "\n";
    std::cout << "Wordcount: " << std::to_string(w_count); // print amount of words
    std::cout << "\nLettercount: " << std::to_string(b_count); // print amount of letters

    while (!exitProgram) {
        if (GetAsyncKeyState(VK_F1)) exitProgram = true; // only exit if key is pressed
    }

    return 0; // end of program obviously
}
