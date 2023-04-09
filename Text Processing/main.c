#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* getLine();
char** getText(int* size);

int main()
{
	int size;
	char** text = getText(&size);
	int j;
	for (int i = 0; i < size; i++) {
		if (text[i] == NULL) {
			printf("\n");
			continue;
		}
		for (j = 0; j < strlen(text[i]); j++) {
			printf("%c", text[i][j]);
		}
		printf("\n");
	}
	// Now I just have to print it in reverse.
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
			return NULL;
		}
		arr = arr1;
		arr[size] = c;
		size++;
		c = getchar();
	}
	char* arr1 = realloc(arr, (size + 1) * sizeof(char));
	if (arr1 == NULL) {
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
		return NULL;
	}

	text = malloc(sizeof(char*));
	if (text == NULL) {
		return NULL;
	}
	text[0] = line;
	line = getLine();
	*size = 1;

	while (1) {
		char** text1 = realloc(text, (*size + 1) * sizeof(char*));
		if (text1 == NULL) {
			return NULL;
		}
		text = text1;
		text[*size] = line;
		(*size)++;
		line = getLine();

		if (text[*size - 1] == NULL && text[*size - 2] == NULL) {
			break;
		}
	}

	return text;
}
