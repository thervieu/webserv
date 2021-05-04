#include "../incs/Client.hpp"

Client::Client(Socket *socket, std::string _addr, int clientFd)
: Socket(clientFd), _serverSocket(socket), _clientFd(clientFd), _ip(_addr), _request(), _received(false)
{}

Client::Client(const Client &other)
: Socket(other._clientFd), _serverSocket(other._serverSocket), _ip(other._ip), _request(other._request), _received(other._received)
{}

Client::~Client(void)
{}

Socket		&Client::getServerSocket(void)
{
	return (*_serverSocket);
}

int			Client::getClientFd(void)
{
	return (_clientFd);
}

std::string	Client::getIP(void)
{
	return (_ip);
}

std::string	&Client::getRequest(void)
{
	return (_request);
}

void		Client::setReceived(bool _bool)
{
	_received = _bool;
}

bool		Client::getReceived(void)
{
	return (_received);
}
