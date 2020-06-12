#pragma once
#include "UrlParsingError.h"
#include <string>
#include <regex>
#include <algorithm>
#include <map>

enum class Protocol
{
	HTTP,
	HTTPS
};

class CHttpUrl
{

public:
	CHttpUrl(std::string const& url);
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol = Protocol::HTTP);	
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol,
		unsigned short port);

	std::string GetURL()const;
	std::string GetDomain()const;
	std::string GetDocument()const;
	Protocol GetProtocol()const;
	unsigned short GetPort()const;

private:
	void ParseUrl(const std::string& url);

	Protocol GetProtocol(std::string protocol);
	unsigned short GetPort(const std::string& line, const Protocol& protocol) const;
	int GetDefaultPort(const Protocol& protocol) const;
	std::string GetDocument(const std::string& document) const;
	std::string GetDomain(const std::string& domain) const;

	std::string ProtocolToString() const;
	std::string PortToString() const;

	const int MAX_PORT_VALUE = 65535;
	
	Protocol m_protocol;
	std::string m_domain;
	unsigned short m_port;
	std::string m_document;
};

