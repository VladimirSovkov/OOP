#pragma once
#include <string>
#include <fstream>
#include <map>
#include <vector>

typedef std::vector <std::string> WordList;
typedef std::map <std::string, WordList> Vocabulary;

bool DownloadTranslationsFromDictionary(std::istream &fileDictionary, Vocabulary & vocabulary);
std::string Translate(std::string line, const Vocabulary& vocabulary);
void AddWordToDictionary(std::string wordInEng, std::string wordInRus, Vocabulary& vocabulary);
void SavingDictionaryToFile(std::ostream& streamToOutputDictionaryFile, const Vocabulary& vocabulary);
