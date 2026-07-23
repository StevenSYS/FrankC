#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "internal/arrays.h"

#define SIZEOFA(_array) (sizeof(_array) / sizeof(*_array))
#define STRINC(_str1, _str2) (strstr(_str1, _str2) != NULL)
#define ARR_RAND(_array, _size) (_array[rand() % _size])

#define RAND_RESPONSE(_arr) randResponse(_arr, SIZEOFA(_arr))

#define ANGER_THRESHOLD 5

#define MAX_ANGER UCHAR_MAX

static char isLocked = 0;

static unsigned char angerLevel = 0;

char *frank_response = "Frank is waiting...";

static char isBoopingSnoot(const char *input) {
	size_t i;
	
	for (i = 0; i < SIZEOFA(boopingSnootWords); i++) {
		if (STRINC(input, boopingSnootWords[i])) {
			return 1;
		}
	}
	return 0;
}

static char isDenyingRat(const char *input) {
	char foundVariation = 0;
	size_t i;
	
	for (i = 0; i < SIZEOFA(typoVariations); i++) {
		if (STRINC(input, typoVariations[i])) {
			foundVariation = 1;
			break;
		}
	}
	
	return (
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

static void randResponse(
	const char *arr[],
	size_t size
) {
	frank_response = (char *)arr[rand() % size];
	return;
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
		if (angerLevel < MAX_ANGER) { /* Added for safety */
			angerLevel++;
		}
		
		if (angerLevel < ANGER_THRESHOLD) {
			RAND_RESPONSE(sadResponses);
		} else {
			RAND_RESPONSE(highAngerResponses);
		}
	} else if (STRINC(input, "rat") && (STRINC(input, "give") || STRINC(input, "feed"))) {
		if (!(rand() % 10)) {
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
			RAND_RESPONSE(feedingFailureResponses);
		}
	} else if (angerLevel >= ANGER_THRESHOLD) {
		RAND_RESPONSE(highAngerResponses);
	} else if (STRINC(input, "quail")) {
		frank_response = "FRANK IS BANNED FROM QUAILS.";
	} else if (isBoopingSnoot(input)) {
		RAND_RESPONSE(boopingSnootResponses);
	} else if (STRINC(input, "rat")) {
		RAND_RESPONSE(positiveRatResponses);
	} else {
		RAND_RESPONSE(neutralResponses);
	}
	return;
}

/* This function is here so you can use libFrank from something like Python (ew) */
const char *frank_getResponse() {
	return frank_response;
}