#define CATCH_CONFIG_MAIN
#include "..\..\..\catch2\catch.hpp"
#include "..\translate\MiniDictionary.h"

TEST_CASE("checking data loading into the dictionary")
{
	WHEN("a stream with the correct dictionary form is input")
	{
		std::istringstream input("[apple] яблоко\n[cat] кот, кошка\n [red] красный\n [red square] красная площадь");
		Vocabulary inputVocabulary;
		Vocabulary outputVocabulary = {
			{"apple", {"яблоко"}},
			{"cat", {"кот", "кошка"}},
			{"red", {"красный"}},
			{"red square", {"красная площадь"}}
		};

		CHECK(DownloadTranslationsFromDictionary(input, inputVocabulary) == true);
		CHECK(inputVocabulary == outputVocabulary);
	}

	WHEN("empty stream is input")
	{
		std::istringstream input("");
		Vocabulary inputVocabulary;
		Vocabulary outputVocabulary = {};

		CHECK(DownloadTranslationsFromDictionary(input, inputVocabulary) == true);
		CHECK(inputVocabulary == outputVocabulary);
	}

	WHEN("a stream with an incorrect dictionary form is input")
	{
		Vocabulary inputVocabulary;
		std::istringstream incorrectDictionaryFileStream("[apple яблоко\n[cat],\n[red]\nred square красная площадь");
		CHECK(DownloadTranslationsFromDictionary(incorrectDictionaryFileStream, inputVocabulary) == false);
	}

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

	AddWordToDictionary(wordInEng, wordInRus, inputVocabulary);
	CHECK(inputVocabulary == outputVocabulary);

	wordInEng = "apple";
	wordInRus = "яблоко";
	inputVocabulary = {};
	outputVocabulary = {
		{"apple", {"яблоко"}}
	};

	AddWordToDictionary(wordInRus, wordInEng, inputVocabulary);
	CHECK(inputVocabulary == outputVocabulary);

	wordInEng = "cat";
	wordInRus = "кот, кошка";
	outputVocabulary = {
		{"apple", {"яблоко"}},
		{"cat", {"кот", "кошка"}}
	};

	AddWordToDictionary(wordInEng, wordInRus, inputVocabulary);
	CHECK(inputVocabulary == outputVocabulary);
}

TEST_CASE("")
{
	std::ostringstream output("");
	Vocabulary vocabulary = {
		{"apple", {"яблоко"}},
		{"cat", {"кот", "кошка"}},
		{"red", {"красный"}},
		{"red square", {"красная площадь"}}
	};

	SavingDictionaryToFile(output, vocabulary);
	CHECK(output.str() == "[apple] яблоко\n[cat] кот, кошка\n[red] красный\n[red square] красная площадь\n");
}
