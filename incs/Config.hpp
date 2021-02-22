#ifndef CONFIG_HPP
# define CONFIG_HPP

# include "webserv.hpp"

struct location
{
	std::string	_root;
	std::vector<std::string> _methods;
	bool		_autoindex;
	std::vector<std::string> _indexes;
	bool		_upload;
	std::string	_upload_path;
	std::vector<std::string> _file_extensions;
	std::vector<std::string> _cgi_path;
	size_t		_client_max_body_size;
};

struct	server
{
	size_t		_port;
	std::string	_root;
	std::string	_host;
	std::vector<std::string>	_names;
	std::vector<std::string>	_error_pages;
	std::vector<location>		_locations;
};

class Config
{
	private:

		std::vector<server> _servers;
		void	parseConfig(std::string file);
		void	parseDirective(std::vector<std::string> splittedLine, bool name);
		size_t	parseServer(std::vector<std::string> vectorFile, size_t start, size_t end);
		void	parseServerDirectives(server _server, std::vector<std::string> splittedLine);
		size_t	parseLocation(std::vector<std::string> vectorFile, size_t start, size_t end);
		void	parseLocationDirectives(location _location, std::vector<std::string> splittedLine);

	public:

		Config(void);
		Config(std::string file);
		Config &operator=(const Config &other);
		~Config(void);
		std::vector<server>	getServers(void);

};

static const char * server_directives[] =
{
	"listen",
	"root",
	"server_name",
	"error_page",
	NULL
};

static const char * location_directives[] =
{
	"root",
	"method",
	"autoindex",
	"index",
	"upload_enable",
	"upload_path",
	"cgi_extension",
	"cgi_path",
	"client_max_body_size",
	NULL
};

#endif