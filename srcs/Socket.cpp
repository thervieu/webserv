#include "../incs/Socket.hpp"

Socket::Socket(void) : _fd(0), _server(server_info())
{
}

Socket::Socket(const Socket &other): _fd(other._fd), _address(other._address), _addrlen(other._addrlen), _server(other._server)
{
}

Socket::Socket(int fd) : _fd(fd)
{
}

Socket::Socket(int fd, server_info server) : _fd(fd), _server(server)
{
}

#include <cerrno>

Socket::Socket(server_info server)
{
	this->_server = server;

	if ((this->_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		std::cout << "Error: Unable to create socket" << std::endl;
		throw std::exception();
	}
	if (setsockopt(this->_fd, SOL_SOCKET, SO_REUSEADDR, &this->_opt, sizeof(this->_opt)) < 0)
	{
		std::cout << "Error: Unable to set socket options: reuseaddr: |" << strerror(errno) << "|\n";
		throw std::exception();
	}

	if (fcntl(this->_fd, F_SETFL, O_NONBLOCK) < 0)
	{
		std::cout << "Error: Unable to set socket to non blocking: |" << strerror(errno) << "|\n";
		throw std::exception();
	}

	this->_address.sin_family = AF_INET;
	this->_address.sin_addr.s_addr = INADDR_ANY;
	this->_address.sin_port = htons((int)server._port);
	if (bind(this->_fd, (struct sockaddr *)&this->_address, sizeof(this->_address)) < 0)
	{
		std::cout << "Error: port [" << server._port << "] bind failed: |" << strerror(errno) << "|\n";
		throw std::exception();
	}
	if (listen(this->_fd, 1000) < 0)
	{
		std::cout << "Error: Unable to listen socket: |" << strerror(errno) << "|\n";
		throw std::exception();
	}
}

Socket::~Socket(void)
{}

int		Socket::getSocketDescriptor(void)
{
	return (_fd);
}


server_info		Socket::getServerConfig(void)
{
	return (_server);
}
