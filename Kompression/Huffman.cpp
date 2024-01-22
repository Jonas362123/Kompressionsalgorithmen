#include "Huffman.h"

Huffman::Huffman(std::string input)
{
	freq.clear();
    output.clear();

    for (int i = 0; i < input.size(); i++) {
        if (freq.count(input[i]) == 0) { // check if the symbol is not in the map
            freq.insert({ input[i], 1}); // insert into the map with a count of 1
        }
        else {
            std::map<char, int>::iterator it = freq.find(input[i]); // get an iterator to the symbol
            it->second++; // increase the count of the symbol
        }
    }

    output = encode();
}

std::map<char, std::string> Huffman::getOutput()
{
    return output;
}


struct Huffman::higher_freq {
    bool operator()(node* l, node* r) {
        return (l->freq > r->freq); // comparing the frequencies of two nodes for the priority queue
    }
};

std::map<char, std::string> Huffman::encode()
{
    std::vector<node*> nodes;

    for (std::pair<char, int> pair : freq) { // turn input into nodes
        node* n = new node(NULL, NULL, nullptr, nullptr);
        n->c = pair.first;
        n->freq = pair.second;
        nodes.emplace_back(n);
    }

    std::priority_queue<node*, std::vector<node*>, higher_freq> queue; // store the nodes in a priority queue
    for (node* n : nodes) {
        queue.push(n);
    }

    int size = queue.size();
    for (int i = 1; i < size; ++i) { // build huffman tree | storing nodes with most freq as leafs of root node (top node)
        node* l = queue.top();
        queue.pop();
        node* r = queue.top();
        queue.pop();

        node* n = new node(NULL, NULL, nullptr, nullptr);
        n->freq = l->freq + r->freq;
        n->lnode = l;
        n->rnode = r;
        queue.emplace(n);
    }

    std::map<char, std::string> coding;
    codings(queue.top(), coding); // build codings | queue.top() being the root node of the huffman tree
    return coding;
}

void Huffman::codings(const node* top, std::map<char, std::string>& coding, std::string str)
{
    if (!top->lnode && !top->rnode) {
        coding[top->c] = str; // return the built string as coding when the bottom of the tree is reached
        return;
    }
    // repeat the function when the bottom of the tree has not been reached
    if (top->lnode)
        codings(top->lnode, coding, str + "0"); // add 0 to the string for left node
    if (top->rnode)
        codings(top->rnode, coding, str + "1"); // add 1 to the string for right node
}
