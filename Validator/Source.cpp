#include "Validator.h"

int main()
{
    HTMLValidator validator;

    const char* filePath = "file.html";
    if (validator.validateFile(filePath))
    {
        printf("The file %s is valid.\n", filePath);
    }
    else
    {
        printf("The file %s contains errors.\n", filePath);
    }

    return 0;
}
