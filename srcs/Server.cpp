#include "../incs/Server.hpp"

Server::Server(void)
{}

Server::Server(const Server &other)
{
	_sockets = other._sockets;
}

Server::~Server(void) {}

void	Server::addSocket(Socket *socket)
{
	_sockets.push_back(socket);
}

void	Server::addClient(Client *client)
{
	_clients.push_back(client);
}

int		Server::getMaxSd(void)
{
	return (_sockets[_sockets.size() - 1]->getSocketDescriptor());
}

std::string		ft_inet_ntoa(struct in_addr in)
{
	std::stringstream buffer;

	unsigned char *bytes = (unsigned char *) &in;
	for (int cur_bytes = 0; cur_bytes < 4; cur_bytes++)
	{
		buffer << (int)bytes[cur_bytes];
		if (cur_bytes != 3)
			buffer << '.';
	}
	return (buffer.str());
}

int		Server::acceptSocketDescriptor(int sd, int max_sd, fd_set *read_set, fd_set *write_set)
{
	int 		newfd;
	struct sockaddr_in	clientaddr;

	socklen_t	addrlen = sizeof(clientaddr);

	if((newfd = accept(sd, (struct sockaddr *)&clientaddr, &addrlen)) == -1)
	{
		std::cout << "Couldn't accept " << sd << std::endl;
		exit(1);
	}

	std::cout << "accepted: " << sd << std::endl;
	addClient(new Client(_sockets[sd], ft_inet_ntoa(clientaddr.sin_addr)));
	FD_SET(newfd, read_set);
	FD_SET(newfd, write_set);

	if (newfd > max_sd)
		max_sd = newfd;
	return (max_sd);
}

int		Server::receiveConnection(int sd, std::string &request)
{
	char buffer_recv[10000 + 1];
	int rc = 0;
    rc = read(sd, buffer_recv, 10000);
	if (rc > 0)
	{
		request.append(buffer_recv);
		return (0);
	}
	else
	{
		return (-1);
	}
}

// Thanks to https://www.tenouk.com/Module41.html
void	Server::select_loop(void)
{
	fd_set	read_set;
	fd_set	master_read_set;
	
	fd_set	write_set;
	fd_set	master_write_set;

	FD_ZERO(&write_set);
	FD_ZERO(&read_set);
	for (size_t i = 0; i < _sockets.size(); i++)
		FD_SET(_sockets[i]->getSocketDescriptor(), &read_set);

	int max_sd = this->getMaxSd();

	while (1)
	{
		read_set = master_read_set;
		write_set = master_write_set;

		std::cout << "HERE3" << std::endl;
		select(max_sd + 1, &read_set, &write_set, NULL, NULL);
		for (int i = 0; i < getMaxSd(); i++)
		{
			int sd = this->_sockets[i]->getSocketDescriptor();
			if (FD_ISSET(sd, &read_set))
				max_sd = acceptSocketDescriptor(sd, max_sd, &read_set, &write_set);
		}

		for (size_t client_nb = 0; client_nb < _clients.size(); client_nb++)
		{
			Client &client = *_clients[client_nb];
			int client_sd;
			client_sd = client.getSocket().getSocketDescriptor();

			if (FD_ISSET(client_sd, &read_set))
			{
				std::cout << "HERE4\n";
				int rtn = receiveConnection(client_sd, client.getRequest());
				if (rtn < 0)
				{
					close(client_sd);
					FD_CLR(client_sd, &master_read_set);
					FD_CLR(client_sd, &master_write_set);
					if (client_sd == max_sd)
						while (FD_ISSET(max_sd, &master_read_set) == false)
							max_sd -= 1;
				}
				client.setReceived(true);
			}
			// call Request.cpp
		}
	}
}
