#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arrays.h"

#define SIZEOFARRAY(_array) sizeof(_array) / sizeof(*_array)
#define INCLUDESSTRING(_str1, _str2) strstr(_str1, _str2) != NULL
#define ARRAYRANDOM(_array) (char *)_array[rand() % SIZEOFARRAY(_array)]

#define LIBFRANK_ANGER_THRESHOLD 5

char *frank_response = "Frank is waiting...";
static char isLocked = 0;

static unsigned char angerLevel = 0;

static char isBoopingSnoot(char *input) {
	char found = 0;
	
	for (unsigned char i = 0; i < SIZEOFARRAY(boopingSnootWords); i++) {
		if (INCLUDESSTRING(input, boopingSnootWords[i])) {
			found = 1;
			break;
		}
	}
	
	return found;
}

static char isDenyingRat(char *input) {
	char foundVariation = 0;
	
	for (unsigned char i = 0; i < SIZEOFARRAY(typoVariations); i++) {
		if (INCLUDESSTRING(input, typoVariations[i])) {
			foundVariation = 1;
			break;
		}
	}
	
	return ( /* This is terrible */
		(INCLUDESSTRING(input, "deny") && INCLUDESSTRING(input, "rat")) ||
		(foundVariation && INCLUDESSTRING(input, "give") && INCLUDESSTRING(input, "rat")) ||
		(foundVariation && INCLUDESSTRING(input, "have") && INCLUDESSTRING(input, "rat")) ||
		(INCLUDESSTRING(input, "unable to give") && INCLUDESSTRING(input, "rat")) ||
		(INCLUDESSTRING(input, "no rat to give")) ||
		(INCLUDESSTRING(input, "no rats for frank")) ||
		(INCLUDESSTRING(input, "no rat for frank")) ||	
		(INCLUDESSTRING(input, "i refuse to give you a rat")) ||
		(INCLUDESSTRING(input, "you are not getting a rat")) ||
		(INCLUDESSTRING(input, "frank is not getting a rat")) ||
		(INCLUDESSTRING(input, "not giving you a rat")) ||
		(INCLUDESSTRING(input, "no rats")) ||
		(INCLUDESSTRING(input, "takes away rat")) ||	
		(INCLUDESSTRING(input, "removes rat")) ||
		(INCLUDESSTRING(input, "steals rat back")) ||
		(INCLUDESSTRING(input, "snatches rat from frank")) ||
		(INCLUDESSTRING(input, "no rat")) ||
		(INCLUDESSTRING(input, "frank loses the rat"))
	);
}

void frank_chat(char *input) {
	if (isLocked) {
		if (INCLUDESSTRING(input, "dingus")) {
			isLocked = 0;
			angerLevel = 0;
			frank_response = "Frank is back. What do you want?";
		} else {
			frank_response = "Frank is digesting. You need to say the magic word to wake her up.";
		}
	} else if (isDenyingRat(input)) { /* In the original, it checks for "rat" and "give" or "feed", before checking this */
		angerLevel++;
		if (angerLevel < LIBFRANK_ANGER_THRESHOLD) {
			frank_response = ARRAYRANDOM(sadResponses);
		} else {
			frank_response = ARRAYRANDOM(highAngerResponses);
		}
	} else if (INCLUDESSTRING(input, "rat") && (INCLUDESSTRING(input, "give") || INCLUDESSTRING(input, "feed"))) {
		if (rand() % 10 == 1) {
			if (angerLevel - 1 > 0) {
				angerLevel -= 1;
			} else {
				angerLevel = 0;
			}
			frank_response = "*Frank snatches the rat and drags it around for 2 hours*";
			isLocked = 1;
			frank_response = "\n Frank is digesting. You need to say the magic word to wake her up.";
		} else {
			frank_response = ARRAYRANDOM(feedingFailureResponses);
		}
	} else if (angerLevel >= LIBFRANK_ANGER_THRESHOLD) {
		frank_response = ARRAYRANDOM(highAngerResponses);
	} else if (INCLUDESSTRING(input, "quail")) {
		frank_response = "FRANK IS BANNED FROM QUAILS.";
	} else if (isBoopingSnoot(input)) {
		frank_response = ARRAYRANDOM(boopingSnootResponses);
	} else if (INCLUDESSTRING(input, "rat")) {
		frank_response = ARRAYRANDOM(positiveRatResponses);
	} else {
		frank_response = ARRAYRANDOM(neutralResponses);
	}
	return;
}

/* This function is here so you can use libFrank from Python */
char *frank_getResponse() {
	return frank_response;
}