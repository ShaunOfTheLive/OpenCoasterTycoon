/* $Id: rail_gui.h 21867 2011-01-20 12:40:04Z rubidium $ */

/*
 * This file is part of OpenCoaster Tycoon.
 * OpenCoaster Tycoon is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenCoaster Tycoon is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenCoaster Tycoon. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file rail_gui.h Functions/types etc. related to the rail GUI. */

#ifndef RAIL_GUI_H
#define RAIL_GUI_H

#include "rail_type.h"
#include "widgets/dropdown_type.h"

struct Window *ShowBuildRailToolbar(RailType railtype);
void ReinitGuiAfterToggleElrail(bool disable);
bool ResetSignalVariant(int32 = 0);
void InitializeRailGUI();
DropDownList *GetRailTypeDropDownList(bool for_replacement = false);

#endif /* RAIL_GUI_H */
