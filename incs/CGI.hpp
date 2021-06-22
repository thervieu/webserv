#ifndef CGI_HPP
# define CGI_HPP

# include "Config.hpp"
# include "Request.hpp"

class CGI
{
	private:

		Request _request;
		location _loc;

	public:

		CGI(std::string, std::string, location);
		~CGI(void);
		std::string executeCGI(void);
		std::string getArgs(void);

};

#endif