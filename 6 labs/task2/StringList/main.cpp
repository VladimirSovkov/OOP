#include "StringList.h"

int main()
{
    CStringList stringList;
    stringList.Insert("str2", stringList.begin());
    stringList.Insert("str1", stringList.begin());
    auto it = ++stringList.begin();
    stringList.Insert("str1.5", it);
    it = ++stringList.begin();
    std::string a = *it;
 	return 0;
}