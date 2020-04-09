#include <optional>
#include "ParseURL.h"
#include <iostream>
#include <map>
#include <regex>

map<Protocol, int> StandardPortValues
{
	{Protocol::HTTP, 80},
	{Protocol::HTTPS, 443},
	{Protocol::FTP ,21}
};

const int MAX_PORT_VALUE = 65535;  

optional<Protocol> GetProtocol(string line)
{
	transform(line.begin(), line.end(), line.begin(), tolower);
	if (line == "http")
	{
		return Protocol::HTTP;
	}
	if (line == "https")
	{
		return Protocol::HTTPS;
	}
	if (line == "ftp")
	{
		return Protocol::FTP;
	}

	return {};
}

optional<int> GetPort(string line, Protocol protocol)
{
	if (line.empty())
	{
		auto it = StandardPortValues.find(protocol);
		return it->second;
	}
	
	int port = atoi(line.c_str());
	if (port < 1 || port > MAX_PORT_VALUE)
	{
		return{};
	}

	return port;
}

bool ParseURL(string const& url, Protocol& protocol, int& port, string& host, string& document)
{
	smatch result;
	regex regularExpression("(^(\\w+)(:\\/\\/)([^\\s:\\/]+)(?::(\\d+))?(?:\\/(\\S*))?$)");
	if (!regex_search(url, result, regularExpression))
	{
		return false;
	}

	optional<Protocol> protocolValue = GetProtocol(result[2]);
	if (!protocolValue)
	{
		return false;
	}
	protocol = protocolValue.value();

	optional<int> portValue = GetPort(result[5], protocol);
	if (!portValue)
	{
		return false;
	}
	
	port = portValue.value();
	host = result[4];
	document = result[6];
 
	return true;
}
