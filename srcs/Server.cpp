#include "../incs/Server.hpp"

Server::Server(void)
{
}

Server::Server(const Server &other)
{
	_sockets = other._sockets;
}

Server::~Server(void) {}
