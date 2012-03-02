/* $Id: dedicated.cpp 20194 2010-07-19 17:46:53Z rubidium $ */

/*
 * This file is part of OpenCoaster Tycoon.
 * OpenCoaster Tycoon is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenCoaster Tycoon is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenCoaster Tycoon. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file dedicated.cpp Forking support for dedicated servers. */

#include "stdafx.h"

#ifdef ENABLE_NETWORK

char *_log_file; ///< File to reroute output of a forked OpenTTD to

#if defined(UNIX) && !defined(__MORPHOS__)

#include <unistd.h>

#if (defined(SUNOS) && !defined(_LP64) && !defined(_I32LPx)) || defined(__HAIKU__)
/* Solaris has, in certain situation, pid_t defined as long, while in other
 *  cases it has it defined as int... this handles all cases nicely.
 * Haiku has also defined pid_t as a long.
 */
# define PRINTF_PID_T "%ld"
#else
# define PRINTF_PID_T "%d"
#endif

void DedicatedFork()
{
	/* Fork the program */
	pid_t pid = fork();
	switch (pid) {
		case -1:
			perror("Unable to fork");
			exit(1);

		case 0: { // We're the child
			FILE *f;

			/* Open the log-file to log all stuff too */
			f = fopen(_log_file, "a");
			if (f == NULL) {
				perror("Unable to open logfile");
				exit(1);
			}
			/* Redirect stdout and stderr to log-file */
			if (dup2(fileno(f), fileno(stdout)) == -1) {
				perror("Rerouting stdout");
				exit(1);
			}
			if (dup2(fileno(f), fileno(stderr)) == -1) {
				perror("Rerouting stderr");
				exit(1);
			}
			break;
		}

		default:
			/* We're the parent */
			printf("Loading dedicated server...\n");
			printf("  - Forked to background with pid " PRINTF_PID_T "\n", pid);
			exit(0);
	}
}
#endif

#else

/** Empty helper function call for NOT(UNIX and not MORPHOS) systems */
void DedicatedFork() {}

#endif /* ENABLE_NETWORK */
