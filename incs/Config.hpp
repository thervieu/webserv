#ifndef CONFIG_HPP
# define CONFIG_HPP

# include <map>

# include "Webserv.hpp"

class location
{
	public:

		std::vector<std::string>	_cgi_extensions;
		std::vector<std::string>	_redirections;
		std::vector<std::string>	_methods;
		std::string					_name;
		std::string					_index;
		std::string					_cgi_path;
		std::string					_cgi_extension;
		std::string					_root;
		std::string					_upload_path;
		size_t						_upload_cleanup;
		size_t						_client_max_body_size;
		bool						_autoindex;
		bool						_upload;
};

class server_info
{
	public:

		std::string						_root;
		std::string						_index;
		std::string						_host;
		std::vector<std::string>		_names;
		std::vector<std::string>		_error_pages;
		std::vector<location>			_locations;
		size_t							_client_max_body_size;
		size_t							_port;
};

class Config
{
	private:

		std::vector<server_info>	_servers;
		int					verifyServers(void);
		void				parseServer(std::vector<std::string> vectorFile, size_t start, size_t end);
		location			parseLocation(std::vector<std::string> vectorFile, size_t start, size_t end);
		void				parseConfig(std::string file);
		void				parseDirective(std::vector<std::string> splittedLine, bool name);
		void				parseServerDirectives(server_info &_server, std::vector<std::string> splittedLine);
		void				parseLocationDirectives(location &_loc, std::vector<std::string> splittedLine);

	public:

		Config(void);
		Config(std::string file);
		~Config(void);
		Config				&operator=(const Config &other);
		std::vector<server_info>	getServers(void);

};

static const char * server_directives[] =
{
	"listen",
	"root",
	"server_name",
	"error_page",
	"index",
	NULL
};

static const char * valid_methods[] =
{
	"GET",
	"HEAD",
	"POST",
	"DELETE",
	"OPTIONS",
	NULL
};

static const char * location_directives[] =
{
	"root",
	"method",
	"autoindex",
	"index",
	"upload_path",
	"cgi_extension",
	"cgi_path",
	"client_max_body_size",
	"rewrite",
	NULL
};

#endif
