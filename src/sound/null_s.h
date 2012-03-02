/* $Id: null_s.h 17788 2009-10-17 15:15:00Z rubidium $ */

/*
 * This file is part of OpenCoaster Tycoon.
 * OpenCoaster Tycoon is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenCoaster Tycoon is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenCoaster Tycoon. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file null_s.h Base for the sound of silence. */

#ifndef SOUND_NULL_H
#define SOUND_NULL_H

#include "sound_driver.hpp"

class SoundDriver_Null: public SoundDriver {
public:
	/* virtual */ const char *Start(const char * const *param) { return NULL; }

	/* virtual */ void Stop() { }
	/* virtual */ const char *GetName() const { return "null"; }
};

class FSoundDriver_Null: public SoundDriverFactory<FSoundDriver_Null> {
public:
	static const int priority = 1;
	/* virtual */ const char *GetName() { return "null"; }
	/* virtual */ const char *GetDescription() { return "Null Sound Driver"; }
	/* virtual */ Driver *CreateInstance() { return new SoundDriver_Null(); }
};

#endif /* SOUND_NULL_H */
