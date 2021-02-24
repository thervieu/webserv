
#ifndef REPONSE_HPP
# define RESPONSE_HPP

# include "webserv.hpp"
# include "Request.hpp"

class Response
{

	private:

		Request		_request;

	public:

		Response();
		Response(Response const &ref);
		Response(Request const &request);
		~Response();

		Response	&operator=(Response const &rhs);

};


#endif
