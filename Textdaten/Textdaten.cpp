#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <map>

/*
- Anzahl Wörter :)
- Anzahl Buchstaben :)
- Anzahl unterschiedlicher Wörter :)
- durchschnitl. Länge/Wort
*/

bool exitProgram;
bool showContent;
bool showUniqueWords;
int w_count;
int b_count;

bool isSeperator(char c) {
    return c == ' ' || c == '\n';
}

int main()
{
    exitProgram = false;
    showContent = true;
    showUniqueWords = false;
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

    for (int i = 0; i < content.size(); i++) { // loop through every character
        content[i] = tolower(content[i]);
        if (!std::isalnum(content[i]) && !isSeperator(content[i])) // erase everything that is not alphanumeric or a seperator so that only words remain
            content.erase(content.begin() + i);
    }

    std::map<std::string, int> m; // map for storing words {word, count}
    std::string tmp = ""; // temporary string to store words into the map

    for (int i = 0; i < content.size(); i++) { // again looping through every character
        if (isSeperator(content[i])) { // check if character is a seperator
            if (m.count(tmp) == 0) { // check if the word is not in the map
                m.insert({ tmp, 1 }); // insert into the map with a count of 1
            }
            else { // check if the word is already in the map
                std::map<std::string, int>::iterator it = m.find(tmp); // get an iterator to the word
                it->second++; // increase the count of the word
            }
            tmp.clear(); // clear the temporary string
            w_count += 1; // increase word count
        }
        else {
            tmp += content[i]; // put letter into temporary string
            b_count += 1; // increase letter count
        }
    }

    if (showContent)
        std::cout << content << "\n";
    std::cout << "Wordcount: " << std::to_string(w_count); // print amount of words
    std::cout << "\nLettercount: " << std::to_string(b_count); // print amount of letters
    std::cout << "\nUnique words: " << std::to_string(m.size()); // print number of elements in the map (amount of unique words)

    if (showUniqueWords) {
        std::cout << "\n\n";
        for (auto& am : m) // iterate through the map
            std::cout << am.first << ": " << am.second << "\n"; // print every unique word and how often they are in the text
    }

    while (!exitProgram) {
        if (GetAsyncKeyState(VK_F1)) exitProgram = true; // only exit if key is pressed
    }

    return 0; // end of program obviously
}
