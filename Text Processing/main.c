#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rand_malloc.h"

char* getLine();
char** getText(int* size);

int main()
{
	int size;
	char** text = getText(&size);
	int i, j;

	for (i = size - 1; i > -1; i--) {
		if (text[i] == NULL) {
			printf("\n");
			continue;
		}
		int wordLength = 0;
		for (j = strlen(text[i]) - 1; j > -1; j--) {
			if (text[i][j] == ' ') {
				for (int k = 1; k <= wordLength; k++) {
					printf("%c", text[i][j + k]);
				}
				printf(" ");
				wordLength = 0;
			}
			else {
				wordLength++;
			}
		}
		for (int k = 1; k <= wordLength; k++) {
			printf("%c", text[i][j + k]);
		}
		printf("\n");
	}
	
	for (int i = 0; i < size; ++i) {
		free(text[i]);
	}
	
	free(text);
	return 0;
}

char* getLine()
{
	char c = getchar();
	if (c == '\n' || c == EOF) {
		return NULL;
	}

	char* arr;
	arr = malloc(sizeof(char));
	if (arr == NULL) {
		return NULL;
	}
	arr[0] = c;
	c = getchar();
	int size = 1;

	while (c != '\n' && c != EOF) {
		char* arr1 = realloc(arr, (size + 1) * sizeof(char));
		if (arr1 == NULL) {
			free(arr1);
			return NULL;
		}
		arr = arr1;
		arr[size] = c;
		size++;
		c = getchar();
	}
	char* arr1 = realloc(arr, (size + 1) * sizeof(char));
	if (arr1 == NULL) {
		free(arr1);
		return NULL;
	}
	arr = arr1;
	arr[size] = '\0';
	return arr;
}

char** getText(int* size)
{
	char** text;
	char* line;
	line = getLine();
	if (line == NULL) {
		free(line);
		return NULL;
	}

	text = malloc(sizeof(char*));
	if (text == NULL) {
		free(text);
		return NULL;
	}
	text[0] = line;
	line = getLine();
	*size = 1;

	while (1) {
		char** text1 = realloc(text, (*size + 1) * sizeof(char*));
		if (text1 == NULL) {
			free(text1);
			return NULL;
		}
		text = text1;
		text[*size] = line;
		(*size)++;
		if (text[*size - 1] == NULL && text[*size - 2] == NULL) {
			break;
		}
		line = getLine();
	}
	*size -= 2;
	char** text1 = realloc(text, *size * sizeof(char*));
	if (text1 == NULL) {
		free(text1);
		return NULL;
	}
	text = text1;
	return text;
}
