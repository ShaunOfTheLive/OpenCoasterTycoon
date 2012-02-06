/* $Id: tcp_admin.cpp 23052 2011-10-22 20:54:23Z rubidium $ */

/*
 * This file is part of OpenTTD.
 * OpenTTD is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenTTD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenTTD. If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file tcp_admin.cpp Basic functions to receive and send TCP packets to and from the admin network.
 */

#ifdef ENABLE_NETWORK

#include "../../stdafx.h"

#include "../network_internal.h"
#include "tcp_admin.h"
#include "../../debug.h"

/* Make sure that these enums match. */
assert_compile((int)CRR_MANUAL    == (int)ADMIN_CRR_MANUAL);
assert_compile((int)CRR_AUTOCLEAN == (int)ADMIN_CRR_AUTOCLEAN);
assert_compile((int)CRR_BANKRUPT  == (int)ADMIN_CRR_BANKRUPT);
assert_compile((int)CRR_END       == (int)ADMIN_CRR_END);

NetworkAdminSocketHandler::NetworkAdminSocketHandler(SOCKET s)
{
	this->sock = s;
}

NetworkAdminSocketHandler::~NetworkAdminSocketHandler()
{
}

NetworkRecvStatus NetworkAdminSocketHandler::CloseConnection(bool error)
{
	delete this;
	return NETWORK_RECV_STATUS_CONN_LOST;
}

/**
 * Defines a simple (switch) case for each network packet.
 * @param type the packet type to create the case for.
 */
#define ADMIN_COMMAND(type) case type: return this->NetworkPacketReceive_ ## type ## _command(p); break;

/**
 * Handle the given packet, i.e. pass it to the right parser receive command.
 * @param p the packet to handle.
 * @return #NetworkRecvStatus of handling.
 */
NetworkRecvStatus NetworkAdminSocketHandler::HandlePacket(Packet *p)
{
	PacketAdminType type = (PacketAdminType)p->Recv_uint8();

	switch (this->HasClientQuit() ? INVALID_ADMIN_PACKET : type) {
		ADMIN_COMMAND(ADMIN_PACKET_ADMIN_JOIN)
		ADMIN_COMMAND(ADMIN_PACKET_ADMIN_QUIT)
		ADMIN_COMMAND(ADMIN_PACKET_ADMIN_UPDATE_FREQUENCY)
		ADMIN_COMMAND(ADMIN_PACKET_ADMIN_POLL)
		ADMIN_COMMAND(ADMIN_PACKET_ADMIN_CHAT)
		ADMIN_COMMAND(ADMIN_PACKET_ADMIN_RCON)

		ADMIN_COMMAND(ADMIN_PACKET_SERVER_FULL)
		ADMIN_COMMAND(ADMIN_PACKET_SERVER_BANNED)
		ADMIN_COMMAND(ADMIN_PACKET_SERVER_ERROR)
		ADMIN_COMMAND(ADMIN_PACKET_SERVER_PROTOCOL)
		ADMIN_COMMAND(ADMIN_PACKET_SERVER_WELCOME)
		ADMIN_COMMAND(ADMIN_PACKET_SERVER_NEWGAME)
		ADMIN_COMMAND(ADMIN_PACKET_SERVER_SHUTDOWN)

		ADMIN_COMMAND(ADMIN_PACKET_SERVER_DATE)
		ADMIN_COMMAND(ADMIN_PACKET_SERVER_CLIENT_JOIN)
		ADMIN_COMMAND(ADMIN_PACKET_SERVER_CLIENT_INFO)
		ADMIN_COMMAND(ADMIN_PACKET_SERVER_CLIENT_UPDATE)
		ADMIN_COMMAND(ADMIN_PACKET_SERVER_CLIENT_QUIT)
		ADMIN_COMMAND(ADMIN_PACKET_SERVER_CLIENT_ERROR)
		ADMIN_COMMAND(ADMIN_PACKET_SERVER_COMPANY_NEW)
		ADMIN_COMMAND(ADMIN_PACKET_SERVER_COMPANY_INFO)
		ADMIN_COMMAND(ADMIN_PACKET_SERVER_COMPANY_UPDATE)
		ADMIN_COMMAND(ADMIN_PACKET_SERVER_COMPANY_REMOVE)
		ADMIN_COMMAND(ADMIN_PACKET_SERVER_COMPANY_ECONOMY)
		ADMIN_COMMAND(ADMIN_PACKET_SERVER_COMPANY_STATS)
		ADMIN_COMMAND(ADMIN_PACKET_SERVER_CHAT)
		ADMIN_COMMAND(ADMIN_PACKET_SERVER_RCON)
		ADMIN_COMMAND(ADMIN_PACKET_SERVER_CONSOLE)
		ADMIN_COMMAND(ADMIN_PACKET_SERVER_CMD_NAMES)
		ADMIN_COMMAND(ADMIN_PACKET_SERVER_CMD_LOGGING)

		default:
			if (this->HasClientQuit()) {
				DEBUG(net, 0, "[tcp/admin] received invalid packet type %d from '%s' (%s)", type, this->admin_name, this->admin_version);
			} else {
				DEBUG(net, 0, "[tcp/admin] received illegal packet from '%s' (%s)", this->admin_name, this->admin_version);
			}

			this->CloseConnection();
			return NETWORK_RECV_STATUS_MALFORMED_PACKET;
	}
}

/**
 * Do the actual receiving of packets.
 * As long as HandlePacket returns OKAY packets are handled. Upon
 * failure, or no more packets to process the last result of
 * HandlePacket is returned.
 * @return #NetworkRecvStatus of the last handled packet.
 */
NetworkRecvStatus NetworkAdminSocketHandler::ReceivePackets()
{
	Packet *p;
	while ((p = this->ReceivePacket()) != NULL) {
		NetworkRecvStatus res = this->HandlePacket(p);
		if (res != NETWORK_RECV_STATUS_OKAY) return res;
	}

	return NETWORK_RECV_STATUS_OKAY;
}

/**
 * Create stub implementations for all receive commands that only
 * show a warning that the given command is not available for the
 * socket where the packet came from.
 * @param type the packet type to create the stub for.
 */
#define DEFINE_UNAVAILABLE_ADMIN_RECEIVE_COMMAND(type) \
NetworkRecvStatus NetworkAdminSocketHandler::NetworkPacketReceive_## type ##_command(Packet *p) \
{ \
	DEBUG(net, 0, "[tcp/admin] received illegal packet type %d from admin %s (%s)", \
			type, this->admin_name, this->admin_version); \
	return NETWORK_RECV_STATUS_MALFORMED_PACKET; \
}

DEFINE_UNAVAILABLE_ADMIN_RECEIVE_COMMAND(ADMIN_PACKET_ADMIN_JOIN)
DEFINE_UNAVAILABLE_ADMIN_RECEIVE_COMMAND(ADMIN_PACKET_ADMIN_QUIT)
DEFINE_UNAVAILABLE_ADMIN_RECEIVE_COMMAND(ADMIN_PACKET_ADMIN_UPDATE_FREQUENCY)
DEFINE_UNAVAILABLE_ADMIN_RECEIVE_COMMAND(ADMIN_PACKET_ADMIN_POLL)
DEFINE_UNAVAILABLE_ADMIN_RECEIVE_COMMAND(ADMIN_PACKET_ADMIN_CHAT)
DEFINE_UNAVAILABLE_ADMIN_RECEIVE_COMMAND(ADMIN_PACKET_ADMIN_RCON)

DEFINE_UNAVAILABLE_ADMIN_RECEIVE_COMMAND(ADMIN_PACKET_SERVER_FULL)
DEFINE_UNAVAILABLE_ADMIN_RECEIVE_COMMAND(ADMIN_PACKET_SERVER_BANNED)
DEFINE_UNAVAILABLE_ADMIN_RECEIVE_COMMAND(ADMIN_PACKET_SERVER_ERROR)
DEFINE_UNAVAILABLE_ADMIN_RECEIVE_COMMAND(ADMIN_PACKET_SERVER_PROTOCOL)
DEFINE_UNAVAILABLE_ADMIN_RECEIVE_COMMAND(ADMIN_PACKET_SERVER_WELCOME)
DEFINE_UNAVAILABLE_ADMIN_RECEIVE_COMMAND(ADMIN_PACKET_SERVER_NEWGAME)
DEFINE_UNAVAILABLE_ADMIN_RECEIVE_COMMAND(ADMIN_PACKET_SERVER_SHUTDOWN)

DEFINE_UNAVAILABLE_ADMIN_RECEIVE_COMMAND(ADMIN_PACKET_SERVER_DATE)
DEFINE_UNAVAILABLE_ADMIN_RECEIVE_COMMAND(ADMIN_PACKET_SERVER_CLIENT_JOIN)
DEFINE_UNAVAILABLE_ADMIN_RECEIVE_COMMAND(ADMIN_PACKET_SERVER_CLIENT_INFO)
DEFINE_UNAVAILABLE_ADMIN_RECEIVE_COMMAND(ADMIN_PACKET_SERVER_CLIENT_UPDATE)
DEFINE_UNAVAILABLE_ADMIN_RECEIVE_COMMAND(ADMIN_PACKET_SERVER_CLIENT_QUIT)
DEFINE_UNAVAILABLE_ADMIN_RECEIVE_COMMAND(ADMIN_PACKET_SERVER_CLIENT_ERROR)
DEFINE_UNAVAILABLE_ADMIN_RECEIVE_COMMAND(ADMIN_PACKET_SERVER_COMPANY_NEW)
DEFINE_UNAVAILABLE_ADMIN_RECEIVE_COMMAND(ADMIN_PACKET_SERVER_COMPANY_INFO)
DEFINE_UNAVAILABLE_ADMIN_RECEIVE_COMMAND(ADMIN_PACKET_SERVER_COMPANY_UPDATE)
DEFINE_UNAVAILABLE_ADMIN_RECEIVE_COMMAND(ADMIN_PACKET_SERVER_COMPANY_REMOVE)
DEFINE_UNAVAILABLE_ADMIN_RECEIVE_COMMAND(ADMIN_PACKET_SERVER_COMPANY_ECONOMY)
DEFINE_UNAVAILABLE_ADMIN_RECEIVE_COMMAND(ADMIN_PACKET_SERVER_COMPANY_STATS)
DEFINE_UNAVAILABLE_ADMIN_RECEIVE_COMMAND(ADMIN_PACKET_SERVER_CHAT)
DEFINE_UNAVAILABLE_ADMIN_RECEIVE_COMMAND(ADMIN_PACKET_SERVER_RCON)
DEFINE_UNAVAILABLE_ADMIN_RECEIVE_COMMAND(ADMIN_PACKET_SERVER_CONSOLE)
DEFINE_UNAVAILABLE_ADMIN_RECEIVE_COMMAND(ADMIN_PACKET_SERVER_CMD_NAMES)
DEFINE_UNAVAILABLE_ADMIN_RECEIVE_COMMAND(ADMIN_PACKET_SERVER_CMD_LOGGING)

#endif /* ENABLE_NETWORK */
