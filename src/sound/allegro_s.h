/* $Id: allegro_s.h 17788 2009-10-17 15:15:00Z rubidium $ */

/*
 * This file is part of OpenTTD.
 * OpenTTD is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenTTD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenTTD. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file allegro_s.h Base fo playing sound via Allegro. */

#ifndef SOUND_ALLEGRO_H
#define SOUND_ALLEGRO_H

#include "sound_driver.hpp"

class SoundDriver_Allegro: public SoundDriver {
public:
	/* virtual */ const char *Start(const char * const *param);

	/* virtual */ void Stop();

	/* virtual */ void MainLoop();
	/* virtual */ const char *GetName() const { return "allegro"; }
};

class FSoundDriver_Allegro: public SoundDriverFactory<FSoundDriver_Allegro> {
public:
	static const int priority = 4;
	/* virtual */ const char *GetName() { return "allegro"; }
	/* virtual */ const char *GetDescription() { return "Allegro Sound Driver"; }
	/* virtual */ Driver *CreateInstance() { return new SoundDriver_Allegro(); }
};

#endif /* SOUND_ALLEGRO_H */
