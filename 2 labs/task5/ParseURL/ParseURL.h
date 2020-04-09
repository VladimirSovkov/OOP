#pragma once
#include<string>

using namespace std;

enum class Protocol
{
	HTTP,
	HTTPS,
	FTP
};

bool ParseURL(string const& url, Protocol& protocol, int& port, string& host, string& document);