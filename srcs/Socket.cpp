#include "../incs/Socket.hpp"

Socket::Socket(void) : _fd(0), _socket(0), _server(server_info()), _buff(NULL)
{
}

Socket::Socket(int fd) : _fd(fd), _server(server_info()), _buff(NULL)
{
}

Socket::Socket(const Socket &other): _fd(other._fd), _socket(0), _address(other._address), _addrlen(other._addrlen), _server(other._server), _buff(other._buff)
{
}

Socket::Socket(server_info server)
{
	this->_server = server;

	if ((this->_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		std::cout << "Error: Unable to create socket" << std::endl;
		exit(1);
	}
	if (setsockopt(this->_fd, SOL_SOCKET, SO_REUSEADDR, &this->_opt, sizeof(this->_opt)) < 0)
	{
		std::cout << "Error: Unable to set socket options: setsockopt" << std::endl;
		exit(1);
	}
	// if (setsockopt(this->_fd, SOL_SOCKET, SO_REUSEPORT, &this->_opt, sizeof(this->_opt)) < 0)
	// {
	// 	std::cout << "Error: Unable to set socket options: setsockopt" << std::endl;
	// 	exit(1);
	// }

	// if (fcntl(this->_fd, F_SETFL, O_NONBLOCK) < 0)
	// {
	// 	std::cout << "Error: Unable to set socket to non blocking" << std::endl;
	// 	exit(1);
	// }
	this->_address.sin_family = AF_INET;
	this->_address.sin_addr.s_addr = INADDR_ANY;
	this->_address.sin_port = htons((int)server._port);
	if (bind(this->_fd, (struct sockaddr *)&this->_address, sizeof(this->_address)) < 0)
	{
		std::cout << "Error: bind failed" << std::endl;
		exit(1);
	}
	if (listen(this->_fd, 3) < 0)
	{
		std::cout << "Error: Unable to listen socket" << std::endl;
		exit(1);
	}
	if (!(this->_buff = static_cast<char*>(malloc(this->_server._client_max_body_size * sizeof(char)))))
	{
		std::cout << "Error: Memory required too high" << std::endl;
		exit(1);
	}
	//this->MainLoop();
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

void	Socket::MainLoop()
{
	Response			response;
	std::vector<char>	message;

	while (1)
	{
		if ((this->_socket = accept(this->_fd, (struct sockaddr *)&this->_address, (socklen_t*)&this->_addrlen)) < 0)
		{
			std::cout << "Error: accept failed" << std::endl;
			exit(1);
		}
		// Select ??
		if (read(this->_socket, this->_buff, this->_server._client_max_body_size) < 0)
		{
			std::cout << "Error: read failed" << std::endl;
			exit(1);
		}
		std::cout << this->_buff << std::endl;
		response.setRequest(Request(this->_buff, this->_server));
		message = response.sendResponse();
		send(this->_socket, &message[0], message.size(), 0);
		std::cout << "\nResponse sent !\n" << std::endl;
	}
}
