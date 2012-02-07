/* $Id: ai_log.hpp 20288 2010-08-01 20:41:46Z yexo $ */

/*
 * This file is part of OpenCoaster Tycoon.
 * OpenCoaster Tycoon is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenCoaster Tycoon is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenCoaster Tycoon. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file ai_log.hpp Everything to handle and issue log messages. */

#ifndef AI_LOG_HPP
#define AI_LOG_HPP

#include "ai_object.hpp"

/**
 * Class that handles all log related functions.
 */
class AILog : public AIObject {
	/* AIController needs access to Enum and Log, in order to keep the flow from
	 *  OpenTTD core to NoAI API clear and simple. */
	friend class AIController;

public:
	/** Get the name of this class to identify it towards squirrel. */
	static const char *GetClassName() { return "AILog"; }

#ifndef EXPORT_SKIP
	/**
	 * Log levels; The value is also feed to DEBUG() lvl.
	 *  This has no use for you, as AI writer.
	 */
	enum AILogType {
		LOG_SQ_ERROR = 0, ///< Squirrel printed an error.
		LOG_ERROR = 1,    ///< User printed an error.
		LOG_SQ_INFO = 2,  ///< Squirrel printed some info.
		LOG_WARNING = 3,  ///< User printed some warning.
		LOG_INFO = 4,     ///< User printed some info.
	};

	/**
	 * Internal representation of the log-data inside the AI.
	 *  This has no use for you, as AI writer.
	 */
	struct LogData {
		char **lines;           ///< The log-lines.
		AILog::AILogType *type; ///< Per line, which type of log it was.
		int count;              ///< Total amount of log-lines possible.
		int pos;                ///< Current position in lines.
		int used;               ///< Total amount of used log-lines.
	};
#endif /* EXPORT_SKIP */

	/**
	 * Print an Info message to the logs.
	 * @param message The message to log.
	 */
	static void Info(const char *message);

	/**
	 * Print a Warning message to the logs.
	 * @param message The message to log.
	 */
	static void Warning(const char *message);

	/**
	 * Print an Error message to the logs.
	 * @param message The message to log.
	 */
	static void Error(const char *message);

#ifndef EXPORT_SKIP
	/**
	 * Free the log pointer.
	 * @note DO NOT CALL YOURSELF; leave it to the internal AI programming.
	 */
	static void FreeLogPointer();
#endif /* EXPORT_SKIP */

private:
	/**
	 * Internal command to log the message in a common way.
	 */
	static void Log(AILog::AILogType level, const char *message);
};

#endif /* AI_LOG_HPP */
