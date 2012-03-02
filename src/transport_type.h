/* $Id: transport_type.h 20632 2010-08-26 22:01:16Z rubidium $ */

/*
 * This file is part of OpenCoaster Tycoon.
 * OpenCoaster Tycoon is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenCoaster Tycoon is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenCoaster Tycoon. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file transport_type.h Base types related to transport. */

#ifndef TRANSPORT_TYPE_H
#define TRANSPORT_TYPE_H

#include "core/enum_type.hpp"

typedef uint16 UnitID;

/** Available types of transport */
enum TransportType {
	/* These constants are for now linked to the representation of bridges
	 * and tunnels, so they can be used by GetTileTrackStatus_TunnelBridge.
	 * In an ideal world, these constants would be used everywhere when
	 * accessing tunnels and bridges. For now, you should just not change
	 * the values for road and rail.
	 */
	TRANSPORT_BEGIN = 0,
	TRANSPORT_RAIL = TRANSPORT_BEGIN, ///< Transport by train
	TRANSPORT_ROAD,  ///< Transport by road vehicle
	TRANSPORT_WATER, ///< Transport over water
	TRANSPORT_AIR,   ///< Transport through air
	TRANSPORT_END,
	INVALID_TRANSPORT = 0xff,
};
template <> struct EnumPropsT<TransportType> : MakeEnumPropsT<TransportType, byte, TRANSPORT_BEGIN, TRANSPORT_END, INVALID_TRANSPORT, 2> {};

#endif /* TRANSPORT_TYPE_H */