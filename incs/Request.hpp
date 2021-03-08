
#ifndef REQUEST_HPP
# define REQUEST_HPP

# include "Webserv.hpp"

class Request
{

	private:

		std::string		_method;
		std::string		_url;
		std::string		_http_version;
		std::string		_accept_charsets;
		std::string		_accept_language;
		std::string		_host;
		std::string		_referer;
		std::string		_user_agent;
		int				_unknown;

	public:

		Request();
		Request(Request const &ref);
		Request(std::string request);
		~Request();

		Request	&operator=(Request const &rhs);
		void	setAcceptCharsets(std::string header);
		void	setAcceptLanguage(std::string header);
		void	setHost(std::string header);
		void	setReferer(std::string header);
		void	setUserAgent(std::string header);
		void	parsing(std::string main_string);
};

#endif
