/* $Id: qtmidi.h 17710 2009-10-04 21:24:09Z michi_cc $ */

/*
 * This file is part of OpenTTD.
 * OpenTTD is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenTTD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenTTD. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file qtmidi.h Base of music playback via the QuickTime driver. */

#ifndef MUSIC_MACOSX_QUICKTIME_H
#define MUSIC_MACOSX_QUICKTIME_H

#include "music_driver.hpp"

class MusicDriver_QtMidi: public MusicDriver {
public:
	/* virtual */ const char *Start(const char * const *param);

	/* virtual */ void Stop();

	/* virtual */ void PlaySong(const char *filename);

	/* virtual */ void StopSong();

	/* virtual */ bool IsSongPlaying();

	/* virtual */ void SetVolume(byte vol);
	/* virtual */ const char *GetName() const { return "qt"; }
};

class FMusicDriver_QtMidi: public MusicDriverFactory<FMusicDriver_QtMidi> {
public:
	static const int priority = 5;
	/* virtual */ const char *GetName() { return "qt"; }
	/* virtual */ const char *GetDescription() { return "QuickTime MIDI Driver"; }
	/* virtual */ Driver *CreateInstance() { return new MusicDriver_QtMidi(); }
};

#endif /* MUSIC_MACOSX_QUICKTIME_H */
