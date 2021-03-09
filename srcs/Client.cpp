#include "../incs/Client.hpp"

Client::Client(const Client &other)
: _socket(other._socket), _ip(other._ip), _request(other._request), _received(other._received)
{}

Client::Client(Socket *socket, std::string _addr)
: _socket(socket), _ip(_addr), _request(), _received(false)
{

}

Socket		&Client::getSocket(void)
{
	return (*_socket);
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
