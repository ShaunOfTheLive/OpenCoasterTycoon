/* $Id: mixer.h 19332 2010-03-06 11:08:31Z peter1138 $ */

/*
 * This file is part of OpenCoaster Tycoon.
 * OpenCoaster Tycoon is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenCoaster Tycoon is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenCoaster Tycoon. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file mixer.h Functions to mix sound samples. */

#ifndef MIXER_H
#define MIXER_H

struct MixerChannel;

bool MxInitialize(uint rate);
void MxMixSamples(void *buffer, uint samples);

MixerChannel *MxAllocateChannel();
void MxSetChannelRawSrc(MixerChannel *mc, int8 *mem, size_t size, uint rate, bool is16bit);
void MxSetChannelVolume(MixerChannel *mc, uint volume, float pan);
void MxActivateChannel(MixerChannel*);

#endif /* MIXER_H */
