/* $Id: vehiclelist.h 20772 2010-09-08 21:37:13Z rubidium $ */

/*
 * This file is part of OpenCoaster Tycoon.
 * OpenCoaster Tycoon is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenCoaster Tycoon is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenCoaster Tycoon. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file vehiclelist.h Functions and type for generating vehicle lists. */

#ifndef VEHICLELIST_H
#define VEHICLELIST_H

#include "core/smallvec_type.hpp"
#include "vehicle_type.h"
#include "company_type.h"
#include "tile_type.h"

/** Vehicle List type flags */
enum VehicleListType {
	VL_STANDARD,
	VL_SHARED_ORDERS,
	VL_STATION_LIST,
	VL_DEPOT_LIST,
	VL_GROUP_LIST,
	VLT_END
};

/** The information about a vehicle list. */
struct VehicleListIdentifier {
	VehicleListType type; ///< The type of vehicle list.
	VehicleType vtype;    ///< The vehicle type associated with this list.
	CompanyID company;    ///< The company associated with this list.
	uint32 index;         ///< A vehicle list type specific index.

	uint32 Pack();
	bool Unpack(uint32 data);

	/**
	 * Create a simple vehicle list.
	 * @param type    List type.
	 * @param vtype   Vehicle type associated with this list.
	 * @param company Company associated with this list.
	 * @param index   Optional type specific index.
	 */
	VehicleListIdentifier(VehicleListType type, VehicleType vtype, CompanyID company, uint index = 0) :
		type(type), vtype(vtype), company(company), index(index) {}

	VehicleListIdentifier(uint32 data);

	/** Simple empty constructor. In this case you must set everything! */
	VehicleListIdentifier() {}
};

typedef SmallVector<const Vehicle *, 32> VehicleList;

bool GenerateVehicleSortList(VehicleList *list, const VehicleListIdentifier &identifier);
void BuildDepotVehicleList(VehicleType type, TileIndex tile, VehicleList *engine_list, VehicleList *wagon_list, bool individual_wagons = false);

#endif /* VEHICLELIST_H */
