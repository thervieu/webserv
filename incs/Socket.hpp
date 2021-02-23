#ifndef SOCKET_HPP
# define SOCKET_HPP

# include "webserv.hpp"
# include "Config.hpp"

class Socket
{
	private:
		
		int     _id;
		struct sockaddr_in _addr;
		server_info _server;

	public:

		Socket(void);
		Socket(const Socket &other);
		Socket(server_info _server);
		~Socket(void);

};

#endif