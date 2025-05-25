#ifndef __LIBFRANK__
#define __LIBFRANK__

void frank_chat(char *input);

/* This function is here so you can use libFrank from Python */
char *frank_getResponse();

extern char frank_response[];

#endif