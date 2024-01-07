#pragma once
#include <string>
#include <map>
#include <vector>

class LZW
{
public:
	LZW(std::string input); // constructer calling the encoding function
	std::vector<int> output; // the output as an integer array. vector makes an array with variable size

private:
	std::map<std::string, int> dict; // dictionary for storing indexes of character sequences
	int dictSize = 256; // Size of the dictionary. already 256 because of filling them with 1 byte sequences
	std::string entry;
	void encode(std::string input); // this is where the fun begins

};

