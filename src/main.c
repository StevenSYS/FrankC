#include <stdio.h>
#include <ctype.h>
#include <frank.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
	#include <windows.h>
#else
	#include <time.h>
#endif

#include "frankArt.h"
#include "progInfo.h"

#define SIZEOFARRAY(_array) sizeof(_array) / sizeof(_array[0])

static char running = 1;

static char *toLower(char *str) {
	char *tmp = str;
	
	while (tmp[0]) {
		if (
			tmp[0] >= 'A' &&
			tmp[0] <= 'Z'
		) {
			tmp[0] += ('a' - 'A');
		}
		tmp++;
	}
	return str;
}

int main(int argc, char *argv[]) {
	char input[LENGTH_INPUT];
	unsigned char i;
	
	#ifdef _WIN32
	srand(GetTickCount());
	#else
	srand(time(NULL));
	#endif
	
	printf(PROGRAM_NAME " v" PROGRAM_VERSION " - The Frank Chatbot formerly on dingusland.fun ported to C\n");
	printf("Source Code: " URL_SOURCE "\n");
	
	for (i = 0; i < SIZEOFARRAY(frankArt); i++) {
		printf("%s\n", frankArt[i]);
	}
	
	printf("\nPress enter/return with no text entered to quit\n");
	
	if (argc > 1) {
		if (strcmp(argv[1], "TEST\n") != 0) {
			running = 0;
		}
	}
	
	while (running) {
		printf("\n%s\nAsk Frank something: ", frank_response);
		if (fgets(input, LENGTH_INPUT, stdin) == NULL) {
			running = 0;
		}
		
		/* https://stackoverflow.com/questions/1247989/how-do-you-allow-spaces-to-be-entered-using-scanf */
		if (
			strlen(input) > 1 &&
			input[strlen(input) - 1] == '\n'
		) {
			input[strlen(input) - 1] = '\0';
			frank_chat(toLower(input));
		} else if (strlen(input) <= 1) {
			running = 0;
		}
	}
	printf("\nQuitting...\n");
	return 0;
}