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

#ifndef __TOOLS__
#define __TOOLS__

#define sizeofArray(_array) sizeof(_array) / sizeof(*_array)
#define includesString(_str1, _str2) strstr(_str1, _str2) != NULL
#define arrayRandom(_array) _array[rand() % sizeofArray(_array)]

#endif