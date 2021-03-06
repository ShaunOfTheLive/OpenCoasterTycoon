/* $Id: airport_sl.cpp 20450 2010-08-11 19:09:26Z rubidium $ */

/*
 * This file is part of OpenCoaster Tycoon.
 * OpenCoaster Tycoon is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenCoaster Tycoon is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenCoaster Tycoon. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file airport_sl.cpp Code handling saving and loading airport ids */

#include "../stdafx.h"

#include "saveload.h"
#include "newgrf_sl.h"

static void Save_APID()
{
	Save_NewGRFMapping(_airport_mngr);
}

static void Load_APID()
{
	Load_NewGRFMapping(_airport_mngr);
}

static void Save_ATID()
{
	Save_NewGRFMapping(_airporttile_mngr);
}

static void Load_ATID()
{
	Load_NewGRFMapping(_airporttile_mngr);
}

extern const ChunkHandler _airport_chunk_handlers[] = {
	{ 'ATID', Save_ATID, Load_ATID, NULL, NULL, CH_ARRAY },
	{ 'APID', Save_APID, Load_APID, NULL, NULL, CH_ARRAY | CH_LAST },
};
