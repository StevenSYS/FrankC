#ifndef __LIBFRANK__
#define __LIBFRANK__

/* Functions */
void frank_chat(const char *input);

/* This function is here so you can use libFrank from Python */
const char *frank_getResponse();

/* Externs */
extern const char *frank_response; /* This variable is a `const` here so that nothing but the library can modify it */

#endif