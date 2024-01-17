#include "LZW.h"

LZW::LZW(std::string input)
{
	output = encode(input); // constructor assigning output to the result of the encode func
}

std::vector<int> LZW::getOutput()
{
	return output;
}

void LZW::fillDict()
{
	dictSize = 256; // amount of ASCII symbols

	for (int i = 0; i < dictSize; i++) { // filling the first 256 entries with all 1 byte sequences
		std::string c = ""; // placeholder for the character because conversion is the best / non existent after exiting the scope
		c = char(i); // character of the index i
		dict[c] = i; // filling the dictionary with the character and the index
	}
}

std::vector<int> LZW::encode(const std::string input)
{
	std::vector<int> out; // output that gets returned at the end
	std::string entry;

	fillDict();

	for (char new_entry : input) { // iterating through the input string and extracting the new entry
		if (dict.count(entry + new_entry) > 0) { // if the entry + the new entry is already in the dictionary the new entry gets added to the entry
			entry += new_entry;
		}
		else {
			out.emplace_back(dict[entry]); // if its not in the dictionary the entry gets added to the output | difference between push_back & emplace_back nonexistent??
			dict[entry + new_entry] = dictSize++; // the entry + new entry is added into the dictionary
			entry = new_entry; // the entry gets replaced with the new entry
		}
	}
	out.emplace_back(dict[entry]); // entry gets added to the output at the end
	return out;
}