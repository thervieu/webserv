#include "../incs/Server.hpp"

Server::Server(void)
{}

Server::Server(const Server &other)
{
	_sockets = other._sockets;
}

Server::~Server(void) {}

void	Server::addSocket(Socket *socket)
{
	_sockets.push_back(socket);
}

int		Server::getMaxFd(void)
{
	return (_sockets[_sockets.size() - 1]->getFd() + 1);
}

void	Server::select_loop(void)
{
	fd_set	read_fd;
	fd_set	write_fd;

	FD_ZERO(&read_fd);
	for (size_t i = 0; i < _sockets.size(); i++)
		FD_SET(_sockets[i]->getFd(), &read_fd);
	FD_ZERO(&write_fd);

	int max_fd = getMaxFd();
	(void)max_fd;
	
}
