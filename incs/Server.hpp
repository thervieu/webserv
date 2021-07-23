#ifndef SERVER_HPP
# define SERVER_HPP

# include "Client.hpp"

class Server
{
	private:
		
		std::vector<Socket *> _sockets;
		std::vector<Client *> _clients;

	public:

		Server(void);
		Server(const Server &server);
		~Server(void);

		void	addSocket(Socket *socket);
		void	addClient(Client *client);

		int		acceptSocketDescriptor(int i, int sd, int max_sd, fd_set *read_set, fd_set *write_set);
		int		receiveConnection(int sd, std::string &request);
		std::vector<Socket *>		getSockets(void);

		int				getMaxSd(void);
		std::string		vecToString(std::vector<char> vector);
		void			select_loop(void);
		void 			endServer(void);
};

#endif