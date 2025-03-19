#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#if _WIN32
#include <windows.h>
#else
#include <time.h>
#endif

#include "frank.h"
#include "frankArt.h"
#include "tools.h"
#include "progInfo.h"

char run = 1;

/* https://stackoverflow.com/questions/59036713/how-do-i-convert-a-char-pointer-to-lower-case */
char *stringToLower(char *str) {
	char *ret = str;
	
	while (*str) {
		*str = tolower(*str);
		str++;
	}
	
	return ret;
}

int main() {
	#if _WIN32
	srand(GetTickCount());
	#else
	srand(time(NULL));
	#endif
	
	char *input = malloc(MAX_STRLENGTH);
	
	if (input == NULL) {
		printf("Failed to allocate memory for variable\n");
		return 1;
	}
	
	printf(PROGRAM_NAME " v" PROGRAM_VERSION " - The Frank Chatbot from dingusland.fun ported to C\n");
	#ifdef ENABLE_DEBUGGING
		printf("Debugging Version\n");
	#endif
	printf("Source Code: https://github.com/StevenSYS/frankc\n");
	
	for (unsigned char i = 0; i < sizeofArray(frankArt_frank); i++) {
		printf("%s\n", frankArt_frank[i]);
	}
	
	printf("\nPress enter/return with no text entered to quit\n");
	
	while (run) {
		printf("\n%s\nAsk Frank something: ", frank_response);
		fgets(input, MAX_STRLENGTH, stdin);
		
		/* https://stackoverflow.com/questions/1247989/how-do-you-allow-spaces-to-be-entered-using-scanf */	
		if (strlen(input) > 1 && input[strlen(input) - 1] == '\n') {
			input[strlen(input) - 1] = '\0';
			frank_handleFrankChat(stringToLower(input));
		} else if (strlen(input) <= 1) {
			run = 0;
		}
	}
	
	printf("\nQuitting...\n");
	
	free(input);
	
	return 0;
}