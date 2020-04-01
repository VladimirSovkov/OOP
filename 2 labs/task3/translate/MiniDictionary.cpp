#include "MiniDictionary.h"

using namespace std;

bool IsEng(string line)
{
	for (size_t i = 0; i < line.length(); i++)
	{
		if ((line[i] >= 'A' && line[i] <= 'Z') ||
			(line[i] >= 'a' && line[i] <= 'z'))
		{
			return true;
		}
	}
	return false;
}

string RemoveLeadingandTrailingSpaces(string line)
{
	bool isSpace = true;

	for (size_t i = 0; i < line.length(); )
	{
		if (isSpace && line[i] == ' ')
		{
			line.erase(i, 1);
		}
		else
		{
			isSpace = false;
			if (line[i] == ' ')
			{
				isSpace = true;
			}
			i++;
		}
	}

	size_t indexOfLastCharacter = line.length();
	indexOfLastCharacter -= 1;

	if (indexOfLastCharacter > 0 && line[indexOfLastCharacter] == ' ')
	{
		line.erase(indexOfLastCharacter, 1);
	}

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

string WriteWordsToStringFromList(WordList wordList)
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

bool LoadingWordsInDictionary(std::ifstream & fileDictionary, Vocabulary& vocabulary)
{
	std::string line;
	string wordInEng;
	string stringInRus;
	size_t startOfWord, endOfWord;
	size_t sizeLine = 0;

	while (getline(fileDictionary, line))
	{
		sizeLine = line.length();
		startOfWord = line.find('[');
		endOfWord = line.find(']');

		if ((startOfWord == string::npos) || (endOfWord == string::npos))
		{
			return false;
		}
		
		wordInEng = line.substr(startOfWord + 1, endOfWord - startOfWord - 1);
		if (endOfWord + 2 > sizeLine)
		{
			return false;
		}

		stringInRus = line.substr(endOfWord + 1);

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



string TranslationFromEngToRus(std::string const& wordEng, Vocabulary& vocabulary)
{
	map <string, WordList>::iterator iteratorVocabulary;
	iteratorVocabulary = vocabulary.find(wordEng);
	if (iteratorVocabulary == vocabulary.end())
	{
		return {};
	}

	return WriteWordsToStringFromList(iteratorVocabulary->second);
}

string TranslationFromRusToEng(string const &wordRus, Vocabulary& vocabulary)
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

string Translate(string &line, Vocabulary& vocabulary)
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

void AddWordToTheDictionary(std::string wordInEng, std::string stringInRus, Vocabulary& vocabulary)
{
	if (!IsEng(wordInEng))
	{
		swap(wordInEng, stringInRus);
	}

	wordInEng = RemoveLeadingandTrailingSpaces(wordInEng);
	WordList wordListInRus = WriteWordsToList(stringInRus);

	vocabulary[wordInEng] = wordListInRus;
}

bool SavingTheDictionaryToFile(std::string &nameFile, Vocabulary & vocabulary)
{
	ofstream outputDictionaryFile(nameFile);
	if (!outputDictionaryFile.is_open())
	{
		return false;
	}
	for (auto it = vocabulary.begin(); it != vocabulary.end(); ++it)
	{
		outputDictionaryFile << '[' << it->first << ']';
		outputDictionaryFile << ' ' << WriteWordsToStringFromList(it->second) << '\n';
	}
	
	outputDictionaryFile.close();
	return true;
}


