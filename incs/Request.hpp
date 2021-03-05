
#ifndef REQUEST_HPP
# define REQUEST_HPP

# include "Webserv.hpp"

class Request
{

	private:

		std::string		_accept_charsets;
		std::string		_accept_language;
		std::string		_host;
		std::string		_referer;
		std::string		_user_agent;

	public:

		Request();
		Request(Request const &ref);
		Request(std::string request);
		~Request();

		Request	&operator=(Request const &rhs);

};

#endif
