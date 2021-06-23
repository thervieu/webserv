#ifndef CGI_HPP
# define CGI_HPP

# include "Config.hpp"
# include "Request.hpp"
# include <string>
# include <string.h>
# include <sys/wait.h>

# define CGI_BUFFER_SIZE 1000

class CGI
{
	private:

		Request _request;
		location _location;

	public:

		CGI(Request & , location);
		~CGI(void);
		void setRequest(Request &);
		std::string executeCGI(std::string);
		char		**getEnv(void);

};

#endif