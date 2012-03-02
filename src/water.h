/* $Id: water.h 20109 2010-07-10 12:45:34Z alberth $ */

/*
 * This file is part of OpenCoaster Tycoon.
 * OpenCoaster Tycoon is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenCoaster Tycoon is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenCoaster Tycoon. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file water.h Functions related to water (management) */

#ifndef WATER_H
#define WATER_H

#include "tile_type.h"
#include "company_type.h"
#include "slope_type.h"

/**
 * Describes the behaviour of a tile during flooding.
 */
enum FloodingBehaviour {
	FLOOD_NONE,    ///< The tile does not flood neighboured tiles.
	FLOOD_ACTIVE,  ///< The tile floods neighboured tiles.
	FLOOD_PASSIVE, ///< The tile does not actively flood neighboured tiles, but it prevents them from drying up.
	FLOOD_DRYUP,   ///< The tile drys up if it is not constantly flooded from neighboured tiles.
};

FloodingBehaviour GetFloodingBehaviour(TileIndex tile);

void TileLoop_Water(TileIndex tile);
bool FloodHalftile(TileIndex t);
void DoFloodTile(TileIndex target);

void ConvertGroundTilesIntoWaterTiles();

void DrawShipDepotSprite(int x, int y, int image);
void DrawWaterClassGround(const struct TileInfo *ti);
void DrawShoreTile(Slope tileh);

void MakeWaterKeepingClass(TileIndex tile, Owner o);

#endif /* WATER_H */
