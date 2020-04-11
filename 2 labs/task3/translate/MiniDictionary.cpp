#include "MiniDictionary.h"
#include <algorithm>

using namespace std;

bool IsEng(string line)
{
	transform(line.begin(), line.end(), line.begin(), tolower);
	if (any_of(line.begin(), line.end(), 
		[](char symbol) { return symbol >= 'a' && symbol <= 'z';}))
	{
		return true;
	}

	return false;
}

string RemoveLeadingandTrailingSpaces(string line)
{
	size_t indexOfFirstNonWhitespace = line.find_first_not_of(" \t");
	if (indexOfFirstNonWhitespace == string::npos)
	{
		return "";
	}
	size_t indexOfLastNonWhitespace = line.find_last_not_of(" \t");
	
	line = line.substr(indexOfFirstNonWhitespace, indexOfLastNonWhitespace - indexOfFirstNonWhitespace + 1);
	return line;
}

WordList WriteWordsToList(string line)
{
	WordList wordList;
	string word = "";
	size_t startWord = 0;
	for (size_t endWord = line.find(','); 
		endWord != string::npos; 
		endWord = line.find(',', endWord + 1))
	{
		word = line.substr(startWord, endWord - startWord);
		word = RemoveLeadingandTrailingSpaces(word);
		if (!word.empty())
		{
			wordList.push_back(word);
		}

		startWord = endWord + 1;
	}

	word = line.substr(startWord, line.length() - startWord);
	word = RemoveLeadingandTrailingSpaces(word);
	if (!word.empty())
	{
		wordList.push_back(word);
	}

	return wordList;
}

string WriteWordsToStringFromList(const WordList& wordList)
{
	string outputString = "";
	for (string word : wordList)
	{
		outputString += (word + ", ");
	}

	size_t lineLength = outputString.length();
	if (lineLength > 2 )
	{
		outputString.erase(lineLength - 2, lineLength);
	}
	
	return outputString;
}

bool DownloadTranslationsFromDictionary(std::istream& fileDictionary, Vocabulary& vocabulary)
{
	std::string line;
	while (getline(fileDictionary, line))
	{
		size_t sizeLine = line.length();
		size_t startOfWord = line.find('[');
		size_t endOfWord = line.find(']');

		if ((startOfWord == string::npos) || (endOfWord == string::npos))
		{
			return false;
		}

		if (startOfWord > endOfWord)
		{
			return false;
		}
		
		string wordInEng = line.substr(startOfWord + 1, endOfWord - startOfWord - 1);
		if (endOfWord + 2 > sizeLine)
		{
			return false;
		}

		string stringInRus = line.substr(endOfWord + 1);
		wordInEng = RemoveLeadingandTrailingSpaces(wordInEng);
		WordList wordListInRus = WriteWordsToList(stringInRus);
		if (wordListInRus.size() == 0)
		{
			return false;
		}

		vocabulary[wordInEng] = wordListInRus;
	}

	return true;
}



string TranslationFromEngToRus(string wordEng, const Vocabulary& vocabulary)
{
	auto iteratorVocabulary = vocabulary.find(wordEng);
	if (iteratorVocabulary == vocabulary.end())
	{
		return {};
	}

	return WriteWordsToStringFromList(iteratorVocabulary->second);
}

string TranslationFromRusToEng(string wordRus, const Vocabulary& vocabulary)
{
	WordList wordList;
	for ( auto it = vocabulary.begin(); it != vocabulary.end(); it++)
	{
		wordList = it->second;
		if (find(wordList.begin(), wordList.end(), wordRus) != wordList.end())
		{
			return it->first;
		}
	}

	return "";
}

string Translate(string line, const Vocabulary& vocabulary)
{
	line = RemoveLeadingandTrailingSpaces(line);
	if (IsEng(line))
	{
		return TranslationFromEngToRus(line, vocabulary);
	}
	else
	{
		return TranslationFromRusToEng(line, vocabulary);
	}
}

void AddWordToDictionary(std::string wordInEng, std::string stringInRus, Vocabulary& vocabulary)
{
	if (!IsEng(wordInEng))
	{
		swap(wordInEng, stringInRus);
	}

	wordInEng = RemoveLeadingandTrailingSpaces(wordInEng);
	WordList wordListInRus = WriteWordsToList(stringInRus);

	if (Translate(wordInEng, vocabulary) != "")
	{
		vocabulary[wordInEng].insert(vocabulary[wordInEng].end(), wordListInRus.begin(), wordListInRus.end());
	}
	else
	{
		vocabulary[wordInEng] = wordListInRus;
	}
}

void SavingDictionaryToFile(std::ostream& streamToOutputDictionaryFile, const Vocabulary& vocabulary)
{
	for (auto it = vocabulary.begin(); it != vocabulary.end(); ++it)
	{
		streamToOutputDictionaryFile << '[' << it->first << ']';
		streamToOutputDictionaryFile << ' ' << WriteWordsToStringFromList(it->second) << '\n';
	}
}


