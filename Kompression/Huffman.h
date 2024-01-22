#pragma once
#include <string>
#include <map>
#include <queue>

class Huffman
{
public:
	Huffman(std::string input);
	
	std::map<char, std::string> getOutput();

private:
	std::map<char, int> freq;
	std::map<char, std::string> output;

	struct node {
		char c;
		int freq;
		node* lnode;
		node* rnode;

		node(char d, int frq, node* l, node* r) {
			c = d;
			freq = frq;
			lnode = l;
			rnode = r;
		}
		node(char d, int frq) {
			c = d;
			freq = frq;
			lnode = rnode = nullptr;
		}
	};

	struct higher_freq;

	void codings(const node* top, std::map<char, std::string>& coding, std::string str = "");
	std::map<char, std::string> encode();
};

