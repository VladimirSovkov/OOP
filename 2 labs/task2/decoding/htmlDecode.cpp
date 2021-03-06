#include "htmlDecode.h"
#include <string>
#include <iostream>
#include <unordered_map>

const std::unordered_map <std::string, std::string> codeLibrary =
{ 
	{"&quot;", "\""},
	{"&apos;", "\'"},
	{"&lt;", "<"},
	{"&gt;", ">"},
	{"&amp;", "&"}
};

std::string HtmlDecode(std::string const& html)
{
	std::string decodingLine = html;
	size_t codeIndex;

	for (auto it = codeLibrary.begin(); it != codeLibrary.end(); ++it)
	{
		std::string valueCode = it->first;
		std::string decryptedValue = it->second;
		size_t sizeCode = valueCode.length();

		while ((codeIndex = decodingLine.find(valueCode)) != std::string::npos)
		{
			decodingLine.erase(codeIndex, sizeCode);
			decodingLine.insert(codeIndex, decryptedValue);
		}
	}
	return decodingLine;
}
