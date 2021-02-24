
#ifndef REPONSE_HPP
# define RESPONSE_HPP

# include "webserv.hpp"
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

	public:

		Response();
		Response(Response const &ref);
		Response(Request const &request);
		~Response();

		Response	&operator=(Response const &rhs);
		std::string	getDate(void);
		std::string	getDay(long day);
		std::string	getNumberDay(long day);
};


#endif
