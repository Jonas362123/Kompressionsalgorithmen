#include "LZW.h"

LZW::LZW(std::string input)
{
	output = encode(input); // constructor assigning output to the result of the encode func
}

std::vector<int> LZW::encode(const std::string input)
{
	std::map<std::string, int> dict; // dictionary for storing indexes of character sequences
	int dictSize = 256; // Size of the dictionary. already 256 because of filling them with 1 byte sequences

	for (int i = 0; i < dictSize; i++) { // filling the first 256 entries with all 1 byte sequences
		std::string c = ""; // placeholder for the character because conversion is the best / non existent after exiting the scope
		c = char(i); // character of the index i
		dict[c] = i; // filling the dictionary with the character and the index
	}

	std::vector<int> out; // output that gets returned at the end
	std::string entry;

	for (char new_entry : input) { // iterating through the input string and extracting the new entry
		if (dict.count(entry + new_entry) != 0) { // if the entry + the new entry is already in the dictionary the new entry gets added to the entry
			entry += new_entry;
		}
		else {
			out.emplace_back(dict[entry]); // if its not in the dictionary the entry gets added to the output
			dict[entry + new_entry] = dictSize++; // the entry + new entry is added into the dictionary
			entry = new_entry; // the entry gets replaced with the new entry
		}
	}
	out.emplace_back(dict[entry]); // entry gets added to the output at the end
	return out;
}

/*std::string LZW::decode(const std::vector<int> input)
{
	std::map<int, std::string> inverted_dict;
	int dictSize = 256;

	for (int i = 0; i < 256; i++) {
		std::string c = "";
		c = char(i);
		inverted_dict[i] = c;
	}

	std::string a, b, out;
	a = inverted_dict[input[0]];
	out = a;

	for (int i = 1; i < input.size(); i++) {
		int c = input[i];
		if (inverted_dict.count(c))
			b = inverted_dict[c];
		else if (c == dictSize)
			b = a + a[0];

		out += b;
		inverted_dict[dictSize++] = a + b[0];
		a = b;
	}

	return out;
}*/