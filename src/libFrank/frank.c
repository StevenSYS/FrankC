#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arrays.h"

#define sizeofArray(_array) sizeof(_array) / sizeof(*_array)
#define includesString(_str1, _str2) strstr(_str1, _str2) != NULL
#define arrayRandom(_array) _array[rand() % sizeofArray(_array)]

#define LIBFRANK_LENGTH_STRING 255
#define LIBFRANK_ANGER_THRESHOLD 5

char *frank_response = "Frank is waiting...";
static char isLocked = 0;

static unsigned char angerLevel = 0;

static char isBoopingSnoot(char *input) {
	char found = 0;
	
	for (unsigned char i = 0; i < sizeofArray(boopingSnootWords); i++) {
		if (includesString(input, boopingSnootWords[i])) {
			found = 1;
			break;
		}
	}
	
	return found;
}

static char isDenyingRat(char *input) {
	char foundVariation = 0;
	
	for (unsigned char i = 0; i < sizeofArray(typoVariations); i++) {
		if (includesString(input, typoVariations[i])) {
			foundVariation = 1;
			break;
		}
	}
	
	return ( /* This is terrible */
		(includesString(input, "deny") && includesString(input, "rat")) ||
		(foundVariation && includesString(input, "give") && includesString(input, "rat")) ||
		(foundVariation && includesString(input, "have") && includesString(input, "rat")) ||
		(includesString(input, "unable to give") && includesString(input, "rat")) ||
		(includesString(input, "no rat to give")) ||
		(includesString(input, "no rats for frank")) ||
		(includesString(input, "no rat for frank")) ||	
		(includesString(input, "i refuse to give you a rat")) ||
		(includesString(input, "you are not getting a rat")) ||
		(includesString(input, "frank is not getting a rat")) ||
		(includesString(input, "not giving you a rat")) ||
		(includesString(input, "no rats")) ||
		(includesString(input, "takes away rat")) ||	
		(includesString(input, "removes rat")) ||
		(includesString(input, "steals rat back")) ||
		(includesString(input, "snatches rat from frank")) ||
		(includesString(input, "no rat")) ||
		(includesString(input, "frank loses the rat"))
	);
}

void frank_chat(char *input) {
	if (isLocked) {
		if (includesString(input, "dingus")) {
			isLocked = 0;
			angerLevel = 0;
			frank_response = "Frank is back. What do you want?";
		} else {
			frank_response = "Frank is digesting. You need to say the magic word to wake her up.";
		}
	} else if (isDenyingRat(input)) { /* In the original, it checks for "rat" and "give" or "feed", before checking this */
		angerLevel++;
		if (angerLevel < LIBFRANK_ANGER_THRESHOLD) {
			frank_response = (char *)arrayRandom(sadResponses);
		} else {
			frank_response = (char *)arrayRandom(highAngerResponses);
		}
	} else if (includesString(input, "rat") && (includesString(input, "give") || includesString(input, "feed"))) {
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
			frank_response = (char *)arrayRandom(feedingFailureResponses);
		}
	} else if (angerLevel >= LIBFRANK_ANGER_THRESHOLD) {
		frank_response = (char *)arrayRandom(highAngerResponses);
	} else if (includesString(input, "quail")) {
		frank_response = "FRANK IS BANNED FROM QUAILS.";
	} else if (isBoopingSnoot(input)) {
		frank_response = (char *)arrayRandom(boopingSnootResponses);
	} else if (includesString(input, "rat")) {
		frank_response = (char *)arrayRandom(positiveRatResponses);
	} else {
		frank_response = (char *)arrayRandom(neutralResponses);
	}
	return;
}

/* This function is here so you can use libFrank from Python */
char *frank_getResponse() {
	return frank_response;
}