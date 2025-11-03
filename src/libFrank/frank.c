#include <stdlib.h>
#include <string.h>

#include "arrays.h"

#define SIZEOFARRAY(_array) sizeof(_array) / sizeof(_array[0])
#define STRINC(_str1, _str2) strstr(_str1, _str2) != NULL
#define ARRAYRANDOM(_array) (char *)_array[rand() % SIZEOFARRAY(_array)]

#define LIBFRANK_ANGER_THRESHOLD 5

static char isLocked = 0;

static unsigned char angerLevel = 0;

char *frank_response = "Frank is waiting...";

static char isBoopingSnoot(const char *input) {
	char found = 0;
	unsigned char i;
	
	for (i = 0; i < SIZEOFARRAY(boopingSnootWords); i++) {
		if (STRINC(input, boopingSnootWords[i])) {
			found = 1;
			break;
		}
	}
	
	return found;
}

static char isDenyingRat(const char *input) {
	char foundVariation = 0;
	unsigned char i;
	
	for (i = 0; i < SIZEOFARRAY(typoVariations); i++) {
		if (STRINC(input, typoVariations[i])) {
			foundVariation = 1;
			break;
		}
	}
	
	return ( /* This is terrible */
		(STRINC(input, "deny") && STRINC(input, "rat")) ||
		(foundVariation && STRINC(input, "give") && STRINC(input, "rat")) ||
		(foundVariation && STRINC(input, "have") && STRINC(input, "rat")) ||
		(STRINC(input, "unable to give") && STRINC(input, "rat")) ||
		(STRINC(input, "no rat to give")) ||
		(STRINC(input, "no rats for frank")) ||
		(STRINC(input, "no rat for frank")) ||
		(STRINC(input, "i refuse to give you a rat")) ||
		(STRINC(input, "you are not getting a rat")) ||
		(STRINC(input, "frank is not getting a rat")) ||
		(STRINC(input, "not giving you a rat")) ||
		(STRINC(input, "no rats")) ||
		(STRINC(input, "takes away rat")) ||
		(STRINC(input, "removes rat")) ||
		(STRINC(input, "steals rat back")) ||
		(STRINC(input, "snatches rat from frank")) ||
		(STRINC(input, "no rat")) ||
		(STRINC(input, "frank loses the rat"))
	);
}

void frank_chat(const char *input) {
	if (isLocked) {
		if (STRINC(input, "dingus")) {
			isLocked = 0;
			angerLevel = 0;
			frank_response = "Frank is back. What do you want?";
		} else {
			frank_response = "Frank is digesting. You need to say the magic word to wake her up.";
		}
	} else if (isDenyingRat(input)) { /* In the original, it checks for "rat" and "give" or "feed" before checking this */
		angerLevel++;
		if (angerLevel < LIBFRANK_ANGER_THRESHOLD) {
			frank_response = ARRAYRANDOM(sadResponses);
		} else {
			frank_response = ARRAYRANDOM(highAngerResponses);
		}
	} else if (STRINC(input, "rat") && (STRINC(input, "give") || STRINC(input, "feed"))) {
		if (rand() % 1 == 0) {
			if (angerLevel - 1 > 0) {
				angerLevel -= 1;
			} else {
				angerLevel = 0;
			}
			frank_response = 
				"*Frank snatches the rat and drags it around for 2 hours*\n"
				" Frank is digesting. You need to say the magic word to wake her up.";
			isLocked = 1;
		} else {
			frank_response = ARRAYRANDOM(feedingFailureResponses);
		}
	} else if (angerLevel >= LIBFRANK_ANGER_THRESHOLD) {
		frank_response = ARRAYRANDOM(highAngerResponses);
	} else if (STRINC(input, "quail")) {
		frank_response = "FRANK IS BANNED FROM QUAILS.";
	} else if (isBoopingSnoot(input)) {
		frank_response = ARRAYRANDOM(boopingSnootResponses);
	} else if (STRINC(input, "rat")) {
		frank_response = ARRAYRANDOM(positiveRatResponses);
	} else {
		frank_response = ARRAYRANDOM(neutralResponses);
	}
	return;
}

/* This function is here so you can use libFrank from Python */
const char *frank_getResponse() {
	return frank_response;
}