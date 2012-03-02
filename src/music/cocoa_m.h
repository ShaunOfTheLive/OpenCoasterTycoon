/* $Id: cocoa_m.h 17710 2009-10-04 21:24:09Z michi_cc $ */

/*
 * This file is part of OpenCoaster Tycoon.
 * OpenCoaster Tycoon is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenCoaster Tycoon is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenCoaster Tycoon. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file cocoa_m.h Base of music playback via CoreAudio. */

#ifndef MUSIC_MACOSX_COCOA_H
#define MUSIC_MACOSX_COCOA_H

#include "music_driver.hpp"

class MusicDriver_Cocoa: public MusicDriver {
public:
	/* virtual */ const char *Start(const char * const *param);

	/* virtual */ void Stop();

	/* virtual */ void PlaySong(const char *filename);

	/* virtual */ void StopSong();

	/* virtual */ bool IsSongPlaying();

	/* virtual */ void SetVolume(byte vol);
	/* virtual */ const char *GetName() const { return "cocoa"; }
};

class FMusicDriver_Cocoa: public MusicDriverFactory<FMusicDriver_Cocoa> {
public:
	static const int priority = 10;
	/* virtual */ const char *GetName() { return "cocoa"; }
	/* virtual */ const char *GetDescription() { return "Cocoa MIDI Driver"; }
	/* virtual */ Driver *CreateInstance() { return new MusicDriver_Cocoa(); }
};

#endif /* MUSIC_MACOSX_COCOA_H */
