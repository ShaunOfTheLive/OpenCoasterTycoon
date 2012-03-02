/* $Id: townname_type.h 20283 2010-08-01 19:22:34Z frosch $ */

/*
 * This file is part of OpenCoaster Tycoon.
 * OpenCoaster Tycoon is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenCoaster Tycoon is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenCoaster Tycoon. If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file townname_type.h
 * Definition of structures used for generating town names.
 */

#ifndef TOWNNAME_TYPE_H
#define TOWNNAME_TYPE_H

#include "newgrf_townname.h"

/**
 * Struct holding a parameters used to generate town name.
 * Speeds things up a bit because these values are computed only once per name generation.
 */
struct TownNameParams {
	uint32 grfid; ///< newgrf ID (0 if not used)
	uint16 type;  ///< town name style

	/**
	 * Initializes this struct from language ID
	 * @param town_name town name 'language' ID
	 */
	TownNameParams(byte town_name)
	{
		extern int _nb_orig_names;
		bool grf = town_name >= _nb_orig_names;
		this->grfid = grf ? GetGRFTownNameId(town_name - _nb_orig_names) : 0;
		this->type = grf ? GetGRFTownNameType(town_name - _nb_orig_names) : SPECSTR_TOWNNAME_START + town_name;
	}

	TownNameParams(const struct Town *t);
};

#endif /* TOWNNAME_TYPE_H */
