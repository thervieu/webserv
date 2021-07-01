#include "../incs/Server.hpp"
#include <strings.h>

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

int		Server::getSocket(int i)
{
	return (this->_sockets[i]->getSocketDescriptor());
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

int		Server::acceptSocketDescriptor(int i, int sd, int max_sd, fd_set *read_set, fd_set *write_set)
{
	int 		newfd;
	struct sockaddr_in	clientaddr;

	socklen_t	addrlen = sizeof(clientaddr);

	if((newfd = accept(sd, (struct sockaddr *)&clientaddr, &addrlen)) == -1)
	{
		std::cout << "Couldn't accept " << sd << std::endl;
		exit(1);
	}

	// std::cout << "accepted: " << sd << std::endl;
	addClient(new Client(_sockets[i], ft_inet_ntoa(clientaddr.sin_addr), newfd));
	FD_SET(newfd, read_set);
	FD_SET(newfd, write_set);

	if (newfd > max_sd)
		max_sd = newfd;
	return (max_sd);
}

int 	isContentWhole(std::string request)
{
	size_t pos = 0;
	size_t find_pos = 0;
	size_t end_pos = request.find("\n");


	while (end_pos != std::string::npos)
	{
		std::string	l = request.substr(pos, end_pos - pos);

		if ((find_pos = l.find("Transfer-Encoding: chunked")) != std::string::npos && find_pos == 0)
			return (2);
		else if ((find_pos = l.find("Content")) != std::string::npos && find_pos == 0)
			return (1);
		else if ((find_pos = l.find("\r\n\r\n")) != std::string::npos && find_pos == 0)
			return (0);

		pos = end_pos + 1;
		end_pos = request.find("\n", pos);
	}
	return (0);
}

size_t getContentLen(std::string request)
{
	size_t pos = 0;
	size_t find_pos = 0;
	size_t end_pos = request.find("\n");


	while (end_pos != std::string::npos)
	{
		std::string	l = request.substr(pos, end_pos - pos);

		if ((find_pos = l.find("Content-Length:")) != std::string::npos && find_pos == 0)
			return (atoi(l.substr(l.find(":") + 2, l.length()).c_str()));
		else if ((find_pos = l.find("\r\n\r\n")) != std::string::npos && find_pos == 0)
			return (0);


		pos = end_pos + 1;
		end_pos = request.find("\n", pos);
	}
	return (0);
}

int		Server::receiveConnection(int sd, std::string &request)
{
	char buffer_recv[BUFFER_SIZE + 1];
	bzero(buffer_recv, BUFFER_SIZE + 1);

	int rtn_read = 0;
    rtn_read = read(sd, buffer_recv, BUFFER_SIZE);
	// std::cout << "rtn read = |" << rtn_read << "|\n";
	// std::cout << "REQUEST BEF = |" << request << "|\n";
	// std::cout << "BUFFER = |" << buffer_recv << "|\n";
	
	if (rtn_read > 0)
	{
		request.append(buffer_recv);
		// std::cout << "REQUEST AFT = |" << request << "|\n";
		// Verification that content exists \r\n etc

		int _complete = isContentWhole(request);
		// std::cout << "complete = |" << _complete << "|\n";
		size_t find_pos;
		if ((find_pos = request.find("\r\n\r\n")) != std::string::npos && _complete == 0)
			return (0);

		if (_complete > 0)
		{
			std::string rest = request.substr(find_pos + 4, request.length() - (find_pos + 4));
			// std::cout << "rest = |" << rest << "|\n";

			if (_complete == 1 && (rest.length() == getContentLen(request)))
				return (0);
			
			std::string to_find = "\r\n\r\n";
			//https://fr.wikipedia.org/wiki/Chunked_transfer_encoding
			if (_complete == 2)
				to_find = "0" + to_find;
			if ((find_pos = rest.find(to_find)) != std::string::npos)
			{
				if (_complete == 1  || (_complete == 2 && (find_pos == 0 || (rest[find_pos - 1] == '\n' && rest[find_pos - 2] == '\r'))))
					return (0);
			}
		}
	}
	else
	{
		return (-1);
	}
	return (1);
}

// Thanks to https:www.tenouk.com/Module41.html
void	Server::select_loop(void)
{
	fd_set	read_set;
	fd_set	master_read_set;
	
	fd_set	write_set;
	fd_set	master_write_set;

	FD_ZERO(&write_set);
	FD_ZERO(&read_set);
	FD_ZERO(&master_write_set);
	FD_ZERO(&master_read_set);
	for (size_t i = 0; i < _sockets.size(); i++)
	{
		FD_SET(_sockets[i]->getSocketDescriptor(), &master_read_set);
	}
	int max_sd = this->getMaxSd();

	while (1)
	{
		read_set = master_read_set;
		write_set = master_write_set;

		// std::cout << "bef select sockets size = |" << _sockets.size() << "|\n";
		select(max_sd + 1, &read_set, &write_set, NULL, NULL);
		for (size_t i = 0; i < _sockets.size(); i++)
		{
			int sd = this->_sockets[i]->getSocketDescriptor();
			if (FD_ISSET(sd, &read_set))
			{
				max_sd = acceptSocketDescriptor(i, sd, max_sd, &master_read_set, &master_write_set);
			}
		}
		for (size_t client_nb = 0; client_nb < _clients.size(); client_nb++)
		{
			Client &client = *_clients[client_nb];
			int client_sd;
			client_sd = client.getSocketDescriptor();
			bool bool_treat = false;
			// std::cout << "client nb = |" << client_nb << "| clients len = |" << _clients.size()<< "| sockets len = |" << _sockets.size() << "|\nCheck FD_ISSET client sd = |" << client_sd << "| bool = |" << client.getReceived() << "|\n";
			if (FD_ISSET(client_sd, &write_set) && client.getReceived() == true)
			{
				Response			response;
				std::vector<char>	message;
				// std::cout << "bef setRequest\n\n";
				
				response.setRequest(Request(client.getRequest(), client.getIP(), client.getServerSocket().getServerConfig()));
				message = response.sendResponse();
				// std::cout << "sendResponse ok\n";
				// https://stackoverflow.com/questions/19172804/crash-when-sending-data-without-connection-via-socket-in-linux
				send(client_sd, &message[0], message.size(), MSG_NOSIGNAL);
				// std::cout << "\nResponse sent !\n" << std::endl;
				
				client.setReceived(false);
				client.getRequest().clear();
				bool_treat = true;
			}
			if (FD_ISSET(client_sd, &read_set) && bool_treat == false)
			{
				int rtn = receiveConnection(client_sd, client.getRequest());
				// std::cout << "rtn receive = |" << rtn << "|\n";
				if (rtn < 0)
				{
					// std::cout << "bad rtn\n";
					close(client_sd);
					// std::cout << "client sd closed rtn\n";
					FD_CLR(client_sd, &master_read_set);
					// std::cout << "fdclr read\n";
					FD_CLR(client_sd, &master_write_set);
					// std::cout << "fdclr write\n";
					if (client_sd == max_sd)
						while (FD_ISSET(max_sd, &master_read_set) == false)
							max_sd -= 1;
					// std::cout << "max sd -=\n";
					delete _clients[client_nb];
					// std::cout << "delete\n";
					_clients.erase(_clients.begin() + client_nb);
					// std::cout << "erase\n";
					client_nb--;
					// std::cout << "client_nb--\n";
				}
				else if (rtn == 0)
				{
					client.setReceived(true);
					// std::cout << "rtn = 0  client nb = |" << client_nb << "| clients len = |" << _clients.size() << "| client sd = |" << client_sd << "| bool = |" << client.getReceived() << "|\n";
				}
			}
		}
	}
}

void Server::endServer(void)
{
	for (size_t client_nb = 0; client_nb < _clients.size(); client_nb++)
	{
		close(_clients[client_nb]->getServerSocket().getSocketDescriptor());
		delete _clients[client_nb];
	}
	for (size_t socket_nb = 0; socket_nb < _sockets.size(); socket_nb++)
	{
		free(this->_sockets[socket_nb]->getBuffer());
		close(_sockets[socket_nb]->getSocketDescriptor());
		delete _sockets[socket_nb];
	}
}
