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

#ifndef __LIBFRANK__
#define __LIBFRANK__

void frank_chat(char *input);

/* This function is here so you can use libFrank from Python */
char *frank_getResponse();

extern char frank_response[];

#endif