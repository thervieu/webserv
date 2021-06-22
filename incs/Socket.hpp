#ifndef SOCKET_HPP
# define SOCKET_HPP

# include "Webserv.hpp"
# include "Config.hpp"
# include "Response.hpp"

# define SIZE_MALLOC 5000000

class Socket
{
	private:
		
		int					_fd;
		int					_opt;
		int					_socket;
		struct sockaddr_in	_address;
		int					_addrlen;
		server_info			_server;
		char				*_buff;


	public:

		Socket(void);
		Socket(int fd);
		Socket(const Socket &other);
		Socket(server_info _server);
		~Socket(void);

		int				getSocketDescriptor(void);
		std::string		getBuffer(void);
		server_info		getServerConfig(void);

};
#endif