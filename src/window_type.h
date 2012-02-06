/* $Id: window_type.h 22650 2011-07-10 20:17:56Z rubidium $ */

/*
 * This file is part of OpenTTD.
 * OpenTTD is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenTTD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenTTD. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file window_type.h Types related to windows */

#ifndef WINDOW_TYPE_H
#define WINDOW_TYPE_H


/**
 * Window classes
 */
enum WindowClass {
	WC_NONE,
	WC_MAIN_WINDOW = WC_NONE,
	WC_MAIN_TOOLBAR,
	WC_STATUS_BAR,
	WC_BUILD_TOOLBAR,
	WC_NEWS_WINDOW,
	WC_TOWN_DIRECTORY,
	WC_STATION_LIST,
	WC_TOWN_VIEW,
	WC_FOUND_TOWN,
	WC_SMALLMAP,
	WC_TRAINS_LIST,
	WC_ROADVEH_LIST,
	WC_SHIPS_LIST,
	WC_AIRCRAFT_LIST,
	WC_VEHICLE_VIEW,
	WC_VEHICLE_DETAILS,
	WC_VEHICLE_REFIT,
	WC_VEHICLE_ORDERS,
	WC_STATION_VIEW,
	WC_VEHICLE_DEPOT,
	WC_BUILD_VEHICLE,
	WC_BUILD_BRIDGE,
	WC_ERRMSG,
	WC_BUILD_STATION,
	WC_BUS_STATION,
	WC_TRUCK_STATION,
	WC_BUILD_DEPOT,
	WC_COMPANY,
	WC_FINANCES,
	WC_COMPANY_COLOUR,
	WC_QUERY_STRING,
	WC_SAVELOAD,
	WC_SELECT_GAME,
	WC_CLIENT_LIST_POPUP,
	WC_INCOME_GRAPH,
	WC_OPERATING_PROFIT,
	WC_TOOLTIPS,
	WC_INDUSTRY_VIEW,
	WC_COMPANY_MANAGER_FACE,
	WC_LAND_INFO,
	WC_TOWN_AUTHORITY,
	WC_SUBSIDIES_LIST,
	WC_GRAPH_LEGEND,
	WC_DELIVERED_CARGO,
	WC_PERFORMANCE_HISTORY,
	WC_COMPANY_VALUE,
	WC_COMPANY_LEAGUE,
	WC_BUY_COMPANY,
	WC_PAYMENT_RATES,
	WC_ENGINE_PREVIEW,
	WC_MUSIC_WINDOW,
	WC_MUSIC_TRACK_SELECTION,
	WC_SCEN_LAND_GEN,
	WC_SCEN_INDUSTRY,
	WC_SCEN_BUILD_TOOLBAR,
	WC_BUILD_TREES,
	WC_SEND_NETWORK_MSG,
	WC_DROPDOWN_MENU,
	WC_BUILD_INDUSTRY,
	WC_GAME_OPTIONS,
	WC_NETWORK_WINDOW,
	WC_INDUSTRY_DIRECTORY,
	WC_MESSAGE_HISTORY,
	WC_CHEATS,
	WC_PERFORMANCE_DETAIL,
	WC_CONSOLE,
	WC_EXTRA_VIEW_PORT,
	WC_CLIENT_LIST,
	WC_NETWORK_STATUS_WINDOW,
	WC_CUSTOM_CURRENCY,
	WC_REPLACE_VEHICLE,
	WC_HIGHSCORE,
	WC_ENDSCREEN,
	WC_SIGN_LIST,
	WC_GENERATE_LANDSCAPE,
	WC_GENERATE_PROGRESS_WINDOW,
	WC_CONFIRM_POPUP_QUERY,
	WC_TRANSPARENCY_TOOLBAR,
	WC_VEHICLE_TIMETABLE,
	WC_BUILD_SIGNAL,
	WC_COMPANY_PASSWORD_WINDOW,
	WC_OSK,
	WC_WAYPOINT_VIEW,
	WC_SELECT_STATION,
	WC_SET_DATE,
	WC_AI_DEBUG,
	WC_AI_LIST,
	WC_AI_SETTINGS,
	WC_NEWGRF_INSPECT,
	WC_SPRITE_ALIGNER,
	WC_INDUSTRY_CARGOES,
	WC_GRF_PARAMETERS,
	WC_BUILD_OBJECT,

	WC_INVALID = 0xFFFF
};

/**
 * Data value for #Window::OnInvalidateData() of windows with class #WC_GAME_OPTIONS.
 */
enum GameOptionsInvalidationData {
	GOID_DEFAULT = 0,
	GOID_NEWGRF_RESCANNED,     ///< NewGRFs were just rescanned.
	GOID_NEWGRF_LIST_EDITED,   ///< List of active NewGRFs is being edited.
	GOID_NEWGRF_PRESET_LOADED, ///< A NewGRF preset was picked.
	GOID_DIFFICULTY_CHANGED,   ///< Difficulty settings were changed.
};

struct Window;

/** Number to differentiate different windows of the same class */
typedef int32 WindowNumber;

#endif /* WINDOW_TYPE_H */
