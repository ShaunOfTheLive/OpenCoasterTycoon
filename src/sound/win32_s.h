/* $Id: win32_s.h 17428 2009-09-05 21:26:51Z rubidium $ */

/*
 * This file is part of OpenTTD.
 * OpenTTD is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenTTD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenTTD. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file win32_s.h Base for Windows sound handling. */

#ifndef SOUND_WIN32_H
#define SOUND_WIN32_H

#include "sound_driver.hpp"

class SoundDriver_Win32: public SoundDriver {
public:
	/* virtual */ const char *Start(const char * const *param);

	/* virtual */ void Stop();
	/* virtual */ const char *GetName() const { return "win32"; }
};

class FSoundDriver_Win32: public SoundDriverFactory<FSoundDriver_Win32> {
public:
	static const int priority = 10;
	/* virtual */ const char *GetName() { return "win32"; }
	/* virtual */ const char *GetDescription() { return "Win32 WaveOut Driver"; }
	/* virtual */ Driver *CreateInstance() { return new SoundDriver_Win32(); }
};

#endif /* SOUND_WIN32_H */
