#include "../incs/Config.hpp"

Config::Config() {}

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
	exit(1);
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
			i = parseServer(lines, i + 1, getNbLastLine(lines, i));
		else
		{
			std::cout << "SyntaxError: Unexpected token: " << splittedLine[0] << std::endl;
			exit(0);
		}
		i++;
	}
	return ;
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
		exit(1);
	}
	if (splittedLine[splittedLine.size() - 1][splittedLine[splittedLine.size() - 1].length() - 1] != ';')
	{
		std::cout << "SyntaxError: Missing semicolon on " << splittedLine[0] << " directive" << std::endl;
		exit(1);
	}
	if (isDirectiveName(splittedLine[0], (name == true) ? server_directives : location_directives) == false)
	{
		std::cout << "SyntaxError: " << splittedLine[0] << " is not a valid directive" << std::endl;
		exit(1);
	}
	return ;
}

/*
*	sets the server directives accordingly
*	adds it to the server vector
*	exits if a parse_error is occured
*/

size_t	Config::parseServer(std::vector<std::string> lines, size_t start, size_t end)
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
	return (end + 1);
}


/*
*	returns the unsigned int format of the string given as argument
*/

size_t	stringToUnsignedInt(std::string str)
{
	std::istringstream stream(str);
	size_t uInt;

	stream >> uInt;
	return (uInt);
}

/*
*	sets the server directives accordingly
*	exits if a parse_error is occured
*/

void	Config::parseServerDirectives(server_info _server, std::vector<std::string> splittedLine)
{
	char last_char;

	parseDirective(splittedLine, true);
	
	splittedLine[splittedLine.size() - 1] = std::string(splittedLine[splittedLine.size() - 1], 0, splittedLine[splittedLine.size() - 1].length() - 1);
	
	if (splittedLine[0] == server_directives[0])
	{
		if (splittedLine.size() != 3)
		{
			std::cout << "SyntaxError: " << splittedLine[0] << " [port] [host]" << std::endl;
			exit(1);
		}
		_server._port = stringToUnsignedInt(splittedLine[1]);
		_server._host = splittedLine[2];
	}
	else if (splittedLine[0] == server_directives[1])
	{
		if (splittedLine.size() != 2)
		{
			std::cout << "SyntaxError: " << splittedLine[0] << " [root_path]" << std::endl;
			exit(1);
		}
		_server._root = splittedLine[1];
	}
	else if (splittedLine[0] == server_directives[2])
	{
		if (splittedLine.size() < 2)
		{
			std::cout << "SyntaxError: " << splittedLine[0] << " [server_name]" << std::endl;
			exit(1);
		}
		for (size_t i = 1; i < splittedLine.size(); i++)
			_server._names.push_back(splittedLine[i]);
	}
	else if (splittedLine[0] == server_directives[2])
	{
		if (splittedLine.size() < 3)
		{
			std::cout << "SyntaxError: " << splittedLine[0] << " [error_number] ... [file_path]" << std::endl;
			exit(1);
		}
		for (size_t i = 1; i < splittedLine.size() - 1; i++)
		{
			_server._error_pages.push_back(splittedLine[i]);
			_server._error_pages.push_back(splittedLine[splittedLine.size() - 1]);

		}
	}
	else if (splittedLine[0] == location_directives[3])
		_server._index = splittedLine[1];
	else if (splittedLine[0] == location_directives[4])
	{
		if (splittedLine.size() != 2)
		{
			std::cout << "SyntaxError: " << splittedLine[1] << " should in format <dec, K, M or G>" << std::endl;
			exit(1);
		}
		_server._client_max_body_size = stringToUnsignedInt(splittedLine[1]);
		last_char = splittedLine[1][splittedLine[1].size() - 1];
		if (last_char == 'K' || last_char == 'k')
			_server._client_max_body_size *= 1024;
		else if (last_char == 'M' || last_char == 'm')
			_server._client_max_body_size *= 1024 * 1024;
		else if (last_char == 'G' || last_char == 'G')
			_server._client_max_body_size *= 1024 * 1024 * 1024;
		else if (!std::isdigit(last_char))
		{
			std::cout << "SyntaxError: " << splittedLine[1] << " should in format <dec, K, M or G>" << std::endl;
			exit(1);
		}
	}
	return ;
}

/*
*	sets the directives at default then reads the file
*	and set them accordingly exits if a parse_error is occured
*/

location	Config::parseLocation(std::vector<std::string> lines, size_t start, size_t end)
{
	std::vector<std::string>	splittedLine;

	location _location; /* = defaultLocation();*/
	splittedLine = splitSpaces(lines[start]);
	if (splittedLine.size() != 3)
		exit(1);
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
	exit(1);
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
				exit(1);
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
		_loc._upload = onOffBool(splittedLine[1]);
	else if (splittedLine[0] == location_directives[5])
		_loc._upload_path = splittedLine[1];
	else if (splittedLine[0] == location_directives[6])
		_loc._upload_cleanup = stringToUnsignedInt(splittedLine[1]);
	else if (splittedLine[0] == location_directives[7])
	{
		for (size_t i = 1; i < splittedLine.size(); ++i)
			_loc._cgi_extensions.push_back(splittedLine[i]);
	}
	else if (splittedLine[0] == location_directives[8])
		_loc._cgi_path = splittedLine[1];
	else if (splittedLine[0] == location_directives[9])
	{
		if (splittedLine.size() != 2)
		{
			std::cout << "SyntaxError: " << splittedLine[1] << " should in format <dec, K, M or G>" << std::endl;
			exit(1);
		}
		_loc._client_max_body_size = stringToUnsignedInt(splittedLine[1]);
		last_char = splittedLine[1][splittedLine[1].size() - 1];
		if (last_char == 'K' || last_char == 'k')
			_loc._client_max_body_size *= 1024;
		else if (last_char == 'M' || last_char == 'm')
			_loc._client_max_body_size *= 1024 * 1024;
		else if (last_char == 'G' || last_char == 'G')
			_loc._client_max_body_size *= 1024 * 1024 * 1024;
		else if (!std::isdigit(last_char))
		{
			std::cout << "SyntaxError: " << splittedLine[1] << " should in format <dec, K, M or G>" << std::endl;
			exit(1);
		}
	}
	return ;
}
