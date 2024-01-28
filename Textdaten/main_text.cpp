/*
Programmiert von Jonas Ramrath
Teile des Codes sind inspiriert von:

https://en.cppreference.com/w/cpp/container/map

*/


#include <iostream>
#include <fstream>
#include <string>
#include <map>

bool win = false;

bool exitProgram;
bool showContent;
bool showUniqueWords;
int w_count; // W�rter
int l_count; // Buchstaben/Letter
int non_alnum; // Count f�r nicht alphanumerische Zeichen
std::string str;

std::map<std::string, int> m; // map for storing words {word, count}
std::string tmp = ""; // temporary string to store words into the map

static bool isSeperator(char c) {
    return c == ' ' || c == '\n';
}

static bool countWords() {
    if (str.size() == 0) return false;
    for (int i = 0; i < str.size(); i++) { // again looping through every character
        if (isSeperator(str[i])) { // check if character is a seperator
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
            tmp += str[i]; // put letter into temporary string
            l_count += 1; // increase letter count
        }
    }
    if (w_count == 0 || l_count == 0) return false;
    return true;
}

static void print() {
    if (showContent)
        std::cout << str << "\n";

    if (showUniqueWords) {
        std::cout << "\n\n";
        for (auto& am : m) // iterate through the map
            std::cout << am.first << ": " << am.second << "\n"; // print every unique word and how often they are in the text
    }

    std::cout << "\nAnalyser by Jonas Ramrath | https://github.com/Jonas362123/Kompressionsalgorithmen\n\n";

    std::cout << "Wordcount: " << std::to_string(w_count) // print amount of words
        << "\nLettercount: " << std::to_string(l_count) // print amount of letters
        << "\nAverage wordlength: " << std::to_string((float)l_count / (float)w_count) // print average amount of letters in a word
        << "\nUnique words: " << std::to_string(m.size()) // print number of elements in the map (amount of unique words)
        << "\nNon alphanumeric: " << std::to_string(non_alnum); // print amount of non alphanumeric
}

int main(int argc, char** argv)
{
    if (argc < 1) {
        std::cout << "not enough arguments: [Inputfile]";
        return 0;
    }

    exitProgram = false;
    showContent = false;
    showUniqueWords = true;
    w_count = 0;
    l_count = 0;
    str = "";

    std::fstream fs;
    std::string filePath = argv[1]; // Pfad zur Datei
    std::string line = "";

    fs.open(filePath, std::ios_base::in); // Datei zur Auslesung �ffnen
    if (!fs.is_open())
        std::cout << "failed to open file"; // Falls der Pfad nicht existiert oder die Datei nicht ge�ffnet werden kann

    while (std::getline(fs, line)) { // fill content line by line
        str += line += "\n";
    }

    fs.close(); // Important :)

    for (int i = 0; i < str.size(); i++) { // loop through every character
        str[i] = tolower(str[i]);
        if (!std::isalnum(str[i]) && !isSeperator(str[i])) {
            str.erase(str.begin() + i); // erase everything that is not alphanumeric or a seperator so that only words remain
            non_alnum++;
            i--;
        }
        if (isSeperator(str[i]) && isSeperator(str[i - 1])) {
            str.erase(str.begin() + i); // erase double Seperators
            i--;
        }
    }

    if (!countWords())
        std::cout << "failed counting";

    print();

    std::cout << "\ntype [0] to exit\n:";

    while (!exitProgram) {
        int in = 1;
        std::cin >> in;
        if (in == 0) exitProgram = true; // only exit if key is pressed
    }

    if (win)
        system("cls");
    else 
        system("clear");
    std::cout << "Successfully exited";

    return 0; // end of program obviously
}
