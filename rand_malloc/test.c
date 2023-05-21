#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rand_malloc.h"

void printInReverse(char** text, int size);
char* getLine();
char** getText(int* size);

int main()
{
	int size = 0;
	char** text = getText(&size);

	if (!text) {
		printf("Memory allocation error");
		return 0;
	}

	printInReverse(text, size);

	for (int i = size; i > 0; --i) {
		free(text[i - 1]);
	}
	
	free(text);
	return 0;
}

char** getText(int* size)
{
	char** text = NULL;
	char* line;
	int bufferSize = 1;

	while ((line = getLine())) {
		char** newBuffer = realloc(text, bufferSize * sizeof(char*));

		if (!newBuffer) {
			goto error;
		}

		text = newBuffer;
		text[bufferSize - 1] = line;
		bufferSize++;

		if (
				bufferSize > 2 && 
				text[bufferSize - 2][0] == '\0' && 
				text[bufferSize - 3][0] == '\0'
			) {
			break;
		}
	}

	*size = bufferSize - 1;
	return text;

	error:
		for (int i = bufferSize - 1; i > 0; --i) {
			free(text[i - 1]);
		}
		free(text);
		return NULL;
}

char* getLine()
{
	char* line = NULL;
	char c;
	int bufferSize = 1;

	while ((c = getchar()) != EOF && c != '\n') {
		char* newBuffer = realloc(line, bufferSize);

		if (!newBuffer) {
			free(line);
			return NULL;
		}
		
		line = newBuffer;
		line[bufferSize - 1] = c;
		bufferSize++;
	}

	if ((c == EOF) && bufferSize == 1) {
		return NULL;
	}
	
	char* newBuffer = realloc(line, bufferSize);

	if (!newBuffer) {
		free(line);
		return NULL;
	}
	
	line = newBuffer;
	line[bufferSize - 1] = '\0';

	return line;
}

void printInReverse(char** text, int size)
{
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
}