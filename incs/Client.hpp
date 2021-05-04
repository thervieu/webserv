#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "Socket.hpp"

class Client: public Socket
{
	private:
		
		Socket			*_serverSocket;
		int				_clientFd;
		std::string 	_ip;
		std::string 	_request;
		bool            _received;
		
	public:

		Client(Socket *socket, std::string _addr, int clientFd);
		Client(const Client &other);

		virtual ~Client(void);

		void            setReceived(bool _bool);

		Socket			&getServerSocket(void);
		int				getClientFd(void);

		std::string		getIP(void);
		std::string		&getRequest(void);
		bool            getReceived(void);
};

#endif