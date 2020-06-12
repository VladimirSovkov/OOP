#include "HttpUrl.h"

const std::map<Protocol, int> STANDARD_PORT
{
	{Protocol::HTTP, 80},
	{Protocol::HTTPS, 443},
};

CHttpUrl::CHttpUrl(std::string const& url)
{
	try
	{
		ParseUrl(url);
	}
	catch(std::invalid_argument& err)
	{
		throw CUrlParsingError(err.what());
	}
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol)
	:CHttpUrl(domain, document, protocol, GetDefaultPort(protocol))
{
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, 
	Protocol protocol, unsigned short port)
{
	if (domain.empty())
	{
		throw std::invalid_argument("domain cannot be an empty string"); 
	}

	if (port < 1 || port > MAX_PORT_VALUE)
	{
		throw std::invalid_argument("port - positive number from 1 to 65535");
	}

	m_domain = GetDomain(domain);
	m_protocol = protocol;
	m_port = port;
	m_document = GetDocument(document);
}

std::string CHttpUrl::GetURL() const
{
	return ProtocolToString() + "://" + m_domain + PortToString() + m_document;
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}

void CHttpUrl::ParseUrl(const std::string& url)
{
	std::smatch result;
	std::regex regularExpression("^(\\w+)(?:\\:\\/\\/)([^\\s:\\/]+)(?::(\\d+))?(?:\\/(\\S*))?$");
	if (!regex_search(url, result, regularExpression))
	{
		throw std::invalid_argument("Incorrect url. protocol://domain[:port][/document]");
	}
	Protocol protocol = GetProtocol(result[1]);
	unsigned short port = GetPort(result[3], protocol);
	m_protocol = protocol;
	m_domain = result[2];
	m_port = port;
	m_document = "/" + std::string(result[4]);
}

Protocol CHttpUrl::GetProtocol(std::string protocol)
{
	std::transform(protocol.begin(), protocol.end(), protocol.begin(), tolower);
	if (protocol == "http")
	{
		return Protocol::HTTP;
	}
	else if (protocol == "https")
	{
		return Protocol::HTTPS;
	}
	throw std::invalid_argument("Incorrect name protocol");
}

int CHttpUrl::GetDefaultPort(const Protocol& protocol) const
{
	auto it = STANDARD_PORT.find(protocol);
	if (it == STANDARD_PORT.end())
	{
		throw std::invalid_argument("this protocol is not included in the list of standard protocols");
	}
	return it->second;
}

std::string CHttpUrl::GetDocument(const std::string& document) const
{
	if (document.empty())
	{
		return "/";
	}
	else if (document[0] == '/')
	{
		return document;
	}
	else
	{
		return "/" + document;
	}
}

std::string CHttpUrl::GetDomain(const std::string& domain) const
{
	if (std::all_of(domain.begin(), domain.end(), [](char symbol) {return symbol != '/'; }))
	{
		return domain;
	}
	throw std::invalid_argument("cannot be \" / \" in the domain");
}

std::string CHttpUrl::ProtocolToString() const
{
	if (m_protocol == Protocol::HTTP)
	{
		return "http";
	}
	else if (m_protocol == Protocol::HTTPS)
	{
		return "https";
	}
	throw std::invalid_argument("no representation for this protocol");
}

std::string CHttpUrl::PortToString() const
{
	auto it = STANDARD_PORT.find(m_protocol);
	if (it != STANDARD_PORT.end() && it->second == m_port)
	{
		return "";
	}

	return ":" + std::to_string(m_port);
}

unsigned short CHttpUrl::GetPort(const std::string& line, const Protocol& protocol) const
{
	int port = 0;
	if (line.empty())
	{
		port = GetDefaultPort(protocol);
	}
	else
	{
		port = atoi(line.c_str());
	}

	if (port < 1 || port > MAX_PORT_VALUE)
	{
		throw std::invalid_argument("port is positive number from 1 to 65535");
	}
	return port;
}
