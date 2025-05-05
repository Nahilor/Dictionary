#include <iostream>
#include <vector>
#include "Dictionary.h"
#include <map>
#include "json.hpp"
#include <fstream>

std::string getWordDefinition(const std::string& word) {
	// Simulate a dictionary lookup
	if (word == "example") {
		return "A representative form or pattern.";
	}
	else if (word == "dictionary") {
		return "A reference book containing an alphabetical list of words with information about them.";
	}
	else {
		return "Word not found in the dictionary.";
	}
}

using json = nlohmann::json;

std::vector<WordEntry> parseWordMeaningsFromFile(const std::string& filename) {
    std::vector<WordEntry> wordEntries;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open " << filename << "\n";
        system("pause");
        return wordEntries;  // Return empty vector if file can't be opened
    }

    json j;
    file >> j;

    // Loop through JSON and fill the wordEntries vector
    for (auto& item : j.items()) {
        WordEntry wordEntry;
        wordEntry.word = item.key();  // Word is the key
        if (item.value().contains("MEANINGS") && !item.value()["MEANINGS"].empty()) {
            wordEntry.meaning = item.value()["MEANINGS"][item.value()["MEANINGS"].begin().key()][1];  // First meaning
        }
        wordEntries.push_back(wordEntry);
    }

    return wordEntries;
}


int binarySearch(const std::vector<WordEntry>& words, const std::string& target) {
    int low = 0;
    int high = words.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (words[mid] == target) {
            return mid; // found
        }
        else if (words[mid] < target) {
            low = mid + 1; // search right half
        }
        else {
            high = mid - 1; // search left half
        }
    }

    return -1; // not found
}