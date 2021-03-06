/* $Id: cheat_func.h 21844 2011-01-18 22:17:15Z rubidium $ */

/*
 * This file is part of OpenCoaster Tycoon.
 * OpenCoaster Tycoon is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenCoaster Tycoon is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenCoaster Tycoon. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file cheat_func.h Functions related to cheating. */

#ifndef CHEAT_FUNC_H
#define CHEAT_FUNC_H

#include "cheat_type.h"

extern Cheats _cheats;

void ShowCheatWindow();

bool CheatHasBeenUsed();

#endif /* CHEAT_FUNC_H */
