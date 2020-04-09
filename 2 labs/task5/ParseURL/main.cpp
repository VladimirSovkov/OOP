#include <iostream>

#include"ParseURL.h"

int main()
{
    std::string stringURL;

	Protocol protocol;
	int port;
	string host;
	string document;

	while (getline(cin, stringURL))
	{
		if (ParseURL(stringURL, protocol, port, host, document))
		{
			cout << stringURL << endl;
			cout << "PORT:  " << port << endl;
			cout << "HOST:  " << host << endl;
			cout << "DOC:  " << document << endl;
		}
		else
		{
			cout << "URL string is entered incorrectly" << endl;
		}
		

	}

	return 0;
}