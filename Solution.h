#ifndef WORD_SOLUTION_H
#define WORD_SOLUTION_H
#include <vector>
#include <string>
#include "Word.h"
#include "Text.h"
#include <iostream>
using namespace std;

struct Node{
    Word data;
    char state;
    Node() : data("  "), state(-1){}
};

int alreadyExists(Word word, vector<Node> data);

class Solution{
private:
    vector<Node> data;
    Text* textptr_1;
    Text* textptr_2;

public:
    Solution(Text* textptr_1, Text* textptr_2) : textptr_1(textptr_1), textptr_2(textptr_2) {}
    void solve(const string&);
    void writeNodesToFile(const string&, const vector<Node>&);
};

void Solution::solve(const string& filename) {
    for(int i = 0; i < size(textptr_1->words); i++){
        Node temp;
        temp.data = textptr_1->words[i].content;
        temp.state = 1;
        data.push_back(temp);
    }

    for(int i = 0; i < size(textptr_2->words); i++){
        if(alreadyExists(textptr_2->words[i], data)){
            data[i].state = 0;

        }else{
            Node temp;
            temp.data = textptr_2->words[i].content;
            temp.state = 2;
            data.push_back(temp);
        }

    }

    writeNodesToFile(filename, data);
}

int alreadyExists(Word word, vector<Node> data){
    for(int i = 0; i < size(data); i++){
        if(data[i].data.content == word.content){
            return i;
        }
    }

    return 0;
}

void Solution::writeNodesToFile(const string& filename, const vector<Node>& nodes) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Failed to open the file: " << filename << std::endl;
        return;
    }

    for (const Node& node : nodes) {
        file << node.data.content << ": ";

        if (node.state == 1) {
            file << "1";
        } else if (node.state == 2) {
            file << "2";
        } else if (node.state == 0) {
            file << "1,2";
        }

        file << std::endl;
    }

    file.close();
}
#endif //WORD_SOLUTION_H