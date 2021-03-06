/* $Id: alloc_func.cpp 17693 2009-10-04 17:16:41Z rubidium $ */

/*
 * This file is part of OpenCoaster Tycoon.
 * OpenCoaster Tycoon is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenCoaster Tycoon is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenCoaster Tycoon. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file alloc_func.cpp Functions to 'handle' memory allocation errors */

#include "../stdafx.h"

/**
 * Function to exit with an error message after malloc() or calloc() have failed
 * @param size number of bytes we tried to allocate
 */
void NORETURN MallocError(size_t size)
{
	error("Out of memory. Cannot allocate " PRINTF_SIZE " bytes", size);
}

/**
 * Function to exit with an error message after realloc() have failed
 * @param size number of bytes we tried to allocate
 */
void NORETURN ReallocError(size_t size)
{
	error("Out of memory. Cannot reallocate " PRINTF_SIZE " bytes", size);
}
