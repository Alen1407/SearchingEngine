#ifndef WORD_WORD_H
#define WORD_WORD_H
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
using namespace std;
class Word{
public:
    string content;
    Word(const string& content) : content(content) {}
    void cleanWord();
    void normalizeWord(const string&);
};

void Word::cleanWord() {
    string cleanedWord;

    // Remove special characters and convert to lowercase
    for (char& c : content) {
        if (isalpha(c)) {
            cleanedWord += tolower(c);
        }
    }

    content = cleanedWord;
}

bool wordExistsInDictionary(const std::string& word, const std::string& filePath) {
    std::ifstream dictionaryFile(filePath);

    if (!dictionaryFile.is_open()) {
        std::cout << "Failed to open the dictionary file." << std::endl;
        return false;
    }

    std::string dictionaryWord;

    while (dictionaryFile >> dictionaryWord) {
        if (word == dictionaryWord) {
            dictionaryFile.close();
            return true;
        }
    }

    dictionaryFile.close();
    return false;
}

void Word::normalizeWord(const std::string& filePath) {
    string word = content;
    // Convert word to lowercase
    transform(word.begin(), word.end(), word.begin(), [](unsigned char c) {
        return tolower(c);
    });

    // Remove special characters and punctuation marks
    word.erase(remove_if(word.begin(), word.end(), [](unsigned char c) {
        return !isalpha(c);
    }), word.end());

    // Check if word exists in dictionary
    if (wordExistsInDictionary(word, filePath)) {
        return;
    }

    // Attempt to remove 's' from the end of the word
    if (word.length() > 1 && word[word.length() - 1] == 's') {
        std::string singularWord = word.substr(0, word.length() - 1);
        if (wordExistsInDictionary(singularWord, filePath)) {
            word = singularWord;
            return;
        }
    }
}

#endif //WORD_WORD_H