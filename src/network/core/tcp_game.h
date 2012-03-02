/* $Id: tcp_game.h 22461 2011-05-15 09:38:54Z rubidium $ */

/*
 * This file is part of OpenCoaster Tycoon.
 * OpenCoaster Tycoon is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenCoaster Tycoon is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenCoaster Tycoon. If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file tcp_game.h Basic functions to receive and send TCP packets for game purposes.
 */

#ifndef NETWORK_CORE_TCP_GAME_H
#define NETWORK_CORE_TCP_GAME_H

#include "os_abstraction.h"
#include "tcp.h"
#include "../network_type.h"
#include "../../core/pool_type.hpp"

#ifdef ENABLE_NETWORK

/**
 * Enum with all types of TCP packets.
 * For the exact meaning, look at #NetworkGameSocketHandler.
 */
enum PacketGameType {
	/*
	 * These first three pair of packets (thus six in
	 * total) must remain in this order for backward
	 * and forward compatability between clients that
	 * are trying to join directly.
	 */

	/* Packets sent by socket accepting code without ever constructing a client socket instance. */
	PACKET_SERVER_FULL,                  ///< The server is full and has no place for you.
	PACKET_SERVER_BANNED,                ///< The server has banned you.

	/* Packets used by the client to join and an error message when the revision is wrong. */
	PACKET_CLIENT_JOIN,                  ///< The client telling the server it wants to join.
	PACKET_SERVER_ERROR,                 ///< Server sending an error message to the client.

	/* Packets used for the pre-game lobby. */
	PACKET_CLIENT_COMPANY_INFO,          ///< Request information about all companies.
	PACKET_SERVER_COMPANY_INFO,          ///< Information about a single company.

	/*
	 * Packets after here assume that the client
	 * and server are running the same version. As
	 * such ordering is unimportant from here on.
	 *
	 * The following is the remainder of the packets
	 * sent as part of authenticating and getting
	 * the map and other important data.
	 */

	/* After the join step, the first is checking NewGRFs. */
	PACKET_SERVER_CHECK_NEWGRFS,         ///< Server sends NewGRF IDs and MD5 checksums for the client to check.
	PACKET_CLIENT_NEWGRFS_CHECKED,       ///< Client acknowledges that it has all required NewGRFs.

	/* Checking the game, and then company passwords. */
	PACKET_SERVER_NEED_GAME_PASSWORD,    ///< Server requests the (hashed) game password.
	PACKET_CLIENT_GAME_PASSWORD,         ///< Clients sends the (hashed) game password.
	PACKET_SERVER_NEED_COMPANY_PASSWORD, ///< Server requests the (hashed) company password.
	PACKET_CLIENT_COMPANY_PASSWORD,      ///< Client sends the (hashed) company password.

	/* The server welcomes the authenticated client and sends information of other clients. */
	PACKET_SERVER_WELCOME,               ///< Server welcomes you and gives you your #ClientID.
	PACKET_SERVER_CLIENT_INFO,           ///< Server sends you information about a client.

	/* Getting the savegame/map. */
	PACKET_CLIENT_GETMAP,                ///< Client requests the actual map.
	PACKET_SERVER_WAIT,                  ///< Server tells the client there are some people waiting for the map as well.
	PACKET_SERVER_MAP_BEGIN,             ///< Server tells the client that it is beginning to send the map.
	PACKET_SERVER_MAP_SIZE,              ///< Server tells the client what the (compressed) size of the map is.
	PACKET_SERVER_MAP_DATA,              ///< Server sends bits of the map to the client.
	PACKET_SERVER_MAP_DONE,              ///< Server tells it has just sent the last bits of the map to the client.
	PACKET_CLIENT_MAP_OK,                ///< Client tells the server that it received the whole map.

	PACKET_SERVER_JOIN,                  ///< Tells clients that a new client has joined.

	/*
	 * At this moment the client has the map and
	 * the client is fully authenticated. Now the
	 * normal communication starts.
	 */

	/* Game progress monitoring. */
	PACKET_SERVER_FRAME,                 ///< Server tells the client what frame it is in, and thus to where the client may progress.
	PACKET_CLIENT_ACK,                   ///< The client tells the server which frame it has executed.
	PACKET_SERVER_SYNC,                  ///< Server tells the client what the random state should be.

	/* Sending commands around. */
	PACKET_CLIENT_COMMAND,               ///< Client executed a command and sends it to the server.
	PACKET_SERVER_COMMAND,               ///< Server distributes a command to (all) the clients.

	/* Human communication! */
	PACKET_CLIENT_CHAT,                  ///< Client said something that should be distributed.
	PACKET_SERVER_CHAT,                  ///< Server distributing the message of a client (or itself).

	/* Remote console. */
	PACKET_CLIENT_RCON,                  ///< Client asks the server to execute some command.
	PACKET_SERVER_RCON,                  ///< Response of the executed command on the server.

	/* Moving a client.*/
	PACKET_CLIENT_MOVE,                  ///< A client would like to be moved to another company.
	PACKET_SERVER_MOVE,                  ///< Server tells everyone that someone is moved to another company.

	/* Configuration updates. */
	PACKET_CLIENT_SET_PASSWORD,          ///< A client (re)sets its company's password.
	PACKET_CLIENT_SET_NAME,              ///< A client changes its name.
	PACKET_SERVER_COMPANY_UPDATE,        ///< Information (password) of a company changed.
	PACKET_SERVER_CONFIG_UPDATE,         ///< Some network configuration important to the client changed.

	/* A server quitting this game. */
	PACKET_SERVER_NEWGAME,               ///< The server is preparing to start a new game.
	PACKET_SERVER_SHUTDOWN,              ///< The server is shutting down.

	/* A client quitting. */
	PACKET_CLIENT_QUIT,                  ///< A client tells the server it is going to quit.
	PACKET_SERVER_QUIT,                  ///< A server tells that a client has quit.
	PACKET_CLIENT_ERROR,                 ///< A client reports an error to the server.
	PACKET_SERVER_ERROR_QUIT,            ///< A server tells that a client has hit an error and did quit.

	PACKET_END                           ///< Must ALWAYS be on the end of this list!! (period)
};

/** Packet that wraps a command */
struct CommandPacket;

/** A queue of CommandPackets. */
class CommandQueue {
	CommandPacket *first; ///< The first packet in the queue.
	CommandPacket *last;  ///< The last packet in the queue; only valid when first != NULL.
	uint count;           ///< The number of items in the queue.

public:
	/** Initialise the command queue. */
	CommandQueue() : first(NULL), last(NULL) {}
	/** Clear the command queue. */
	~CommandQueue() { this->Free(); }
	void Append(CommandPacket *p);
	CommandPacket *Pop(bool ignore_paused = false);
	CommandPacket *Peek(bool ignore_paused = false);
	void Free();
	/** Get the number of items in the queue. */
	uint Count() const { return this->count; }
};

#define DECLARE_GAME_RECEIVE_COMMAND(type) virtual NetworkRecvStatus NetworkPacketReceive_## type ##_command(Packet *p)
#define DEF_GAME_RECEIVE_COMMAND(cls, type) NetworkRecvStatus cls ##NetworkGameSocketHandler::NetworkPacketReceive_ ## type ## _command(Packet *p)

/** Base socket handler for all TCP sockets */
class NetworkGameSocketHandler : public NetworkTCPSocketHandler {
/* TODO: rewrite into a proper class */
private:
	NetworkClientInfo *info;  ///< Client info related to this socket

protected:

	/**
	 * Notification that the server is full.
	 */
	DECLARE_GAME_RECEIVE_COMMAND(PACKET_SERVER_FULL);

	/**
	 * Notification that the client trying to join is banned.
	 */
	DECLARE_GAME_RECEIVE_COMMAND(PACKET_SERVER_BANNED);

	/**
	 * Try to join the server:
	 * string  OpenTTD revision (norev000 if no revision).
	 * string  Name of the client (max NETWORK_NAME_LENGTH).
	 * uint8   ID of the company to play as (1..MAX_COMPANIES).
	 * uint8   ID of the clients Language.
	 */
	DECLARE_GAME_RECEIVE_COMMAND(PACKET_CLIENT_JOIN);

	/**
	 * The client made an error:
	 * uint8   Error code caused (see NetworkErrorCode).
	 */
	DECLARE_GAME_RECEIVE_COMMAND(PACKET_SERVER_ERROR);

	/**
	 * Request company information (in detail).
	 */
	DECLARE_GAME_RECEIVE_COMMAND(PACKET_CLIENT_COMPANY_INFO);

	/**
	 * Sends information about the companies (one packet per company):
	 * uint8   Version of the structure of this packet (NETWORK_COMPANY_INFO_VERSION).
	 * bool    Contains data (false marks the end of updates).
	 * uint8   ID of the company.
	 * string  Name of the company.
	 * uint32  Year the company was inaugurated.
	 * uint64  Value.
	 * uint64  Money.
	 * uint64  Income.
	 * uint16  Performance (last quarter).
	 * bool    Company is password protected.
	 * uint16  Number of trains.
	 * uint16  Number of lorries.
	 * uint16  Number of busses.
	 * uint16  Number of planes.
	 * uint16  Number of ships.
	 * uint16  Number of train stations.
	 * uint16  Number of lorry stations.
	 * uint16  Number of bus stops.
	 * uint16  Number of airports and heliports.
	 * uint16  Number of harbours.
	 * bool    Company is an AI.
	 * string  Client names (comma separated list)
	 */
	DECLARE_GAME_RECEIVE_COMMAND(PACKET_SERVER_COMPANY_INFO);

	/**
	 * Send information about a client:
	 * uint32  ID of the client (always unique on a server. 1 = server, 0 is invalid).
	 * uint8   ID of the company the client is playing as (255 for spectators).
	 * string  Name of the client.
	 */
	DECLARE_GAME_RECEIVE_COMMAND(PACKET_SERVER_CLIENT_INFO);

	/**
	 * Indication to the client that the server needs a game password.
	 */
	DECLARE_GAME_RECEIVE_COMMAND(PACKET_SERVER_NEED_GAME_PASSWORD);

	/**
	 * Indication to the client that the server needs a company password:
	 * uint32  Generation seed.
	 * string  Network ID of the server.
	 */
	DECLARE_GAME_RECEIVE_COMMAND(PACKET_SERVER_NEED_COMPANY_PASSWORD);

	/**
	 * Send a password to the server to authorize:
	 * uint8   Password type (see NetworkPasswordType).
	 * string  The password.
	 */
	DECLARE_GAME_RECEIVE_COMMAND(PACKET_CLIENT_GAME_PASSWORD);

	/**
	 * Send a password to the server to authorize
	 * uint8   Password type (see NetworkPasswordType).
	 * string  The password.
	 */
	DECLARE_GAME_RECEIVE_COMMAND(PACKET_CLIENT_COMPANY_PASSWORD);

	/**
	 * The client is joined and ready to receive his map:
	 * uint32  Own client ID.
	 * uint32  Generation seed.
	 * string  Network ID of the server.
	 */
	DECLARE_GAME_RECEIVE_COMMAND(PACKET_SERVER_WELCOME);

	/**
	 * Request the map from the server.
	 * uint32  NewGRF version (release versions of OpenTTD only).
	 */
	DECLARE_GAME_RECEIVE_COMMAND(PACKET_CLIENT_GETMAP);

	/**
	 * Notification that another client is currently receiving the map:
	 * uint8   Number of clients waiting in front of you.
	 */
	DECLARE_GAME_RECEIVE_COMMAND(PACKET_SERVER_WAIT);

	/**
	 * Sends that the server will begin with sending the map to the client:
	 * uint32  Current frame.
	 */
	DECLARE_GAME_RECEIVE_COMMAND(PACKET_SERVER_MAP_BEGIN);

	/**
	 * Sends the size of the map to the client.
	 * uint32  Size of the (compressed) map (in bytes).
	 */
	DECLARE_GAME_RECEIVE_COMMAND(PACKET_SERVER_MAP_SIZE);

	/**
	 * Sends the data of the map to the client:
	 * Contains a part of the map (until max size of packet).
	 */
	DECLARE_GAME_RECEIVE_COMMAND(PACKET_SERVER_MAP_DATA);

	/**
	 * Sends that all data of the map are sent to the client:
	 */
	DECLARE_GAME_RECEIVE_COMMAND(PACKET_SERVER_MAP_DONE);

	/**
	 * Tell the server that we are done receiving/loading the map.
	 */
	DECLARE_GAME_RECEIVE_COMMAND(PACKET_CLIENT_MAP_OK);

	/**
	 * A client joined (PACKET_CLIENT_MAP_OK), what usually directly follows is a PACKET_SERVER_CLIENT_INFO:
	 * uint32  ID of the client that just joined the game.
	 */
	DECLARE_GAME_RECEIVE_COMMAND(PACKET_SERVER_JOIN);

	/**
	 * Sends the current frame counter to the client:
	 * uint32  Frame counter
	 * uint32  Frame counter max (how far may the client walk before the server?)
	 * uint32  General seed 1 (dependant on compile settings, not default).
	 * uint32  General seed 2 (dependant on compile settings, not default).
	 * uint8   Random token to validate the client is actually listening (only occasionally present).
	 */
	DECLARE_GAME_RECEIVE_COMMAND(PACKET_SERVER_FRAME);

	/**
	 * Sends a sync-check to the client:
	 * uint32  Frame counter.
	 * uint32  General seed 1.
	 * uint32  General seed 2 (dependant on compile settings, not default).
	 */
	DECLARE_GAME_RECEIVE_COMMAND(PACKET_SERVER_SYNC);

	/**
	 * Tell the server we are done with this frame:
	 * uint32  Current frame counter of the client.
	 * uint8   The random token that the server sent in the PACKET_SERVER_FRAME packet.
	 */
	DECLARE_GAME_RECEIVE_COMMAND(PACKET_CLIENT_ACK);

	/**
	 * Send a DoCommand to the Server:
	 * uint8   ID of the company (0..MAX_COMPANIES-1).
	 * uint32  ID of the command (see command.h).
	 * uint32  P1 (free variables used in DoCommand).
	 * uint32  P2
	 * uint32  Tile where this is taking place.
	 * string  Text.
	 * uint8   ID of the callback.
	 */
	DECLARE_GAME_RECEIVE_COMMAND(PACKET_CLIENT_COMMAND);

	/**
	 * Sends a DoCommand to the client:
	 * uint8   ID of the company (0..MAX_COMPANIES-1).
	 * uint32  ID of the command (see command.h).
	 * uint32  P1 (free variable used in DoCommand).
	 * uint32  P2.
	 * uint32  Tile where this is taking place.
	 * string  Text.
	 * uint8   ID of the callback.
	 * uint32  Frame of execution.
	 */
	DECLARE_GAME_RECEIVE_COMMAND(PACKET_SERVER_COMMAND);

	/**
	 * Sends a chat-packet to the server:
	 * uint8   ID of the action (see NetworkAction).
	 * uint8   ID of the destination type (see DestType).
	 * uint32  ID of the client or company (destination of the chat).
	 * string  Message (max NETWORK_CHAT_LENGTH).
	 * uint64  data (used e.g. for 'give money' actions).
	 */
	DECLARE_GAME_RECEIVE_COMMAND(PACKET_CLIENT_CHAT);

	/**
	 * Sends a chat-packet to the client:
	 * uint8   ID of the action (see NetworkAction).
	 * uint32  ID of the client (origin of the chat).
	 * string  Message (max NETWORK_CHAT_LENGTH).
	 * uint64  data (used e.g. for 'give money' actions).
	 */
	DECLARE_GAME_RECEIVE_COMMAND(PACKET_SERVER_CHAT);

	/**
	 * Set the password for the clients current company:
	 * string  The password.
	 */
	DECLARE_GAME_RECEIVE_COMMAND(PACKET_CLIENT_SET_PASSWORD);

	/**
	 * Gives the client a new name:
	 * string  New name of the client.
	 */
	DECLARE_GAME_RECEIVE_COMMAND(PACKET_CLIENT_SET_NAME);

	/**
	 * The client is quiting the game.
	 */
	DECLARE_GAME_RECEIVE_COMMAND(PACKET_CLIENT_QUIT);

	/**
	 * The client made an error and is quiting the game.
	 * uint8   Error of the code caused (see NetworkErrorCode).
	 */
	DECLARE_GAME_RECEIVE_COMMAND(PACKET_CLIENT_ERROR);

	/**
	 * Notification that a client left the game:
	 * uint32  ID of the client.
	 */
	DECLARE_GAME_RECEIVE_COMMAND(PACKET_SERVER_QUIT);

	/**
	 * Inform all clients that one client made an error and thus has quit/been disconnected:
	 * uint32  ID of the client that caused the error.
	 * uint8   Code of the error caused (see NetworkErrorCode).
	 */
	DECLARE_GAME_RECEIVE_COMMAND(PACKET_SERVER_ERROR_QUIT);

	/**
	 * Let the clients know that the server is closing.
	 */
	DECLARE_GAME_RECEIVE_COMMAND(PACKET_SERVER_SHUTDOWN);

	/**
	 * Let the clients know that the server is loading a new map.
	 */
	DECLARE_GAME_RECEIVE_COMMAND(PACKET_SERVER_NEWGAME);

	/**
	 * Send the result of an issues RCon command back to the client:
	 * uint16  Colour code.
	 * string  Output of the RCon command
	 */
	DECLARE_GAME_RECEIVE_COMMAND(PACKET_SERVER_RCON);

	/**
	 * Send an RCon command to the server:
	 * string  RCon password.
	 * string  Command to be executed.
	 */
	DECLARE_GAME_RECEIVE_COMMAND(PACKET_CLIENT_RCON);

	/**
	 * Sends information about all used GRFs to the client:
	 * uint8   Amount of GRFs (the following data is repeated this many times, i.e. per GRF data).
	 * uint32  GRF ID
	 * 16 * uint8   MD5 checksum of the GRF
	 */
	DECLARE_GAME_RECEIVE_COMMAND(PACKET_SERVER_CHECK_NEWGRFS);

	/**
	 * Tell the server that we have the required GRFs
	 */
	DECLARE_GAME_RECEIVE_COMMAND(PACKET_CLIENT_NEWGRFS_CHECKED);

	/**
	 * Move a client from one company into another:
	 * uint32  ID of the client.
	 * uint8   ID of the new company.
	 */
	DECLARE_GAME_RECEIVE_COMMAND(PACKET_SERVER_MOVE);

	/**
	 * Request the server to move this client into another company:
	 * uint8   ID of the company the client wants to join.
	 * string  Password, if the company is password protected.
	 */
	DECLARE_GAME_RECEIVE_COMMAND(PACKET_CLIENT_MOVE);

	/**
	 * Update the clients knowledge of which company is password protected:
	 * uint16  Bitwise representation of each company
	 */
	DECLARE_GAME_RECEIVE_COMMAND(PACKET_SERVER_COMPANY_UPDATE);

	/**
	 * Update the clients knowledge of the max settings:
	 * uint8   Maximum number of companies allowed.
	 * uint8   Maximum number of spectators allowed.
	 */
	DECLARE_GAME_RECEIVE_COMMAND(PACKET_SERVER_CONFIG_UPDATE);

	NetworkRecvStatus HandlePacket(Packet *p);

	NetworkGameSocketHandler(SOCKET s);
public:
	ClientID client_id;          ///< Client identifier
	uint32 last_frame;           ///< Last frame we have executed
	uint32 last_frame_server;    ///< Last frame the server has executed
	CommandQueue incoming_queue; ///< The command-queue awaiting handling
	uint last_packet;            ///< Time we received the last frame.

	NetworkRecvStatus CloseConnection(bool error = true);
	virtual NetworkRecvStatus CloseConnection(NetworkRecvStatus status) = 0;
	virtual ~NetworkGameSocketHandler() {}

	inline void SetInfo(NetworkClientInfo *info) { assert(info != NULL && this->info == NULL); this->info = info; }
	inline NetworkClientInfo *GetInfo() const { return this->info; }

	NetworkRecvStatus ReceivePackets();

	const char *ReceiveCommand(Packet *p, CommandPacket *cp);
	void SendCommand(Packet *p, const CommandPacket *cp);
};

#endif /* ENABLE_NETWORK */

#endif /* NETWORK_CORE_TCP_GAME_H */
