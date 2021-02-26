
#ifndef REPONSE_HPP
# define RESPONSE_HPP

# include "Webserv.hpp"
# include "Request.hpp"
# include <ctime>
# include <sys/time.h>

# define SEC_PER_MIN 60
# define SEC_PER_HOUR 3600
# define SEC_PER_DAY 86400
# define DAY_PER_YEAR 365.25

class Response
{

	private:

		Request			_request;
		std::string		_response;
		int				_code;

	public:

		Response();
		Response(Response const &ref);
		Response(Request const &request);
		~Response();

		Response	&operator=(Response const &rhs);
		std::string	getDate(int type);
		std::string	getDay(long day);
		std::string	getNumberDay(long day);
		std::string	getCode(void);
		std::string	getMessage(int code);
		std::string	getLocation(std::string url);
		std::string	getServer(void);
		std::string	getRetryAfter(void);
		std::string	getLastModified(const char *file);
		std::string	getContentLength(const char *file);
		std::string	getContentType(std::string file);
		std::string	getExtension(std::string extension);
		std::string	getContentLanguage(void);
};


#endif
