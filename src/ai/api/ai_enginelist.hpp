/* $Id: ai_enginelist.hpp 20563 2010-08-19 15:37:28Z yexo $ */

/*
 * This file is part of OpenCoaster Tycoon.
 * OpenCoaster Tycoon is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenCoaster Tycoon is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenCoaster Tycoon. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file ai_enginelist.hpp List all the engines. */

#ifndef AI_ENGINELIST_HPP
#define AI_ENGINELIST_HPP

#include "ai_list.hpp"
#include "ai_vehicle.hpp"

/**
 * Create a list of engines based on a vehicle type.
 * @ingroup AIList
 */
class AIEngineList : public AIList {
public:
	/** Get the name of this class to identify it towards squirrel. */
	static const char *GetClassName() { return "AIEngineList"; }

	/**
	 * @param vehicle_type The type of vehicle to make a list of engines for.
	 */
	AIEngineList(AIVehicle::VehicleType vehicle_type);
};

#endif /* AI_ENGINELIST_HPP */
