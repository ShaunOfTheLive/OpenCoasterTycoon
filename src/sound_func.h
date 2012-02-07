/* $Id: sound_func.h 21698 2011-01-02 18:12:39Z rubidium $ */

/*
 * This file is part of OpenCoaster Tycoon.
 * OpenCoaster Tycoon is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenCoaster Tycoon is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenCoaster Tycoon. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file sound_func.h Functions related to sound. */

#ifndef SOUND_FUNC_H
#define SOUND_FUNC_H

#include "sound_type.h"
#include "vehicle_type.h"
#include "tile_type.h"

extern MusicFileSettings _msf;

void SndPlayTileFx(SoundID sound, TileIndex tile);
void SndPlayVehicleFx(SoundID sound, const Vehicle *v);
void SndPlayFx(SoundID sound);
void SndCopyToPool();

#endif /* SOUND_FUNC_H */
