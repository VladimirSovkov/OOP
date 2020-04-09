#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../ParseURL/ParseURL.h"

Protocol protocol;
int port;
string host;
string document;

TEST_CASE("checking for invalid delimiters")
{
	string url = "http:host";
	bool functionResult = ParseURL(url, protocol, port, host, document);

	CHECK(false == functionResult);

	url = "http://host";
	functionResult = ParseURL(url, protocol, port, host, document);

	CHECK(true == functionResult);

	url = "http://host/document";
	functionResult = ParseURL(url, protocol, port, host, document);

	CHECK(true == functionResult);

	url = "https:/host";
	functionResult = ParseURL(url, protocol, port, host, document);

	CHECK(false == functionResult);

	url = "http://host document";
	functionResult = ParseURL(url, protocol, port, host, document);

	CHECK(false == functionResult);

	url = "http/host document";
	functionResult = ParseURL(url, protocol, port, host, document);

	CHECK(false == functionResult);
}

TEST_CASE("checking for different host numbers")
{
	string url = "https://host:65536/document";
	bool functionResult = ParseURL(url, protocol, port, host, document);

	CHECK(false == functionResult);

	url = "https://host:65535/document";
	functionResult = ParseURL(url, protocol, port, host, document);

	CHECK(true == functionResult);

	url = "https://host:1000/document";
	functionResult = ParseURL(url, protocol, port, host, document);

	CHECK(true == functionResult);

	url = "http://host:number/text";
	functionResult = ParseURL(url, protocol, port, host, document);

	CHECK(false == functionResult);

	url = "http://host:/document";
	functionResult = ParseURL(url, protocol, port, host, document);

	CHECK(false == functionResult);
}

TEST_CASE("checking for different protocol values")
{
	string url = "https://host:655/document";
	bool functionResult = ParseURL(url, protocol, port, host, document);

	CHECK(true == functionResult);

	url = "http://host:655/document";
	functionResult = ParseURL(url, protocol, port, host, document);

	CHECK(true == functionResult);

	url = "FTP://host:655/document";
	functionResult = ParseURL(url, protocol, port, host, document);

	CHECK(true == functionResult);

	url = "ht tps://host:655/document";
	functionResult = ParseURL(url, protocol, port, host, document);

	CHECK(false == functionResult);

	url = "TEXT://host:655/document";
	functionResult = ParseURL(url, protocol, port, host, document);

	CHECK(false == functionResult);
}

TEST_CASE("check with invalid host")
{
	string url = "https://ho st:655/document";
	bool functionResult = ParseURL(url, protocol, port, host, document);

	CHECK(false == functionResult);

	url = "https:// host:655/document";
	functionResult = ParseURL(url, protocol, port, host, document);

	CHECK(false == functionResult);
}

TEST_CASE("validation with incorrect document")
{
	string url = "https://ho st:655/doc ument";
	bool functionResult = ParseURL(url, protocol, port, host, document);

	CHECK(false == functionResult);

	url = "https://ho st:655/document/   text";
	functionResult = ParseURL(url, protocol, port, host, document);

	CHECK(false == functionResult);
}

TEST_CASE("check for the correct receipt of data")
{
	string url = "https://host:655/document";
	bool functionResult = ParseURL(url, protocol, port, host, document);
	
	CHECK(protocol == Protocol::HTTPS);
	CHECK(host == "host");
	CHECK(port == 655);
	CHECK(document == "document");
	CHECK(true == functionResult);

	url = "https://host/document";
	functionResult = ParseURL(url, protocol, port, host, document);

	CHECK(protocol == Protocol::HTTPS);
	CHECK(host == "host");
	CHECK(port == 443);
	CHECK(document == "document");
	CHECK(true == functionResult);

	//document = "";
	url = "https://host";
	functionResult = ParseURL(url, protocol, port, host, document);

	CHECK(protocol == Protocol::HTTPS);
	CHECK(host == "host");
	CHECK(port == 443);
	CHECK(document == "");
	CHECK(true == functionResult);
}