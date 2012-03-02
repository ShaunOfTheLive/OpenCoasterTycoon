/* $Id: cocoa_s.h 17428 2009-09-05 21:26:51Z rubidium $ */

/*
 * This file is part of OpenCoaster Tycoon.
 * OpenCoaster Tycoon is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenCoaster Tycoon is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenCoaster Tycoon. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file cocoa_s.h Base for Cocoa sound handling. */

#ifndef SOUND_COCOA_H
#define SOUND_COCOA_H

#include "sound_driver.hpp"

class SoundDriver_Cocoa: public SoundDriver {
public:
	/* virtual */ const char *Start(const char * const *param);

	/* virtual */ void Stop();
	/* virtual */ const char *GetName() const { return "cocoa"; }
};

class FSoundDriver_Cocoa: public SoundDriverFactory<FSoundDriver_Cocoa> {
public:
	static const int priority = 10;
	/* virtual */ const char *GetName() { return "cocoa"; }
	/* virtual */ const char *GetDescription() { return "Cocoa Sound Driver"; }
	/* virtual */ Driver *CreateInstance() { return new SoundDriver_Cocoa(); }
};

#endif /* SOUND_COCOA_H */
