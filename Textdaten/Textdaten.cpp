#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

bool exitProgram;

int main()
{
    exitProgram = false;

    std::fstream fs;
    std::string fPath = "C:\\Users\\simon\\Desktop\\test.txt";
    std::string content = "";
    std::string line = "";
    fs.open(fPath, std::ios_base::in);
    while (std::getline(fs, line)) {
        content += line += "\n";
    }
    fs.close();
    
    //std::cout << content; //print file content

    while (!exitProgram) {
        if (GetAsyncKeyState(VK_F1)) exitProgram = true;
    }

    return 0;
}
