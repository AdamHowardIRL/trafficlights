#include <stdio.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE

char* replace_char(char* str, char find, char replace) {
	char *current_pos = strchr(str, find);
	while (current_pos) {
		*current_pos = replace;
		current_pos = strchr(current_pos, find);
	}
	return str;
}

int main(void) {	
	long lSize;

	int i = 0;
	int numProgs = 0;
	char* programs[50];
	char line[50];

	FILE *file;
	file = fopen("my.txt", "r");

	//Read file into array
	while (fgets(line, sizeof line, file) != NULL) {
		programs[i] = strdup(line);
		
		programs[i] = replace_char(programs[i], '\\', '\0');
		programs[i] = replace_char(programs[i], '\n', '\0');

		i++;
		
		numProgs++;
	}

	printf("Words in file: %d \n", numProgs);
	
	//Sort array
	for (int i = 0; i < numProgs; i++) {
		for (int j = i + 1; j < numProgs; j++)
			if (strcmp(programs[i], programs[j]) > 0) {
				char* temp = programs[i];
				programs[i] = programs[j];
				programs[j] = temp;
			}
		printf("%s \n", programs[i]);
	}

	fclose(file);
	getchar();

	return 0;
}

