/* $Id: clear_func.h 22019 2011-02-07 22:38:02Z rubidium $ */

/*
 * This file is part of OpenCoaster Tycoon.
 * OpenCoaster Tycoon is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenCoaster Tycoon is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenCoaster Tycoon. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file clear_func.h Functions related to clear (MP_CLEAR) land. */

#ifndef CLEAR_FUNC_H
#define CLEAR_FUNC_H

#include "tile_cmd.h"

void DrawHillyLandTile(const TileInfo *ti);
void DrawClearLandTile(const TileInfo *ti, byte set);
void DrawClearLandFence(const TileInfo *ti);
void TileLoopClearHelper(TileIndex tile);

#endif /* CLEAR_FUNC_H */
