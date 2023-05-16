#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rand_malloc.h"

void printInReverse(char** text, size_t size);
char* readLine();
char** readText(size_t* bufferSize);

int main()
{
	size_t size = 0;
	char** text = readText(&size);

	if (!text) {
		printf("Memory allocation error");
		return 0;
	}

	printInReverse(text, size);

	for (size_t i = size; i > 0; --i) {
		free(text[i - 1]);
	}
	
	free(text);
	return 0;
}

char** readText(size_t* size)
{
	char** text = NULL;
	char* line;
	size_t bufferSize = 1;

	while ((line = readLine())) {
		char** newBuffer = realloc(text, bufferSize * sizeof(char*));

		if (!newBuffer) {
			goto error;
		}

		text = newBuffer;
		text[bufferSize - 1] = line;
		bufferSize++;

		if (
				bufferSize > 2 && 
				text[bufferSize - 2][0] == '\n' && 
				text[bufferSize - 3][0] == '\n'
			) {
			break;
		}
	}

	*size = bufferSize - 1;
	return text;

	error:
		for (size_t i = bufferSize - 1; i > 0; --i) {
			free(text[i - 1]);
		}
		free(text);
		return NULL;
}

char* readLine()
{
	char* line = NULL;
	char c;
	size_t bufferSize = 1;

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

void printInReverse(char** text, size_t size)
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
				for (size_t k = 1; k <= wordLength; k++) {
					printf("%c", text[i][j + k]);
				}

				printf(" ");
				wordLength = 0;
			}
			else {
				wordLength++;
			}
		}

		for (size_t k = 1; k <= wordLength; k++) {
			printf("%c", text[i][j + k]);
		}

		printf("\n");
	}
}