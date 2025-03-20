/*
	This file is part of FrankC.

	FrankC is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	any later version.

	FrankC is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License along with FrankC.
	If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define sizeofArray(_array) sizeof(_array) / sizeof(*_array)
#define includesString(_str1, _str2) strstr(_str1, _str2) != NULL
#define arrayRandom(_array) _array[rand() % sizeofArray(_array)]

#define MAX_FRANK_STRLENGTH 255

char frank_response[MAX_FRANK_STRLENGTH] = "Frank is waiting...";

char isLocked = 0;
unsigned char angerLevel = 0;
const unsigned char angerThreshold = 5;

const char *typoVariations[] = {
	"can't",
	"cant",
	"won't",
	"wont",
	"don't",
	"dont"
};

const char *positiveRatResponses[] = {
	"Frank is interested.",
	"Frank edges closer, tongue flicking.",
	"Frank's pupils dilate with excitement.",
	"Frank starts licking profusely.",
	"Frank perks up instantly.",
	"Frank watches intently, coiled and ready.",
	"Frank slithers forward, very intrigued.",
};

const char *highAngerResponses[] = {
	"Frank hisses fiercely, her eyes narrowing with disdain.",
	"Frank coils tightly, flicking her tongue in irritation.",
	"Frank's scales ripple as she fixes you with a cold glare.",
	"Frank flicks her tongue sharply, showing clear displeasure."
};

const char *feedingFailureResponses[] = {
	"Frank misses completely.",
	"Frank lunges forward and bonks the glass.",
	"Frank strikes but bites herself."
};

const char *neutralResponses[] = {
	"Frank says nothing.",
	"Frank says nothing.",
	"Frank says nothing.",
	"Frank says nothing.",
	"Frank says nothing.",
	"Frank says nothing.",
	"Frank says nothing.",
	"Frank says nothing.",
	"Frank says nothing.",
	"Frank says nothing.",
	"Frank says nothing.",
	"Frank says nothing.",
	"Frank says nothing.",
	"Frank says nothing.",
	"Frank says nothing.",
	"Frank says nothing.",
	"Frank says nothing.",
	"Frank says nothing.",
	"Frank says nothing.",
	"Frank says nothing.",
	"Frank says nothing.",
	"Frank says nothing.",
	"Frank says nothing.",
	"Frank says nothing.",
	"Frank says nothing.",
	"Frank says nothing.",
	"Frank says nothing.",
	"Frank says nothing.",
	"Frank says nothing.",
	"Frank stares at you, unamused.",
	"Frank is too tired to care.",
	"Frank sighs.",
	"Frank curls up and ignores you.",
	"Frank stares at the ceiling.",
	"Frank gives you a blank look.",
	"Frank pretends she didn’t hear that.",
	"Frank looks the other way.",
	"Frank is not impressed.",
	"Frank is too busy doing nothing.",
	"Frank gives you a slow, unblinking stare.",
	"Frank is clearly not interested.",
	"Frank is busy... doing absolutely nothing.",
	"Frank yawns.",
	"Frank doesn’t even bother to look at you.",
	"Frank slithers off without saying a word.",
	"Frank just sits there. Silent.",
	"Frank rolls her eyes (if snakes could roll their eyes).",
	"Frank stares at you like you've said something foolish.",
	"Frank gives you a long, silent stare.",
	"Frank sneezes in your general direction.",
	"Frank doesn’t even flinch.",
	"Frank is having none of this.",
	"Frank seems to have fallen asleep.",
	"Frank hisses softly and says nothing.",
	"Frank looks bored.",
	"Frank flicks her tongue, then ignores you.",
	"Frank just sits there. Existing.",
	"Frank doesn’t dignify that with a response.",
	"Frank slithers into the void.",
	"Frank seems to have mentally checked out.",
	"Frank stares into the middle distance.",
	"Frank stares blankly at the wall.",
	"Frank gives you a look of mild disdain.",
	"Frank is doing her best to look uninterested."
};

const char *sadResponses[] = {
	"Frank coils up, heartbroken.",
	"Frank hisses softly and flicks her tongue.",
	"Frank stares at you with a cold, silent glare.",
	"Frank flicks her tongue in clear disappointment.",
	"Frank disappears into a tight coil, sulking."
};

const char *boopingSnootResponses[] = {
	"Frank recoils instantly, her eyes narrowing.",
	"Frank hisses and coils back.",
	"Frank flinches, her gaze filled with betrayal.",
	"Frank flicks her tongue sharply in disapproval.",
	"Frank stares at you coldly. Don’t do that again.",
	"Frank freezes, her posture radiating displeasure.",
	"Frank actually dislikes snoot boops."
};

const char *boopingSnootWords[] = {
	"boop",
	"snoot boop",
	"booping snoot",
	"boop your snoot"
};

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
			strcpy(frank_response, "Frank is back. What do you want?");
		} else {
			strcpy(frank_response, "Frank is digesting. You need to say the magic word to wake her up.");
		}
	} else if (isDenyingRat(input)) { /* In the original, it checks for "rat" and "give" or "feed", before checking this */
		angerLevel++;
		if (angerLevel < angerThreshold) {
			strcpy(frank_response, arrayRandom(sadResponses));
		} else {
			strcpy(frank_response, arrayRandom(highAngerResponses));
		}
	} else if (includesString(input, "rat") && (includesString(input, "give") || includesString(input, "feed"))) {
		if (rand() < RAND_MAX / 10) {
			if (angerLevel - 1 > 0) {
				angerLevel -= 1;
			} else {
				angerLevel = 0;
			}
			strcpy(frank_response, "*Frank snatches the rat and drags it around for 2 hours*");
			isLocked = 1;
			strcat(frank_response, "\n Frank is digesting. You need to say the magic word to wake her up.");
		} else {
			strcpy(frank_response, arrayRandom(feedingFailureResponses));
		}
	} else if (angerLevel >= angerThreshold) {
		strcpy(frank_response, arrayRandom(highAngerResponses));
	} else if (includesString(input, "quail")) {
		strcpy(frank_response, "FRANK IS BANNED FROM QUAILS.");
	} else if (isBoopingSnoot(input)) {
		strcpy(frank_response, arrayRandom(boopingSnootResponses));
	} else if (includesString(input, "rat")) {
		strcpy(frank_response, arrayRandom(positiveRatResponses));
	} else {
		strcpy(frank_response, arrayRandom(neutralResponses));
	}
	
	return;
}