/* $Id: null.cpp 21782 2011-01-14 15:34:33Z frosch $ */

/*
 * This file is part of OpenCoaster Tycoon.
 * OpenCoaster Tycoon is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenCoaster Tycoon is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenCoaster Tycoon. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file null.cpp A blitter that doesn't blit. */

#include "../stdafx.h"
#include "null.hpp"

static FBlitter_Null iFBlitter_Null;

Sprite *Blitter_Null::Encode(SpriteLoader::Sprite *sprite, AllocatorProc *allocator)
{
	Sprite *dest_sprite;
	dest_sprite = (Sprite *)allocator(sizeof(*dest_sprite));

	dest_sprite->height = sprite->height;
	dest_sprite->width  = sprite->width;
	dest_sprite->x_offs = sprite->x_offs;
	dest_sprite->y_offs = sprite->y_offs;

	return dest_sprite;
}
