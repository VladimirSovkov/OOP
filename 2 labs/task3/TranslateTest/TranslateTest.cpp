#define CATCH_CONFIG_MAIN
#include "..\..\..\catch2\catch.hpp"
#include "..\translate\MiniDictionary.h"

TEST_CASE("checking data loading into the dictionary")
{
	std::ifstream inputCorrectFile("testData/FileWithTheCorrectForm.txt");
	Vocabulary inputVocabulary;
	Vocabulary outputVocabulary = {
		{"apple", {"яблоко"}},
		{"cat", {"кот", "кошка"}},
		{"red", {"красный"}},
		{"red square", {"красная площадь"}}
	};

	CHECK(LoadingWordsInDictionary(inputCorrectFile, inputVocabulary) == true);
	CHECK(inputVocabulary == outputVocabulary);

	inputCorrectFile.close();

	std::ifstream inputEmptyFile("testData/EmptyFile.txt");
	inputVocabulary = {};
	outputVocabulary = {};

	CHECK(LoadingWordsInDictionary(inputEmptyFile, inputVocabulary) == true);
	CHECK(inputVocabulary == outputVocabulary);

	inputEmptyFile.close();

	std::ifstream inputIncorrectFile("testData/FileWithIncorrectDataRecording.txt");
	CHECK(LoadingWordsInDictionary(inputIncorrectFile, inputVocabulary) == false);

	inputIncorrectFile.close();
}

TEST_CASE("check translation search words")
{
	Vocabulary vocabulary = {
		{"apple", {"яблоко"}},
		{"cat", {"кот", "кошка"}},
		{"red", {"красный"}},
		{"red square", {"красная площадь"}}
	};

	std::string inputString = " red ";

	CHECK(Translate(inputString, vocabulary) == "красный");

	inputString = "кошка ";

	CHECK(Translate(inputString, vocabulary) == "cat");

	inputString = "дом ";
	CHECK(Translate(inputString, vocabulary) == "");
}


TEST_CASE("check for adding a word to the dictionary")
{
	Vocabulary inputVocabulary = {};
	std::string wordInEng = "red";
	std::string wordInRus = "красный";
	Vocabulary outputVocabulary = {
		{"red", {"красный"}}
	};

	AddWordToTheDictionary(wordInEng, wordInRus, inputVocabulary);
	CHECK(inputVocabulary == outputVocabulary);

	wordInEng = "apple";
	wordInRus = "яблоко";
	inputVocabulary = {};
	outputVocabulary = {
		{"apple", {"яблоко"}}
	};

	AddWordToTheDictionary(wordInRus, wordInEng, inputVocabulary);
	CHECK(inputVocabulary == outputVocabulary);

	wordInEng = "cat";
	wordInRus = "кот, кошка";
	inputVocabulary = {};
	outputVocabulary = {
		{"cat", {"кот", "кошка"}}
	};

	AddWordToTheDictionary(wordInEng, wordInRus, inputVocabulary);
	CHECK(inputVocabulary == outputVocabulary);
}
