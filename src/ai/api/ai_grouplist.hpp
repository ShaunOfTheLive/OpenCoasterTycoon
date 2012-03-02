/* $Id: ai_grouplist.hpp 20563 2010-08-19 15:37:28Z yexo $ */

/*
 * This file is part of OpenCoaster Tycoon.
 * OpenCoaster Tycoon is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenCoaster Tycoon is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenCoaster Tycoon. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file ai_grouplist.hpp List all the groups (you own). */

#ifndef AI_GROUPLIST_HPP
#define AI_GROUPLIST_HPP

#include "ai_list.hpp"

/**
 * Creates a list of groups of which you are the owner.
 * @note Neither AIGroup::GROUP_ALL nor AIGroup::GROUP_DEFAULT is in this list.
 * @ingroup AIList
 */
class AIGroupList : public AIList {
public:
	/** Get the name of this class to identify it towards squirrel. */
	static const char *GetClassName() { return "AIGroupList"; }
	AIGroupList();
};

#endif /* AI_GROUPLIST_HPP */
