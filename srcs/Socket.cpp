#include "../incs/Socket.hpp"

Socket::Socket(void)
{
}

Socket::Socket(const Socket &other): _id(other._id), _addr(other._addr), _server(other._server)
{
}

Socket::Socket(server_info serv)
{
	_server = serv;
	//create sock
	//sockoptions ?
	//bind
	//listensock
}

Socket::~Socket(void) {}
