
#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include "Webserv.hpp"
# include "Request.hpp"
# include "CGI.hpp"
# include <dirent.h>
# include <string.h>
# include <bits/stdc++.h>
# include <algorithm>

# define SEC_PER_MIN 60
# define SEC_PER_HOUR 3600
# define SEC_PER_DAY 86400
# define DAY_PER_YEAR 365.25

class Response
{

	private:

		Request			_request;
		std::string		_encoding_type;
		std::string		_content;
		std::string		_root;
		bool			_cgi;
		int				_code;
		location		_location;

	public:

		Response();
		Response(Response const &ref);
		Response(Request const &request);
		~Response();

		Response			&operator=(Response const &rhs);
		void				setRequest(Request &);
		void				VerifyRedirection(void);
		int					findLocation(std::string cpy);
		std::string			itos(int nb);
		std::string			itos(long nb);
		std::string			getDate(int type);
		std::string			getDay(long day);
		std::string			getNumberDay(long day);
		std::string			getCode(void);
		std::string			getMessage(int code);
		std::string			getLocation(void);
		std::string			getServer(void);
		std::string			getRetryAfter(void);
		std::string			getLastModified(void);
		std::string			getContentLength(void);
		std::string			getContentType(void);
		std::string			getExtension(std::string extension);
		std::string			getContentLanguage(void);
		std::string			getWWWAuthentificate(void);
		std::string 		getTransferEncoding(void);
		std::string 		getAllow(void);
		std::string 		find_error_page(void);
		std::string			findIndex(void);
		location			getLocation(std::string url, std::vector<location> locations);
		bool				IsCGICalled(std::string url);
		bool				isAllowedMethod(void);
		bool				VerifyHost(void) const;
		std::string			upload(void);

		std::vector<char>	MAINResponse(void);
		std::vector<char>	DELETEResponse(void);
		std::vector<char>	OPTIONSResponse(void);
		std::vector<char>	wrongMethodReponse(void);

		std::vector<char>	sendResponse(void);
		std::vector<char>	getContent(void);
		std::vector<char>	getAutoindex(void);
		std::vector<char>	changeContent(std::vector<char> array);
};

#endif
