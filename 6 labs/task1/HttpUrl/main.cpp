#include "HttpUrl.h"
#include <iostream>

void InformationOutput(const CHttpUrl& url)
{
	std::string urlLine = url.GetURL();
	std::cout << "URL: " << urlLine << std::endl;
	
	Protocol protocol = url.GetProtocol();
	std::cout << "Protocol: ";
	if (protocol == Protocol::HTTP)
	{
		std::cout << "http" << std::endl;
	}
	else if(protocol == Protocol::HTTP)
	{
		std::cout << "https" << std::endl;
	}

	std::cout << "Domain: " << url.GetDomain() << std::endl;
	std::cout << "Port: " << url.GetPort() << std::endl;
	std::cout << "Document: " << url.GetDocument() << std::endl;
}

int main()
{
	std::string inputLine;
	while (!std::cin.eof())
	{
		std::cout << "URL: ";
		getline(std::cin, inputLine);
		try
		{
			CHttpUrl url(inputLine);
			InformationOutput(url);
		}
		catch (const CUrlParsingError& err)
		{
			std::cout << err.what() << std::endl;
		}
		catch (const std::invalid_argument& err)
		{
			std::cout << err.what() << std::endl;
		}
	}
	return 0;
}