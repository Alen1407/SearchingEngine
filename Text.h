#ifndef WORD_TEXT_H
#define WORD_TEXT_H
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Word.h"
#include <set>
using namespace std;
class Text{
public:
    vector<Word> words;

public:
    Text(const string& filePath){
        ifstream myFile(filePath);
        if(myFile.is_open()){
            string strWord;

            while(myFile >> strWord){
                Word word(strWord);
                word.cleanWord();
                word.normalizeWord("/home/alen/Desktop/Word/texts/words_alpha.txt");
                words.push_back(word);
            }
            removeDuplicates(words);
            myFile.close();
        }
    }

    void removeDuplicates(vector<Word>&);
};

struct WordComparator {
    bool operator()(const Word& a, const Word& b) const {
        return a.content < b.content;
    }
};

void Text::removeDuplicates(vector<Word>& words) {
    std::set<Word, WordComparator> uniqueWords(words.begin(), words.end());
    words.assign(uniqueWords.begin(), uniqueWords.end());
}
#endif //WORD_TEXT_H
