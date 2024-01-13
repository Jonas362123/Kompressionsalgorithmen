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
	std::vector<int> encode(const std::string input); // this is where the fun begins
	//std::string decode(const std::vector<int> input); // decoding for testing purposes

};

