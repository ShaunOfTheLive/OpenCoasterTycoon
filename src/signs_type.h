/* $Id: signs_type.h 21797 2011-01-14 22:08:40Z rubidium $ */

/*
 * This file is part of OpenCoaster Tycoon.
 * OpenCoaster Tycoon is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenCoaster Tycoon is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenCoaster Tycoon. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file signs_type.h Types related to signs */

#ifndef SIGNS_TYPE_H
#define SIGNS_TYPE_H

typedef uint16 SignID;
struct Sign;

static const SignID INVALID_SIGN = 0xFFFF;

static const uint MAX_LENGTH_SIGN_NAME_CHARS  =  32; ///< The maximum length of a sign name in characters including '\0'
static const uint MAX_LENGTH_SIGN_NAME_PIXELS = 255; ///< The maximum length of a sign name in pixels

#endif /* SIGNS_TYPE_H */
