#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>

using namespace std;

struct Line
{
	long valueInt;
	char ValueChar;
};

int main()
{
	ifstream inputFile("input9.txt");
	long countExperts = 0;
	inputFile >> countExperts;
	int countScraps = 0;
	inputFile >> countScraps;

	long count = 0;

	vector<Line> straightLine;
	for (long i = 0; i < countExperts; i++)
	{
		inputFile >> count;
		straightLine.push_back({ count, '[' });
		inputFile >> count;
		straightLine.push_back({ count, ']' });
	}

	sort(straightLine.begin(), straightLine.end(), [](const Line& a, const Line& b) {return a.valueInt < b.valueInt; });

	long out = 0;
	count = 0;
	bool isFirst = true;
	Line temp;
	int size = straightLine.size();
	for (int i = 0; i < size; i++)
	{
		if (straightLine[i].ValueChar == '[')
		{
			count++;
			if (!isFirst)
			{
				if (straightLine[i].valueInt == straightLine[i - 1].valueInt and
					straightLine[i - 1].ValueChar == ']')
				{
					continue;
				}

				if (straightLine[i].valueInt == straightLine[i + 1].valueInt and
					straightLine[i + 1].ValueChar == ']')
				{
					continue;
				}
			}

			if (count == countScraps)
			{
				out++;
			}
			isFirst = false;
		}
		else
		{
			count--;
		}
	}

	cout << out << endl;

}