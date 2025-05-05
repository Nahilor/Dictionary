#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>

struct WordEntry {
    std::string word;
    std::string meaning;
};


int binarySearch(const std::vector<WordEntry>& words, const std::string& target);
std::vector<WordEntry> parseWordMeaningsFromFile(const std::string& filename);