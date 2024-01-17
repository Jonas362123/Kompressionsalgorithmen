#pragma once
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>

class LZ77
{
public:
	LZ77(std::string input, std::string filepath);
	void Output(std::string filepath);


private:
	struct triplet {
		int pos;
		int length;
		char next;
	};

	struct window {
		std::string lookaheadbuf;
		std::string searchbuf;
		int lookaheadbuf_max = 128;
		int searchbuf_max = 4096;
	};

	window win;
	std::string inputData;
	std::vector<triplet> output;
	void updateLookahead();
	void updateSearch(triplet longest);
	triplet getLongestMatch();
	void encode();
};

