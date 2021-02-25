#ifndef SERVER_HPP
# define SERVER_HPP

# include "Socket.hpp"

class Server
{
	private:
		
		std::vector<Socket *> _sockets;

	public:

		Server(void);
		Server(const Server &server);
		~Server(void);

		void	addSocket(Socket *socket);

};

#endif