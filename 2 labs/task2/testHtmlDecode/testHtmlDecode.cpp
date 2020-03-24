#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../decoding/htmlDecode.h"

TEST_CASE("An empty line is passed to the input")
{
	std::string html = "";
	std::string emptyLine = "";

	CHECK(HtmlDecode(html) == emptyLine);
}

TEST_CASE("function loop test")
{
	std::string html = "&&&qu&apos;ot;;;....&&&";
	std::string decryptedLine = "&&&qu\'ot;;;....&&&";

	CHECK(HtmlDecode(html) == decryptedLine);

	html = "&&&&&&;;;;.....&&&&";
	decryptedLine = "&&&&&&;;;;.....&&&&";

	CHECK(HtmlDecode(html) == decryptedLine);
}

TEST_CASE("a string with encrypted characters is transmitted")
{
	std::string html = "256 &gt; 254 &amp; &apos;a&apos; &lt; &apos;b&apos;";
	std::string decryptedLine = "256 > 254 & \'a\' < \'b\'";

	CHECK(HtmlDecode(html) == decryptedLine);

	html = "&quot;word&quot;";
	decryptedLine = "\"word\"";

	CHECK(HtmlDecode(html) == decryptedLine);
}