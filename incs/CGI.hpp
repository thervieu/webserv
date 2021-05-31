#ifndef CGI_HPP
# define CGI_HPP

# include "Config.hpp"
# include "Request.hpp"

class CGI
{
	private:

		std::string _full_path;
		std::string _ressource_path;
		location _loc;

	public:

		CGI(std::string, std::string, location);
		~CGI(void);
		std::string executeCGI(void);
		std::string getArgs(void);

};

#endif