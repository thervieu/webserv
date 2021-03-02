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
		Socket(const Socket &other);
		Socket(server_info _server);
		~Socket(void);

		int				getFd(void);
		std::string		getBuffer(void);

		void			MainLoop(void);
};

#endif