#include <iostream>
#include <cstdio> 
#include <cstring> 
#pragma warning(disable : 4996)

using namespace std;

class HTMLValidator
{
public:
    bool validateFile(const char* filePath);
private:
    bool isValidTagStructure(const char* content);
};

