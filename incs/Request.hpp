
#ifndef REQUEST_HPP
# define REQUEST_HPP

# include "Webserv.hpp"

class Request
{

	private:

		std::vector<std::string>	_arguments;
		server_info		_config;
		std::string		_request;
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
		Request(std::string request, server_info config);
		~Request();

		Request			&operator=(Request const &rhs);
		int				setHeader(std::string str);
		void			setAcceptCharsets(std::string header);
		void			setAcceptLanguage(std::string header);
		void			setHost(std::string header);
		void			setReferer(std::string header);
		void			setUserAgent(std::string header);
		void			setURI(std::string str);
		std::string		getAcceptCharsets(void) const;
		std::string		getAcceptLanguage(void) const;
		std::string		getHost(void) const;
		std::string		getReferer(void) const;
		std::string		getUserAgent(void) const;
		std::string		getMethod(void) const;
		std::string		getURI(void) const;
		std::string		getHTTPVersion(void) const;
		std::string		getRequest(void) const;
		server_info		getConfig(void) const;
		int				getUnknown(void) const;
		void			parsing(std::string str);
};

#endif
