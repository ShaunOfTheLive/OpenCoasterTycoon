/* $Id: gamelog.h 20674 2010-08-28 20:15:45Z alberth $ */

/*
 * This file is part of OpenTTD.
 * OpenTTD is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenTTD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenTTD. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file gamelog.h Functions to be called to log possibly unsafe game events */

#ifndef GAMELOG_H
#define GAMELOG_H

#include "newgrf_config.h"

enum GamelogActionType {
	GLAT_START,        ///< Game created
	GLAT_LOAD,         ///< Game loaded
	GLAT_GRF,          ///< GRF changed
	GLAT_CHEAT,        ///< Cheat was used
	GLAT_SETTING,      ///< Setting changed
	GLAT_GRFBUG,       ///< GRF bug was triggered
	GLAT_EMERGENCY,    ///< Emergency savegame
	GLAT_END,          ///< So we know how many GLATs are there
	GLAT_NONE  = 0xFF, ///< No logging active; in savegames, end of list
};

void GamelogStartAction(GamelogActionType at);
void GamelogStopAction();

void GamelogReset();

typedef void GamelogPrintProc(const char *s);
void GamelogPrint(GamelogPrintProc *proc); // needed for WIN32 / WINCE crash.log

void GamelogPrintDebug(int level);
void GamelogPrintConsole();

void GamelogEmergency();
bool GamelogTestEmergency();

void GamelogRevision();
void GamelogMode();
void GamelogOldver();
void GamelogSetting(const char *name, int32 oldval, int32 newval);

void GamelogGRFUpdate(const GRFConfig *oldg, const GRFConfig *newg);
void GamelogGRFAddList(const GRFConfig *newg);
void GamelogGRFRemove(uint32 grfid);
void GamelogGRFAdd(const GRFConfig *newg);
void GamelogGRFCompatible(const GRFIdentifier *newg);

void GamelogTestRevision();
void GamelogTestMode();

bool GamelogGRFBugReverse(uint32 grfid, uint16 internal_id);

#endif /* GAMELOG_H */
