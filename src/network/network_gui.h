/* $Id: network_gui.h 18809 2010-01-15 16:41:15Z rubidium $ */

/*
 * This file is part of OpenCoaster Tycoon.
 * OpenCoaster Tycoon is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenCoaster Tycoon is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenCoaster Tycoon. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file network_gui.h GUIs related to networking. */

#ifndef NETWORK_GUI_H
#define NETWORK_GUI_H

#include "../company_type.h"
#include "../economy_type.h"
#include "../window_type.h"
#include "network_type.h"

#ifdef ENABLE_NETWORK

void ShowNetworkNeedPassword(NetworkPasswordType npt);
void ShowNetworkGiveMoneyWindow(CompanyID company);
void ShowNetworkChatQueryWindow(DestType type, int dest);
void ShowJoinStatusWindow();
void ShowNetworkGameWindow();
void ShowClientList();
void ShowNetworkCompanyPasswordWindow(Window *parent);


/** Company information stored at the client side */
struct NetworkCompanyInfo : NetworkCompanyStats {
	char company_name[NETWORK_COMPANY_NAME_LENGTH]; ///< Company name
	Year inaugurated_year;                          ///< What year the company started in
	Money company_value;                            ///< The company value
	Money money;                                    ///< The amount of money the company has
	Money income;                                   ///< How much did the company earned last year
	uint16 performance;                             ///< What was his performance last month?
	bool use_password;                              ///< Is there a password
	char clients[NETWORK_CLIENTS_LENGTH];           ///< The clients that control this company (Name1, name2, ..)
};

NetworkCompanyInfo *GetLobbyCompanyInfo(CompanyID company);

#else /* ENABLE_NETWORK */
/* Network function stubs when networking is disabled */

static inline void ShowNetworkChatQueryWindow(byte desttype, int dest) {}
static inline void ShowClientList() {}
static inline void ShowNetworkGameWindow() {}
static inline void ShowNetworkCompanyPasswordWindow(Window *parent) {}

#endif /* ENABLE_NETWORK */

#endif /* NETWORK_GUI_H */
