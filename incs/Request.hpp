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
		std::string		_clientIP;
		std::string		_query;
		std::string		_content;
		std::string		_contentLength;
		std::string		_contentType;
		int				_unknown;

	public:

		Request();
		Request(Request const &ref);
		Request(std::string request, std::string client_ip, server_info config,  bool chunked);
		~Request();

		Request			&operator=(Request const &rhs);
		void			setConfig(server_info config);
		int				setHeader(std::string str);
		void			setAcceptCharsets(std::string header);
		void			setAcceptLanguage(std::string header);
		void			setHost(std::string header);
		void			setReferer(std::string header);
		void			setUserAgent(std::string header);
		void			setURL(std::string str);
		void			setCLientIP(std::string str);
		void			setContentLength(std::string str);
		void			setContentType(std::string str);
		std::vector<std::string>	getArguments(void) const;
		void			ParseBody(std::string body, bool chunked);
		std::string		getAcceptCharsets(void) const;
		std::string		getAcceptLanguage(void) const;
		std::string		getHost(void) const;
		std::string		getReferer(void) const;
		std::string		getUserAgent(void) const;
		std::string		getMethod(void) const;
		std::string		getURL(void) const;
		std::string		getHTTPVersion(void) const;
		std::string		getRequest(void) const;
		std::string		getClientIP(void) const;
		std::string		getContent(void) const;
		std::string		getQuery(void) const;
		void			setContent(std::string	content);
		std::string		getContentLength(void) const;
		std::string		getContentType(void) const;
		server_info		getConfig(void) const;
		int				getUnknown(void) const;
		size_t			hexatoi(std::string) const;
		void			parsing(std::string str, bool chunked);
};

#endif
