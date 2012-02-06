/* $Id: macos.h 22992 2011-10-04 20:12:02Z rubidium $ */

/*
 * This file is part of OpenTTD.
 * OpenTTD is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenTTD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenTTD. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file macos.h Functions related to MacOS support. */

#ifndef MACOS_H
#define MACOS_H

/* It would seem that to ensure backward compability we have to ensure that we have defined MAC_OS_X_VERSION_10_x everywhere */
#ifndef MAC_OS_X_VERSION_10_3
#define MAC_OS_X_VERSION_10_3 1030
#endif

#ifndef MAC_OS_X_VERSION_10_4
#define MAC_OS_X_VERSION_10_4 1040
#endif

#ifndef MAC_OS_X_VERSION_10_5
#define MAC_OS_X_VERSION_10_5 1050
#endif

#ifndef MAC_OS_X_VERSION_10_6
#define MAC_OS_X_VERSION_10_6 1060
#endif

#ifndef MAC_OS_X_VERSION_10_7
#define MAC_OS_X_VERSION_10_7 1070
#endif

#ifndef MAC_OS_X_VERSION_10_8
#define MAC_OS_X_VERSION_10_8 1080
#endif


/** Helper function displaying a message the best possible way. */
void ShowMacDialog(const char *title, const char *message, const char *button_label);

void GetMacOSVersion(int *return_major, int *return_minor, int *return_bugfix);

/**
 * Check if we are at least running on the specified version of Mac OS.
 * @param major major version of the os. This would be 10 in the case of 10.4.11.
 * @param minor minor version of the os. This would be 4 in the case of 10.4.11.
 * @param bugfix bugfix version of the os. This would be 11 in the case of 10.4.11.
 * @return true if the running os is at least what we asked, false otherwise.
 */
static inline bool MacOSVersionIsAtLeast(long major, long minor, long bugfix)
{
	int version_major, version_minor, version_bugfix;
	GetMacOSVersion(&version_major, &version_minor, &version_bugfix);

	if (version_major < major) return false;
	if (version_major == major && version_minor < minor) return false;
	if (version_major == major && version_minor == minor && version_bugfix < bugfix) return false;

	return true;
}

#endif /* MACOS_H */
