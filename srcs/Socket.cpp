#include "../incs/Socket.hpp"

Socket::Socket(void) : _fd(0), _server(server_info()), _buff(NULL)
{
}

Socket::Socket(int fd) : _fd(fd), _server(server_info()), _buff(NULL)
{
}

Socket::Socket(const Socket &other): _fd(other._fd), _address(other._address), _addrlen(other._addrlen), _server(other._server), _buff(other._buff)
{
}

Socket::Socket(server_info server)
{
	this->_server = server;

	if ((this->_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		std::cout << "Error: Unable to create socket" << std::endl;
		throw std::exception();
	}
	if (setsockopt(this->_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &this->_opt, sizeof(this->_opt)) < 0)
	{
		std::cout << "Error: Unable to set socket options: reuseaddr" << std::endl;
		throw std::exception();
	}

	if (fcntl(this->_fd, F_SETFL, O_NONBLOCK) < 0)
	{
		std::cout << "Error: Unable to set socket to non blocking" << std::endl;
		throw std::exception();
	}

	this->_address.sin_family = AF_INET;
	this->_address.sin_addr.s_addr = INADDR_ANY;
	this->_address.sin_port = htons((int)server._port);
	if (bind(this->_fd, (struct sockaddr *)&this->_address, sizeof(this->_address)) < 0)
	{
		std::cout << "Error: bind failed" << std::endl;
		throw std::exception();
	}
	if (listen(this->_fd, 1000) < 0)
	{
		std::cout << "Error: Unable to listen socket" << std::endl;
		throw std::exception();
	}
	if (!(this->_buff = static_cast<char*>(malloc(this->_server._client_max_body_size * sizeof(char)))))
	{
		std::cout << "Error: Memory required too high" << std::endl;
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

char			*Socket::getBuffer()
{
	return (this->_buff);
}
