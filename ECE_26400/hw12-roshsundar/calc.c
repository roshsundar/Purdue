#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "main.h"

popResult RPN(char * filename)
{
    popResult ret;
    ret. value = 0;
    ret.good = false;
    
    FILE * ptr = fopen(filename,"r");
    if (ptr == NULL)
    {
        printf("ERROR: No file opened.");
        return ret;
    }

    char element[10];
    if (fscanf(ptr, "%s", element) != 1)
    {
        fclose(ptr);
        return ret;
    }
    rewind(ptr);
    Stack * stack = buildStack();
    while (fscanf(ptr, "%s", element) == 1)
    {
        bool isnum = isNum(element);

        if (isnum)
        {
            push(stack, (float) atof(element));
        }
        else
        {
            popResult pop2 = pop(stack);
            popResult pop1 = pop(stack);

            if (pop2.good == false || pop1.good == false)
            {
                fclose(ptr);
                freeAll(stack);
                return ret;
            }

            float num2 = pop2.value;
            float num1 = pop1.value;
            float num;

            if (strcmp(element, "+") == 0)
            {
                num = num1 + num2;
            }
            else if (strcmp(element, "-") == 0)
            {
                num = num1 - num2;
            }
            else if (strcmp(element, "*") == 0)
            {
                num = num1 * num2;
            }
            else if (strcmp(element, "/") == 0)
            {
                num = num1 / num2;
            }

            push(stack, num);
        }
    }

    // If only one number in stack, expression is good
    // If not, return EXIT_FAILURE
    if (stack -> head -> next != NULL)
    {
        fclose(ptr);
        freeAll(stack);
        return ret;
    }

    ret = pop(stack);
    fclose(ptr);
    freeAll(stack);
    return ret;
}

bool isNum(char * element)
{
    bool isnum = true;

    if (strcmp(element, "-") == 0)
    {
        isnum = false;
        return isnum;
    }

    for (int i = 0; i < strlen(element); i++)
    {
        if (!isdigit(element[i]) && element[i] != '.' && element[i] != '-')
        {
            isnum = false;
            break;
        }
    }

    return isnum;
}