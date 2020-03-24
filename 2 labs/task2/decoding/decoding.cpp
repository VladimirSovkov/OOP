#include "htmlDecode.h"
#include <iostream>
#include <string>


using namespace std;

int main()
{
	string line;
	while (getline(cin, line))
	{
		line = HtmlDecode(line);
		cout << line << endl;
	}
	
	return 0;
}