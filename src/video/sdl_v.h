/* $Id: sdl_v.h 17428 2009-09-05 21:26:51Z rubidium $ */

/*
 * This file is part of OpenCoaster Tycoon.
 * OpenCoaster Tycoon is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenCoaster Tycoon is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenCoaster Tycoon. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file sdl_v.h Base of the SDL video driver. */

#ifndef VIDEO_SDL_H
#define VIDEO_SDL_H

#include "video_driver.hpp"

class VideoDriver_SDL: public VideoDriver {
public:
	/* virtual */ const char *Start(const char * const *param);

	/* virtual */ void Stop();

	/* virtual */ void MakeDirty(int left, int top, int width, int height);

	/* virtual */ void MainLoop();

	/* virtual */ bool ChangeResolution(int w, int h);

	/* virtual */ bool ToggleFullscreen(bool fullscreen);
	/* virtual */ const char *GetName() const { return "sdl"; }
};

class FVideoDriver_SDL: public VideoDriverFactory<FVideoDriver_SDL> {
public:
	static const int priority = 5;
	/* virtual */ const char *GetName() { return "sdl"; }
	/* virtual */ const char *GetDescription() { return "SDL Video Driver"; }
	/* virtual */ Driver *CreateInstance() { return new VideoDriver_SDL(); }
};

#endif /* VIDEO_SDL_H */
