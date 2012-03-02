/* $Id: ai_industrylist.cpp 21888 2011-01-22 10:33:16Z rubidium $ */

/*
 * This file is part of OpenCoaster Tycoon.
 * OpenCoaster Tycoon is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenCoaster Tycoon is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenCoaster Tycoon. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file ai_industrylist.cpp Implementation of AIIndustryList and friends. */

#include "../../stdafx.h"
#include "ai_industrylist.hpp"
#include "../../industry.h"

AIIndustryList::AIIndustryList()
{
	Industry *i;
	FOR_ALL_INDUSTRIES(i) {
		this->AddItem(i->index);
	}
}

AIIndustryList_CargoAccepting::AIIndustryList_CargoAccepting(CargoID cargo_id)
{
	const Industry *i;

	FOR_ALL_INDUSTRIES(i) {
		for (byte j = 0; j < lengthof(i->accepts_cargo); j++) {
			if (i->accepts_cargo[j] == cargo_id) this->AddItem(i->index);
		}
	}
}

AIIndustryList_CargoProducing::AIIndustryList_CargoProducing(CargoID cargo_id)
{
	const Industry *i;

	FOR_ALL_INDUSTRIES(i) {
		for (byte j = 0; j < lengthof(i->produced_cargo); j++) {
			if (i->produced_cargo[j] == cargo_id) this->AddItem(i->index);
		}
	}
}
