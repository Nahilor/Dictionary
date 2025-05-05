#include <iostream>
#include <vector>
#include "Dictionary.h"
#include <map>
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;

std::vector<WordEntry> parseWordMeaningsFromFile(const std::string& filename) {
    std::vector<WordEntry> wordEntries;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open " << filename << "\n";
        system("pause");
        return wordEntries; 
    }

    json j;
    file >> j;

    for (auto& item : j.items()) {
        WordEntry wordEntry;
        wordEntry.word = item.key();
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
        if (words[mid].word == target) {
            return mid;
        }
        else if (words[mid].word < target) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }

    return -1;
}