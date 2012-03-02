/* $Id: ai_map.hpp 20288 2010-08-01 20:41:46Z yexo $ */

/*
 * This file is part of OpenCoaster Tycoon.
 * OpenCoaster Tycoon is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenCoaster Tycoon is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenCoaster Tycoon. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file ai_map.hpp Everything to query and manipulate map metadata. */

#ifndef AI_MAP_HPP
#define AI_MAP_HPP

#include "ai_object.hpp"
#include "../../tile_type.h"

/**
 * Class that handles all map related functions.
 */
class AIMap : public AIObject {
public:
	static const int TILE_INVALID = (int)INVALID_TILE; ///< Invalid TileIndex.

	/** Get the name of this class to identify it towards squirrel. */
	static const char *GetClassName() { return "AIMap"; }

	/**
	 * Checks whether the given tile is valid.
	 * @param tile The tile to check.
	 * @return True is the tile it within the boundaries of the map.
	 */
	static bool IsValidTile(TileIndex tile);

	/**
	 * Gets the number of tiles in the map.
	 * @return The size of the map in tiles.
	 * @post Return value is always positive.
	 */
	static TileIndex GetMapSize();

	/**
	 * Gets the amount of tiles along the SW and NE border.
	 * @return The length along the SW and NE borders.
	 * @post Return value is always positive.
	 */
	static uint32 GetMapSizeX();

	/**
	 * Gets the amount of tiles along the SE and NW border.
	 * @return The length along the SE and NW borders.
	 * @post Return value is always positive.
	 */
	static uint32 GetMapSizeY();

	/**
	 * Gets the place along the SW/NE border (X-value).
	 * @param tile The tile to get the X-value of.
	 * @pre IsValidTile(tile).
	 * @return The X-value.
	 * @post Return value is always lower than GetMapSizeX().
	 */
	static int32 GetTileX(TileIndex tile);

	/**
	 * Gets the place along the SE/NW border (Y-value).
	 * @param tile The tile to get the Y-value of.
	 * @pre IsValidTile(tile).
	 * @return The Y-value.
	 * @post Return value is always lower than GetMapSizeY().
	 */
	static int32 GetTileY(TileIndex tile);

	/**
	 * Gets the TileIndex given a x,y-coordinate.
	 * @param x The X coordinate.
	 * @param y The Y coordinate.
	 * @pre x < GetMapSizeX().
	 * @pre y < GetMapSizeY().
	 * @return The TileIndex for the given (x,y) coordinate.
	 */
	static TileIndex GetTileIndex(uint32 x, uint32 y);

	/**
	 * Calculates the Manhattan distance; the difference of
	 *  the X and Y added together.
	 * @param tile_from The start tile.
	 * @param tile_to The destination tile.
	 * @pre IsValidTile(tile_from).
	 * @pre IsValidTile(tile_to).
	 * @return The Manhattan distance between the tiles.
	 */
	static int32 DistanceManhattan(TileIndex tile_from, TileIndex tile_to);

	/**
	 * Calculates the distance between two tiles via 1D calculation.
	 *  This means the distance between X or the distance between Y, depending
	 *  on which one is bigger.
	 * @param tile_from The start tile.
	 * @param tile_to The destination tile.
	 * @pre IsValidTile(tile_from).
	 * @pre IsValidTile(tile_to).
	 * @return The maximum distance between the tiles.
	 */
	static int32 DistanceMax(TileIndex tile_from, TileIndex tile_to);

	/**
	 * The squared distance between the two tiles.
	 *  This is the distance is the length of the shortest straight line
	 *  between both points.
	 * @param tile_from The start tile.
	 * @param tile_to The destination tile.
	 * @pre IsValidTile(tile_from).
	 * @pre IsValidTile(tile_to).
	 * @return The squared distance between the tiles.
	 */
	static int32 DistanceSquare(TileIndex tile_from, TileIndex tile_to);

	/**
	 * Calculates the shortest distance to the edge.
	 * @param tile From where the distance has to be calculated.
	 * @pre IsValidTile(tile).
	 * @return The distances to the closest edge.
	 */
	static int32 DistanceFromEdge(TileIndex tile);
};

#endif /* AI_MAP_HPP */