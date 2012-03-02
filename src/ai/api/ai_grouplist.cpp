/* $Id: ai_grouplist.cpp 21888 2011-01-22 10:33:16Z rubidium $ */

/*
 * This file is part of OpenCoaster Tycoon.
 * OpenCoaster Tycoon is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenCoaster Tycoon is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenCoaster Tycoon. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file ai_grouplist.cpp Implementation of AIGroupList and friends. */

#include "../../stdafx.h"
#include "ai_grouplist.hpp"
#include "../../company_func.h"
#include "../../group.h"

AIGroupList::AIGroupList()
{
	Group *g;
	FOR_ALL_GROUPS(g) {
		if (g->owner == _current_company) this->AddItem(g->index);
	}
}