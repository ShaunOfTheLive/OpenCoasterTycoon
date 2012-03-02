/* $Id: townname_func.h 17612 2009-09-22 13:54:54Z smatz $ */

/*
 * This file is part of OpenCoaster Tycoon.
 * OpenCoaster Tycoon is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenCoaster Tycoon is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenCoaster Tycoon. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file townname_func.h Town name generator stuff. */

#ifndef TOWNNAME_FUNC_H
#define TOWNNAME_FUNC_H

char *GenerateTownNameString(char *buf, const char *last, size_t lang, uint32 seed);
char *GetTownName(char *buff, const struct TownNameParams *par, uint32 townnameparts, const char *last);
char *GetTownName(char *buff, const struct Town *t, const char *last);
bool VerifyTownName(uint32 r, const struct TownNameParams *par);
bool GenerateTownName(uint32 *townnameparts);

#endif /* TOWNNAME_FUNC_H */
