/* $Id: object.h 21846 2011-01-18 23:09:43Z rubidium $ */

/*
 * This file is part of OpenCoaster Tycoon.
 * OpenCoaster Tycoon is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenCoaster Tycoon is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenCoaster Tycoon. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file object.h Functions related to objects. */

#ifndef OBJECT_H
#define OBJECT_H

#include "tile_type.h"
#include "company_type.h"
#include "object_type.h"

void UpdateCompanyHQ(TileIndex tile, uint score);

void BuildObject(ObjectType type, TileIndex tile, CompanyID owner = OWNER_NONE, struct Town *town = NULL, uint8 view = 0);

void PlaceProc_Object(TileIndex tile);
void ShowBuildObjectPicker(struct Window *w);

#endif /* OBJECT_H */