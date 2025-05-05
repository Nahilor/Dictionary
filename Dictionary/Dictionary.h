#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>

// Struct to hold word meaning data
struct WordEntry {
    std::string word;
    std::string meaning;
};


int binarySearch(const std::vector<WordEntry>& words, const std::string& target);
std::string getWordDefinition(const std::string& word);
std::vector<WordEntry> parseWordMeaningsFromFile(const std::string& filename);