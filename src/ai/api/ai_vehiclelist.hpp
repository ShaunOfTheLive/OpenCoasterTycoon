/* $Id: ai_vehiclelist.hpp 20563 2010-08-19 15:37:28Z yexo $ */

/*
 * This file is part of OpenTTD.
 * OpenTTD is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenTTD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenTTD. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file ai_vehiclelist.hpp List all the vehicles (you own). */

#ifndef AI_VEHICLELIST_HPP
#define AI_VEHICLELIST_HPP

#include "ai_list.hpp"
#include "ai_vehicle.hpp"

/**
 * Creates a list of vehicles of which you are the owner.
 * @ingroup AIList
 */
class AIVehicleList : public AIList {
public:
	/** Get the name of this class to identify it towards squirrel. */
	static const char *GetClassName() { return "AIVehicleList"; }
	AIVehicleList();
};

/**
 * Creates a list of vehicles that have orders to a given station.
 * @ingroup AIList
 */
class AIVehicleList_Station : public AIList {
public:
	/** Get the name of this class to identify it towards squirrel. */
	static const char *GetClassName() { return "AIVehicleList_Station"; }

	/**
	 * @param station_id The station to get the list of vehicles from, which have orders to it.
	 * @pre AIBaseStation::IsValidBaseStation(station_id)
	 */
	AIVehicleList_Station(StationID station_id);
};

/**
 * Creates a list of vehicles that have orders to a given depot.
 * The list is created with a tile. If the tile is part of an airport all
 * aircraft having a depot order on a hangar of that airport will be
 * returned. For all other vehicle types the tile has to be a depot or
 * an empty list will be returned.
 * @ingroup AIList
 */
class AIVehicleList_Depot : public AIList {
public:
	/** Get the name of this class to identify it towards squirrel. */
	static const char *GetClassName() { return "AIVehicleList_Depot"; }

	/**
	 * @param tile The tile of the depot to get the list of vehicles from, which have orders to it.
	 */
	AIVehicleList_Depot(TileIndex tile);
};

/**
 * Creates a list of vehicles that share orders.
 * @ingroup AIList
 */
class AIVehicleList_SharedOrders : public AIList {
public:
	/** Get the name of this class to identify it towards squirrel. */
	static const char *GetClassName() { return "AIVehicleList_SharedOrders"; }

	/**
	 * @param vehicle_id The vehicle that the rest shared orders with.
	 */
	AIVehicleList_SharedOrders(VehicleID vehicle_id);
};

/**
 * Creates a list of vehicles that are in a group.
 * @ingroup AIList
 */
class AIVehicleList_Group : public AIList {
public:
	/** Get the name of this class to identify it towards squirrel. */
	static const char *GetClassName() { return "AIVehicleList_Group"; }

	/**
	 * @param group_id The ID of the group the vehicles are in.
	 */
	AIVehicleList_Group(GroupID group_id);
};

/**
 * Creates a list of vehicles that are in the default group.
 * @ingroup AIList
 */
class AIVehicleList_DefaultGroup : public AIList {
public:
	/** Get the name of this class to identify it towards squirrel. */
	static const char *GetClassName() { return "AIVehicleList_DefaultGroup"; }

	/**
	 * @param vehicle_type The VehicleType to get the list of vehicles for.
	 */
	AIVehicleList_DefaultGroup(AIVehicle::VehicleType vehicle_type);
};

#endif /* AI_VEHICLELIST_HPP */
