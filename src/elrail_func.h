/* $Id: elrail_func.h 21845 2011-01-18 22:31:06Z rubidium $ */

/*
 * This file is part of OpenCoaster Tycoon.
 * OpenCoaster Tycoon is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenCoaster Tycoon is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenCoaster Tycoon. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file elrail_func.h header file for electrified rail specific functions */

#ifndef ELRAIL_FUNC_H
#define ELRAIL_FUNC_H

#include "rail.h"
#include "tile_cmd.h"
#include "transparency.h"

/**
 * Test if a rail type has catenary
 * @param rt Rail type to test
 */
static inline bool HasCatenary(RailType rt)
{
	return HasBit(GetRailTypeInfo(rt)->flags, RTF_CATENARY);
}

/**
 * Test if we should draw rail catenary
 * @param rt Rail type to test
 */
static inline bool HasCatenaryDrawn(RailType rt)
{
	return HasCatenary(rt) && !IsInvisibilitySet(TO_CATENARY) && !_settings_game.vehicle.disable_elrails;
}

void DrawCatenary(const TileInfo *ti);
void DrawCatenaryOnTunnel(const TileInfo *ti);
void DrawCatenaryOnBridge(const TileInfo *ti);

bool SettingsDisableElrail(int32 p1); ///< _settings_game.disable_elrail callback

#endif /* ELRAIL_FUNC_H */
