#include "LZW.h"

LZW::LZW(std::string input)
{
	encode(input);
}

void LZW::encode(std::string input)
{
	for (int i = 0; i < 256; i++) { // filling the first 256 entries with all 1 byte sequences
		std::string c = ""; // placeholder for the character because conversion is the best / non existent after exiting the scope
		c = char(i); // character of the index i
		dict[c] = i; // filling the dictionary with the character and the index
	}

	for (char new_entry : input) { // iterating through the input string and extracting the new entry
		if (dict.count(entry + new_entry) != 0) { // if the entry + the new entry is already in the dictionary the new entry gets added to the entry
			entry += new_entry;
		}
		else {
			output.push_back(dict[entry]); // if its not in the dictionary the entry gets added to the output
			dict[entry + new_entry] = dictSize++; // the entry + new entry is added into the dictionary
			entry = new_entry; // the entry gets replaced with the new entry
		}
		output.push_back(dict[entry]); // entry gets added to the output at the end
	}

}
