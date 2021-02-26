#ifndef SOCKET_HPP
# define SOCKET_HPP

# include "Webserv.hpp"
# include "Config.hpp"

class Socket
{
	private:
		
		int					_fd;
		int					_opt;
		struct sockaddr_in	_address;
		server_info			_server;

	public:

		Socket(void);
		Socket(const Socket &other);
		Socket(server_info _server);
		~Socket(void);

		int		getFd(void);

};

#endif