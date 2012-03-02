/* $Id: png.hpp 21886 2011-01-22 09:53:15Z rubidium $ */

/*
 * This file is part of OpenCoaster Tycoon.
 * OpenCoaster Tycoon is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenCoaster Tycoon is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenCoaster Tycoon. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file png.hpp Base for reading files from PNG. */

#ifndef SPRITELOADER_PNG_HPP
#define SPRITELOADER_PNG_HPP

#include "spriteloader.hpp"

/** Sprite loader for graphics coming from a PNG image. */
class SpriteLoaderPNG : public SpriteLoader {
public:
	bool LoadSprite(SpriteLoader::Sprite *sprite, uint8 file_slot, size_t file_pos, SpriteType sprite_type);
};

#endif /* SPRITELOADER_PNG_HPP */
