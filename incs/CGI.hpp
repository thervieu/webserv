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
		std::string _root;

	public:

		CGI(Request & , location, std::string);
		~CGI(void);
		void setRequest(Request &);
		std::string executeCGI(std::string);
		char		**getEnv(std::string);

};

#endif