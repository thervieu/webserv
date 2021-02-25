#include "../incs/Socket.hpp"

Socket::Socket(void)
{
}

Socket::Socket(const Socket &other): _fd(other._fd), _address(other._address), _server(other._server)
{
}

Socket::Socket(server_info server)
{
	_server = server;
	_address.sin_family = AF_INET;
	_address.sin_addr.s_addr = INADDR_ANY;
	_address.sin_port = htons(server._port);
	if ((_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		std::cout << "Error: Unable to create socket" << std::endl;
		exit(1);
	}
	if (setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &_opt, sizeof(_opt)))
	{
		std::cout << "Error: Unable to set socket options: setsockopt" << std::endl;
		exit(1);
	}
	if (fcntl(_fd, F_SETFL, O_NONBLOCK) < 0)
	{
		std::cout << "Error: Unable to set socket to non blocking" << std::endl;
		exit(1);
	}
	if (bind(_fd, (struct sockaddr *)&_address, sizeof(_address)) < 0)
	{
		std::cout << "Error: bind failed" << std::endl;
		exit(1);
	}
	if (listen(_fd, 1000) < 0)
	{
		std::cout << "Error: Unable to listen socket" << std::endl;
		exit(1);
	}
}

Socket::~Socket(void) {}


int		Socket::getFd(void)
{
	return (_fd);
}
