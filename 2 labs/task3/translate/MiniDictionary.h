#pragma once
#include <string>
#include <fstream>
#include <map>
#include <vector>

typedef std::vector <std::string> WordList;
typedef std::map <std::string, WordList> Vocabulary;

bool LoadingWordsInDictionary(std::istream &fileDictionary, Vocabulary & vocabulary);
std::string Translate(std::string & line, Vocabulary & vocabulary);
void AddWordToTheDictionary(std::string wordInEng, std::string wordInRus, Vocabulary& vocabulary);
bool SavingTheDictionaryToFile(std::string& nameFile, Vocabulary & vocabulary);
