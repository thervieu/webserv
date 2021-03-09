#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "Socket.hpp"

class Client
{
	private:
		
		Socket			*_socket;
		std::string 	_ip;
		std::string 	_request;
		bool            _received;
		
	public:

		Client(const Client &other);
		Client(Socket *socket, std::string _addr);
		~Client(void);

		void            setReceived(bool _bool);

		Socket			&getSocket(void);
		std::string		getIP(void);
		std::string		&getRequest(void);
		bool            getReceived(void);
};

#endif