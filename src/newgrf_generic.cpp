/* $Id: newgrf_generic.cpp 22885 2011-09-03 18:51:59Z frosch $ */

/*
 * This file is part of OpenCoaster Tycoon.
 * OpenCoaster Tycoon is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenCoaster Tycoon is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenCoaster Tycoon. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file newgrf_generic.cpp Handling of generic feature callbacks. */

#include "stdafx.h"
#include "debug.h"
#include "newgrf.h"
#include "newgrf_spritegroup.h"
#include "industrytype.h"
#include "core/bitmath_func.hpp"
#include <list>


struct GenericCallback {
	const GRFFile *file;
	const SpriteGroup *group;

	GenericCallback(const GRFFile *file, const SpriteGroup *group) :
		file(file),
		group(group)
	{ }
};

typedef std::list<GenericCallback> GenericCallbackList;

static GenericCallbackList _gcl[GSF_END];


/**
 * Reset all generic feature callback sprite groups.
 */
void ResetGenericCallbacks()
{
	for (uint8 feature = 0; feature < lengthof(_gcl); feature++) {
		_gcl[feature].clear();
	}
}


/**
 * Add a generic feature callback sprite group to the appropriate feature list.
 * @param feature
 * @param file
 * @param group
 */
void AddGenericCallback(uint8 feature, const GRFFile *file, const SpriteGroup *group)
{
	if (feature >= lengthof(_gcl)) {
		grfmsg(5, "AddGenericCallback: Unsupported feature 0x%02X", feature);
		return;
	}

	/* Generic feature callbacks are evaluated in reverse (i.e. the last group
	 * to be added is evaluated first, etc) thus we push the group to the
	 * beginning of the list so a standard iterator will do the right thing. */
	_gcl[feature].push_front(GenericCallback(file, group));
}


static uint32 GenericCallbackGetRandomBits(const ResolverObject *object)
{
	return 0;
}


static uint32 GenericCallbackGetTriggers(const ResolverObject *object)
{
	return 0;
}


static void GenericCallbackSetTriggers(const ResolverObject *object, int triggers)
{
	return;
}


static uint32 GenericCallbackGetVariable(const ResolverObject *object, byte variable, byte parameter, bool *available)
{
	switch (variable) {
		case 0x40: return object->grffile->cargo_map[object->u.generic.cargo_type];

		case 0x80: return object->u.generic.cargo_type;
		case 0x81: return CargoSpec::Get(object->u.generic.cargo_type)->bitnum;
		case 0x82: return object->u.generic.default_selection;
		case 0x83: return object->u.generic.src_industry;
		case 0x84: return object->u.generic.dst_industry;
		case 0x85: return object->u.generic.distance;
		case 0x86: return object->u.generic.event;
		case 0x87: return object->u.generic.count;
		case 0x88: return object->u.generic.station_size;

		default: break;
	}

	DEBUG(grf, 1, "Unhandled generic feature variable 0x%02X", variable);

	*available = false;
	return UINT_MAX;
}


static const SpriteGroup *GenericCallbackResolveReal(const ResolverObject *object, const RealSpriteGroup *group)
{
	if (group->num_loaded == 0) return NULL;

	return group->loaded[0];
}


static inline void NewGenericResolver(ResolverObject *res)
{
	res->GetRandomBits = &GenericCallbackGetRandomBits;
	res->GetTriggers   = &GenericCallbackGetTriggers;
	res->SetTriggers   = &GenericCallbackSetTriggers;
	res->GetVariable   = &GenericCallbackGetVariable;
	res->ResolveReal   = &GenericCallbackResolveReal;

	res->callback        = CBID_NO_CALLBACK;
	res->callback_param1 = 0;
	res->callback_param2 = 0;
	res->ResetState();
}


/**
 * Follow a generic feature callback list and return the first successful
 * answer
 * @param feature GRF Feature of callback
 * @param object  pre-populated resolver object
 * @param [out] file Optionally returns the GRFFile which made the final decision for the callback result.
 *                   May be NULL if not required.
 * @return callback value if successful or CALLBACK_FAILED
 */
static uint16 GetGenericCallbackResult(uint8 feature, ResolverObject *object, const GRFFile **file)
{
	assert(feature < lengthof(_gcl));

	/* Test each feature callback sprite group. */
	for (GenericCallbackList::const_iterator it = _gcl[feature].begin(); it != _gcl[feature].end(); ++it) {
		const SpriteGroup *group = it->group;
		object->grffile = it->file;
		group = SpriteGroup::Resolve(group, object);
		if (group == NULL || group->GetCallbackResult() == CALLBACK_FAILED) continue;

		/* Return NewGRF file if necessary */
		if (file != NULL) *file = it->file;

		return group->GetCallbackResult();
	}

	/* No callback returned a valid result, so we've failed. */
	return CALLBACK_FAILED;
}


/**
 * 'Execute' an AI purchase selection callback
 *
 * @param feature GRF Feature to call callback for.
 * @param cargo_type Cargotype to pass to callback. (Variable 80)
 * @param default_selection 'Default selection' to pass to callback. (Variable 82)
 * @param src_industry 'Source industry type' to pass to callback. (Variable 83)
 * @param dst_industry 'Destination industry type' to pass to callback. (Variable 84)
 * @param distance 'Distance between source and destination' to pass to callback. (Variable 85)
 * @param event 'AI construction event' to pass to callback. (Variable 86)
 * @param count 'Construction number' to pass to callback. (Variable 87)
 * @param station_size 'Station size' to pass to callback. (Variable 88)
 * @param [out] file Optionally returns the GRFFile which made the final decision for the callback result.
 *                   May be NULL if not required.
 * @return callback value if successful or CALLBACK_FAILED
 */
uint16 GetAiPurchaseCallbackResult(uint8 feature, CargoID cargo_type, uint8 default_selection, IndustryType src_industry, IndustryType dst_industry, uint8 distance, AIConstructionEvent event, uint8 count, uint8 station_size, const GRFFile **file)
{
	ResolverObject object;

	NewGenericResolver(&object);

	if (src_industry != IT_AI_UNKNOWN && src_industry != IT_AI_TOWN) {
		const IndustrySpec *is = GetIndustrySpec(src_industry);
		/* If this is no original industry, use the substitute type */
		if (is->grf_prop.subst_id != INVALID_INDUSTRYTYPE) src_industry = is->grf_prop.subst_id;
	}

	if (dst_industry != IT_AI_UNKNOWN && dst_industry != IT_AI_TOWN) {
		const IndustrySpec *is = GetIndustrySpec(dst_industry);
		/* If this is no original industry, use the substitute type */
		if (is->grf_prop.subst_id != INVALID_INDUSTRYTYPE) dst_industry = is->grf_prop.subst_id;
	}

	object.callback = CBID_GENERIC_AI_PURCHASE_SELECTION;
	object.u.generic.cargo_type        = cargo_type;
	object.u.generic.default_selection = default_selection;
	object.u.generic.src_industry      = src_industry;
	object.u.generic.dst_industry      = dst_industry;
	object.u.generic.distance          = distance;
	object.u.generic.event             = event;
	object.u.generic.count             = count;
	object.u.generic.station_size      = station_size;

	uint16 callback = GetGenericCallbackResult(feature, &object, file);
	if (callback != CALLBACK_FAILED) callback = GB(callback, 0, 8);
	return callback;
}
