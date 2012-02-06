/* $Id: ai_signlist.hpp 20563 2010-08-19 15:37:28Z yexo $ */

/*
 * This file is part of OpenTTD.
 * OpenTTD is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenTTD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenTTD. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file ai_signlist.hpp List all the signs of your company. */

#ifndef AI_SIGNLIST_HPP
#define AI_SIGNLIST_HPP

#include "ai_list.hpp"

/**
 * Create a list of signs your company has created.
 * @ingroup AIList
 */
class AISignList : public AIList {
public:
	/** Get the name of this class to identify it towards squirrel. */
	static const char *GetClassName() { return "AISignList"; }
	AISignList();
};

#endif /* AI_SIGNLIST_HPP */
