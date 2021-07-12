#include "../incs/Config.hpp"

Config::Config()
{}

Config::Config(std::string file)
{
	parseConfig(file);
}

Config &Config::operator=(const Config &other)
{
	if (this != &other)
		_servers = other._servers;
	return (*this);
}

Config::~Config() {}


std::vector<server_info>	Config::getServers(void)
{
	return (_servers);
}

/*
*	returns the line at which the brace it was called on ends 
*/

size_t	getNbLastLine(std::vector<std::string> lines, size_t i)
{
	int nb_open_braces = 0;
	if (lines[i].size() == 1)
		i++;
	std::vector<std::string> line;
	while (i < lines.size())
	{
		line = splitSpaces(lines[i]);
		for (size_t j = 0; j < line.size(); j++)
		{
			if (line[j] == "{")
				nb_open_braces++;
			else if (line[j] == "}")
				nb_open_braces--;
		}
		i++;
		if (nb_open_braces == 0)
			return (i);
	}
	std::cout << "SyntaxError: braces don't match" << std::endl;
	throw std::exception();
}

/*
*	reads through the file lines and each time "server" occurs calls its parsing
*/

void	Config::parseConfig(std::string file)
{
	std::string strFile = readFile(file);
	std::vector<std::string> lines = createVectorLines(strFile);

	size_t i = 0;
	std::vector<std::string>	splittedLine;
	while (i < lines.size())
	{
		splittedLine = splitSpaces(lines[i]);
		if (splittedLine[0] == "server")
		{
			parseServer(lines, i + 1, getNbLastLine(lines, i));
			i = getNbLastLine(lines, i);
		}
		else
		{
			std::cout << "SyntaxError: Unexpected token: " << splittedLine[0] << std::endl;
			throw std::exception();
		}
	}
	if (verifyServers())
		throw std::exception();
	return ;
}

int		Config::verifyServers(void)
{
	for (size_t i = 0; i < _servers.size(); i++)
	{
		if (_servers[i]._root.compare("") == 0 || _servers[i]._host.compare("") == 0
			|| _servers[i]._locations.size() == 0)
		{
			std::cout << "A server must have the following directives: listen, root and at least one location.\n";
			return (1);
		}
		for (size_t j = 0; j < _servers[i]._locations.size(); j++)
		{
			if (_servers[i]._locations[j]._methods.size() == 0)
			{
				std::cout << "A location must have the following directive: method. (autoindex is set at 0)\n";
				return (1);
			}
		}
	}
	return (0);
}
/*
*	verifies that the directive name is valid
*	(is asked to be implemented by the subject)
*/

bool	isDirectiveName(std::string str, const char **names)
{
	size_t i = 0;
	while (names[i])
	{
		if (str == names[i])
			return (true);
		i++;
	}
	return (false);
}

/*
*	verifies the number of words of the directive,
*	that there is an ending semicolon and that the directive name
*	is asked to be implemented by the project
*	exits if a parse_error is occured
*/

void	Config::parseDirective(std::vector<std::string> splittedLine, bool name)
{
	if (splittedLine.size() < 2)
	{
		std::cout << "SyntaxError: Directives should have at least one argument: " << splittedLine[0] << std::endl;
		throw std::exception();
	}
	if (splittedLine[splittedLine.size() - 1][splittedLine[splittedLine.size() - 1].length() - 1] != ';')
	{
		std::cout << "SyntaxError: Missing semicolon on " << splittedLine[0] << " directive" << std::endl;
		throw std::exception();
	}
	if (isDirectiveName(splittedLine[0], (name == true) ? server_directives : location_directives) == false)
	{
		std::cout << "SyntaxError: " << splittedLine[0] << " is not a valid directive" << std::endl;
		throw std::exception();
	}
	return ;
}

/*
*	sets the server directives accordingly
*	adds it to the server vector
*	exits if a parse_error is occured
*/

void	Config::parseServer(std::vector<std::string> lines, size_t start, size_t end)
{
	std::vector<std::string>	splittedLine;

	server_info _server; /* = defaultServer();*/
	while (start < end - 1)
	{
		splittedLine = splitSpaces(lines[start]);
		if (splittedLine[0] == "location")
		{
			_server._locations.push_back(parseLocation(lines, start, getNbLastLine(lines, start)));
			start = getNbLastLine(lines, start);
		}
		else
		{
			parseServerDirectives(_server, splittedLine);
			start++;
		}
	}
	_servers.push_back(_server);
	return ;
}


/*
*	returns the unsigned int format of the string given as argument
*/

size_t	ft_atoi(std::string str)
{
	size_t		i;
	size_t		nb;
	size_t		sign;

	i = 0;
	sign = 0;
	nb = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign++;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		nb = (nb * 10) + (str[i++] - '0');
	if (sign == 1)
		return (-nb);
	else
		return (nb);
}

/*
*	sets the server directives accordingly
*	exits if a parse_error is occured
*/

void	Config::parseServerDirectives(server_info &_server, std::vector<std::string> splittedLine)
{
	parseDirective(splittedLine, true);
	
	splittedLine[splittedLine.size() - 1] = std::string(splittedLine[splittedLine.size() - 1], 0, splittedLine[splittedLine.size() - 1].length() - 1);

	if (splittedLine[0] == server_directives[0])
	{
		if (splittedLine.size() != 3)
		{
			std::cout << "SyntaxError: " << splittedLine[0] << " [port] [host]" << std::endl;
			throw std::exception();
		}
		_server._port = ft_atoi(splittedLine[1]);
		_server._host = splittedLine[2];
	}
	else if (splittedLine[0] == server_directives[1])
	{
		if (splittedLine.size() != 2)
		{
			std::cout << "SyntaxError: " << splittedLine[0] << " [root_path]" << std::endl;
			throw std::exception();
		}
		_server._root = splittedLine[1];
	}
	else if (splittedLine[0] == server_directives[2])
	{
		if (splittedLine.size() < 2)
		{
			std::cout << "SyntaxError: " << splittedLine[0] << " [server_name]" << std::endl;
			throw std::exception();
		}
		for (size_t i = 1; i < splittedLine.size(); i++)
			_server._names.push_back(splittedLine[i]);
	}
	else if (splittedLine[0] == server_directives[3])
	{
		if (splittedLine.size() < 3)
		{
			std::cout << "SyntaxError: " << splittedLine[0] << " [error_number] ... [file_path]" << std::endl;
			throw std::exception();
		}
		for (size_t i = 1; i < splittedLine.size() - 1; i++)
		{
			_server._error_pages.push_back(splittedLine[i]);
			_server._error_pages.push_back(splittedLine[splittedLine.size() - 1]);

		}
	}
	else if (splittedLine[0] == server_directives[4])
		_server._index = splittedLine[1];
	return ;
}

/*
*	sets the directives at default then reads the file
*	and set them accordingly exits if a parse_error is occured
*/

location	Config::parseLocation(std::vector<std::string> lines, size_t start, size_t end)
{
	std::vector<std::string>	splittedLine;

	location _location;
	_location._autoindex = false;
	_location._client_max_body_size = 1024 * 1024;
	splittedLine = splitSpaces(lines[start]);
	if (splittedLine.size() != 3)
		throw std::exception();
	_location._name = splittedLine[1];
	start++;	
	while (start < end - 1)
	{
		splittedLine = splitSpaces(lines[start]);
		parseLocationDirectives(_location, splittedLine);
		start++;
	}
	return (_location);
}

/*
*	self explanatory: returns true is index is on, false if off and exits if wrong argument is given
*/

bool	onOffBool(std::string str)
{
	if (str == "on")
		return (true);
	else if (str == "off")
		return (false);
	std::cout << "Invalid boolean parameter: '" << str << "': should be 'on' or 'off'" << std::endl;
	throw std::exception();
}

/*
*	checks if the method is valid to HTTP 1.1 
*/

bool	isMethod(std::string str)
{
	size_t i = 0;
	while (valid_methods[i])
	{
		if (str == valid_methods[i])
			return (true);
		i++;
	}
	return (false);
}

/*
*	sets the location directives accordingly
*	exits if a parse_error is occured
*/

void	Config::parseLocationDirectives(location &_loc, std::vector<std::string> splittedLine)
{
	char last_char;

	parseDirective(splittedLine, false);
	splittedLine[splittedLine.size() - 1] = std::string(splittedLine[splittedLine.size() - 1], 0, splittedLine[splittedLine.size() - 1].length() - 1);

	if (splittedLine[0] == location_directives[0])
		_loc._root = splittedLine[1];
	else if (splittedLine[0] == location_directives[1])
	{
		for (size_t i = 1; i < splittedLine.size(); ++i)
		{
			if (isMethod(splittedLine[i]) == false)
			{
				std::cout << "Invalid method: " << splittedLine[i] << std::endl;
				throw std::exception();
			}
			else
				_loc._methods.push_back(splittedLine[i]);
		}
	}
	else if (splittedLine[0] == location_directives[2])
		_loc._autoindex = onOffBool(splittedLine[1]);
	else if (splittedLine[0] == location_directives[3])
		_loc._index = splittedLine[1];
	else if (splittedLine[0] == location_directives[4])
		_loc._upload_path = splittedLine[1];
	else if (splittedLine[0] == location_directives[5])
	{
		for (size_t i = 1; i < splittedLine.size(); ++i)
			_loc._cgi_extensions.push_back(splittedLine[i]);
	}
	else if (splittedLine[0] == location_directives[6])
		_loc._cgi_path = splittedLine[1];
	else if (splittedLine[0] == location_directives[7])
	{
		_loc._client_max_body_size = 0;
		if (splittedLine.size() != 2)
		{
			std::cout << "SyntaxError: " << splittedLine[1] << " should in format <dec, K, M or G>" << std::endl;
			throw std::exception();
		}
		_loc._client_max_body_size = ft_atoi(splittedLine[1]);
		last_char = splittedLine[1][splittedLine[1].size() - 1];
		if (last_char == 'K' || last_char == 'k')
			_loc._client_max_body_size *= 1024;
		else if (last_char == 'M' || last_char == 'm')
			_loc._client_max_body_size *= 1024 * 1024;
		else if (last_char == 'G' || last_char == 'g')
			_loc._client_max_body_size *= 1024 * 1024 * 1024;
		else if (!std::isdigit(last_char))
		{
			std::cout << "SyntaxError: " << splittedLine[1] << " should in format <dec, K, M or G>" << std::endl;
			throw std::exception();
		}
	}
	else if (splittedLine[0] == location_directives[8])
	{
		if (splittedLine.size() != 4)
		{
			std::cout << "SyntaxError: " << splittedLine[0] << " directive should be in format 'rewrite ^/old_link$ http://new_link [redirection_type]" << std::endl;
			throw std::exception();
		}
		if (splittedLine[1][0] != '^' || splittedLine[1][1] != '/' || splittedLine[1][splittedLine[1].length() - 1] != '$')
		{
			std::cout << splittedLine[1] << "\n";
			std::cout << "SyntaxError: " << splittedLine[0] << " directive should be in format 'rewrite ^/old_link$ http://new_link [redirection_type]" << std::endl;
			throw std::exception();
		}
		if (splittedLine[3].compare("permanent") != 0 && splittedLine[3].compare("temporary") != 0)
		{
			std::cout << "SyntaxError: " << splittedLine[0] << " directive should in format have 'permanent' or 'temporary as redirection_type" << std::endl;
			throw std::exception();
		}
		_loc._redirections.push_back(splittedLine[1].substr(1, splittedLine[1].length() - 2));
		_loc._redirections.push_back(splittedLine[2]);
		_loc._redirections.push_back(splittedLine[3]);
	}
	return ;
}
