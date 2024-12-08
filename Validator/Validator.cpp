#include "Validator.h"

bool HTMLValidator::validateFile(const char* filePath)
{
    FILE* file = fopen(filePath, "r");
    if (file == nullptr)
    {
        printf("Error: Unable to open file %s\n", filePath);
        return false;
    }

    char content[10000] = { 0 };
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file))
    {
        strcat(content, buffer);
    }
    fclose(file);


    return isValidTagStructure(content);
}

bool HTMLValidator::isValidTagStructure(const char* content)
{
    char stack[1000][50];
    int top = -1;

    for (int i = 0; content[i] != '\0'; ++i)
    {
        if (content[i] == '<')
        {
            char tag[50] = { 0 };
            int j = 0;
            bool closingTag = false;

            if (content[i + 1] == '/')
            {
                closingTag = true;
                i++;
            }

            while (content[++i] != '>' && content[i] != '\0')
            {
                if (j < 49) tag[j++] = content[i];
            }

            if (content[i] != '>')
            {
                printf("Error: Invalid tag detected\n");
                return false;
            }

            if (closingTag)
            {
                if (top == -1 || strcmp(stack[top], tag) != 0)
                {
                    printf("Error: Closing tag </%s> does not match\n", tag);
                    return false;
                }
                top--;
            }
            else
            {
                if (top < 999)
                {
                    strcpy(stack[++top], tag);
                }
                else
                {
                    printf("Error: Too many nested tags\n");
                    return false;
                }
            }
        }
    }

    if (top != -1)
    {
        printf("Error: Not all tags are properly closed\n");
        return false;
    }

    return true;
}
