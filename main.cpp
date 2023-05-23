#include "Text.h"
#include "Solution.h"

using namespace std;

vector<string> searchWordInFile(const string& filename, const string& word) {
    vector<string> fileNames;

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Failed to open the file: " << filename << endl;
        return fileNames;
    }

    string line;
    while (getline(file, line)) {
        // Split the line into content and state
        size_t colonPos = line.find(':');
        if (colonPos == string::npos) {
            continue;
        }
        string content = line.substr(0, colonPos);
        string state = line.substr(colonPos + 1);

        // Check if the word is found in the content
        if (content.find(word) != std::string::npos) {
            fileNames.push_back(filename + ": " + state);
        }
    }

    file.close();
    return fileNames;
}

int main() {
    Text myText_1("/home/alen/Desktop/Word/texts/1.txt");
    Text myText_2("/home/alen/Desktop/Word/texts/2.txt");

    Solution solution(&myText_1, &myText_2);
    solution.solve("/home/alen/Desktop/Word/texts/db.txt");

    cout << "Enter the word you want to search: ";

    string word;
    cout << "Enter a word to search: ";
    cin >> word;

    vector<string> fileNames = searchWordInFile("/home/alen/Desktop/Word/texts/db.txt", word);

    if (fileNames.empty()) {
        cout << "No files found containing the word '" << word << "'" << endl;
    } else {
        cout << "Files containing the word '" << word << "': ";
        for (const string& fileName : fileNames) {
            cout << fileName << endl;
        }
    }


    return 0;
}
