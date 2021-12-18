#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"

/** INTERFACE FUNCTIONS **/
bool compare(char * inputPath, char * nodePath);
int turns(char * path);

PathLL * buildPaths() {
	PathLL * retval = malloc(sizeof(PathLL));
	retval->head = NULL;
	return retval;
}

void freePaths(PathLL * p) {
	PathNode * nextNode = p -> head;
	PathNode * toFree;

	while (nextNode != NULL)
	{
		toFree = nextNode;
		nextNode = nextNode -> next;
		freeNode(toFree);
	}
	free(p);
}

PathNode * buildNode(char * path) {
	PathNode * newNode = malloc(sizeof(PathNode));
	newNode -> next = NULL;
	newNode -> path = malloc(sizeof(char) * strlen(path) + 1);
	strcpy(newNode -> path, path);
	return newNode;
}

void freeNode(PathNode * p) {
	free(p -> path);
	free(p);
	return;
}

bool addNode(PathLL * paths, char * path) {
	
	//fill in
	if (containsNode(paths, path)) return false;

	PathNode * pointer = paths -> head;

	PathNode * insertNode = buildNode(path);

	if (pointer == NULL)
	{
		paths -> head = insertNode;
		return true;
	}

	if (compare(path, pointer -> path))
	{
		insertNode -> next = paths -> head;
		paths -> head = insertNode;
		return true;
	}

	while (pointer -> next != NULL)
	{
		if (compare(path, pointer -> next -> path))
		{
			insertNode -> next = pointer -> next;
			pointer -> next = insertNode;
			return true;
		}
		pointer = pointer -> next;
	}
	pointer -> next = insertNode;
	return true;
}

bool compare(char * inputPath, char * nodePath)
{
	bool rule1 = strlen(inputPath) < strlen(nodePath);
	bool rule2 = strlen(inputPath) == strlen(nodePath) && turns(inputPath) < turns(nodePath);
	bool rule3 = strlen(inputPath) == strlen(nodePath) && turns(inputPath) == turns(nodePath) && strcmp(inputPath, nodePath) < 0;

	return (rule1 || rule2 || rule3);
}

int turns(char * path)
{
	int turns = 0;

	for (int i = 0; i < strlen(path) - 1; i++)
	{
		if (path[i] != path[i+1])
		{
			turns++;
		}
	}
	return turns;
}

bool removeNode(PathLL * paths, char * path) {
	if (containsNode(paths, path) == false)
	{
		return false;
	}

	PathNode * pointer = paths -> head;
	while (strcmp(path, pointer -> path) != 0)
	{
		pointer = pointer -> next;
	}
	
	PathNode * rnode;
	rnode = pointer -> next;
	pointer -> next = (pointer -> next) -> next;
	freeNode(rnode);
	return true;
}

bool containsNode(PathLL * paths, char * path) {
	PathNode * pointer = paths -> head;
	while (pointer != NULL)
	{
		if(strcmp(path, pointer -> path) == 0)
		{
			return true;
		}
		pointer = pointer -> next;
	}
	return false;
}

void printPaths(PathLL * paths, FILE * fptr) {
	PathNode * curr = paths->head;
	int i = 0;
	while (curr != NULL) {
		fprintf(fptr, "Path %2d: %s\n", i, curr->path);
		i++;
		curr = curr->next;
	}
}
