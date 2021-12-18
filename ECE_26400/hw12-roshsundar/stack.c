#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "main.h"

Stack * buildStack()
{
	Stack * retval = malloc(sizeof(Stack));
	retval->head = NULL;
	return retval;
}

StackNode * buildNode(float value) 
{
	StackNode * newNode = malloc(sizeof(StackNode));
	newNode -> next = NULL;
	newNode -> value = 0;
	return newNode;
}

void push(Stack * stack, float value)
{
    StackNode * insertNode = buildNode(value);
    insertNode -> next = stack -> head;
	insertNode -> value = value;
	stack -> head = insertNode;
}

void freeAll(Stack * stack)
{
    StackNode * nextNode = stack -> head;
	StackNode * toFree;

	while (nextNode != NULL)
	{
		toFree = nextNode;
		nextNode = nextNode -> next;
		free(toFree);
	}
	free(stack);
}

popResult pop(Stack * stack)
{
    StackNode * rmNode = stack -> head;
	popResult res;

    if (rmNode == NULL)
    {
		res.value = 0;
		res.good = false;
        return res;
    }

    res.value = rmNode -> value;
	res.good = true;
    stack -> head = stack -> head -> next;
    free(rmNode);
    return res;
}