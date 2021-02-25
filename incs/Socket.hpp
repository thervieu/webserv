#ifndef SOCKET_HPP
# define SOCKET_HPP

# include "webserv.hpp"
# include "Config.hpp"

class Socket
{
	private:
		
		int					_id;
		int					_opt;
		struct sockaddr_in	_address;
		server_info			_server;

	public:

		Socket(void);
		Socket(const Socket &other);
		Socket(server_info _server);
		~Socket(void);

};

#endif