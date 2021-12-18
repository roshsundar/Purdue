#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

typedef struct StackNode 
{
	float value;
	struct StackNode * next;
} StackNode;

typedef struct Stack
{
	StackNode * head;
} Stack;

Stack * buildStack();

StackNode * buildNode(float value);

void push(Stack * stack, float value);

void freeAll(Stack * stack);

typedef struct popResult
{
	float value;
	bool good;
} popResult;

popResult pop(Stack * stack);

popResult RPN(char * filename);

bool isNum(char * element);