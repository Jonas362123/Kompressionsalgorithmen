#include "LZ77.h"

LZ77::LZ77(std::string input, std::string filepath)
{
	inputData = input;
	encode();
	Output(filepath);
}

void LZ77::Output(std::string filepath)
{
	std::ofstream ofs(filepath, std::ofstream::binary | std::ofstream::out); // outputfilestream for writing encoded data to a file
	if (ofs.is_open()) {
		for (triplet triplet : output) {
			ofs << (char*)&triplet.pos;
			ofs << (char*)&triplet.length;
			ofs << triplet.next;
		}
	}
	ofs.close(); // closing file
}

void LZ77::updateLookahead()
{
	if ((inputData.length() != 0) && (win.lookaheadbuf.length() < win.lookaheadbuf_max)) { // conditions for updating buffer: inputdata is not empty & lookaheadbuffer is not full
		int delta_length = win.lookaheadbuf_max - win.lookaheadbuf.length(); // get the space that is left in the lookaheadbuffer
		if (inputData.length() < delta_length)
			delta_length = inputData.length(); // clamp the length to the inputdata
		win.lookaheadbuf.append(inputData, 0, delta_length); // fill the space with inputdata
		inputData.erase(0, delta_length); // erase the data that has been filled into the lookaheadbuffer
	}
}

void LZ77::updateSearch(triplet longest) {
	win.searchbuf.append(win.lookaheadbuf, 0, longest.length + 1); // fill the searchbuffer with the triplet of the lookaheadbuffer
	win.lookaheadbuf.erase(0, longest.length + 1); // erase the part that has been filled to the searchbuffer
	if (win.searchbuf.length() > win.searchbuf_max)
		win.searchbuf.erase(0, win.searchbuf.length() - win.searchbuf_max); // clamp the searchbuffer to max
}

LZ77::triplet LZ77::getLongestMatch()
{
	triplet longest;

	longest.pos = 0;
	longest.length = 0;
	longest.next = win.lookaheadbuf[0];

	for (int i = win.lookaheadbuf.length(); i > 0; i--) { // reverse iterate through the lookaheadbuffer to decrease the length of the substring every iteration
		std::string find = win.lookaheadbuf.substr(0, i); // get the substring of the lookaheadbuffer
		int pos = win.searchbuf.find(find);
		if (pos != std::string::npos) { // store the triplet when the substring is found in the searchbuffer
			longest.pos = pos;
			longest.length = i;
			longest.next = win.lookaheadbuf[i + 1];
			break; // break the loop
		}
	}
	return longest;
}

void LZ77::encode()
{
	std::vector<triplet> out;
	do {
		triplet longest;
		updateLookahead(); // keeping the lookaheadbuffer filled
		longest = getLongestMatch();
		out.push_back(longest); // output the triplet
		updateSearch(longest); // keeping the searchbuffer filled
	} while (win.lookaheadbuf.length() > 0);

	output = out;
}
