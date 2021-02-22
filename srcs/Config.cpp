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

std::vector<server>	Config::getServers(void)
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
		std::cout << "SyntaxError: Directives should have at least one argument" << std::endl;
		exit(1);
	}
	if (splittedLine[splittedLine.size() - 1][splittedLine[splittedLine.size() - 1].length() - 1] != ';')
	{
		std::cout << "SyntaxError: Missing semicolon on " << splittedLine[0] << " directive" << std::endl;
		exit(1);
	}
	if (isDirectiveName(splittedLine[0], (name == true) ? server_directives : location_directives) == false)
	{
		std::cout << name << std::endl;
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

	server _server; /* = defaultServer();*/
	while (start < end)
	{
		splittedLine = splitSpaces(lines[start]);
		if (splittedLine[0] == "location")
			start = parseLocation(lines, start + 1, getNbLastLine(lines, start));
		else
			parseServerDirectives(_server, splittedLine);
		start++;
	}
	_servers.push_back(_server);
	return (end + 1);
}

/*
*	sets the server directives accordingly
*	exits if a parse_error is occured
*/

void	Config::parseServerDirectives(server _server, std::vector<std::string> splittedLine)
{
	parseDirective(splittedLine, true);
	if (splittedLine[0] == server_directives[0])
	{
		if (splittedLine.size() != 3)
		{
			std::cout << "SyntaxError: " << splittedLine[0] << " [port] [host]" << std::endl;
			exit(1);
		}
		//_server.port = atoi(splittedLine[1])
		_server._host = splittedLine[2];
	}
	else if (splittedLine[0] == server_directives[1])
	{
		if (splittedLine.size() != 2)
		{
			std::cout << "SyntaxError: " << splittedLine[0] << " [root_path]" << std::endl;
			exit(1);
		}
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
		if (splittedLine.size() != 2)
		{
			std::cout << "SyntaxError: " << splittedLine[0] << " [server_name]" << std::endl;
			exit(1);
		}
		for (size_t i = 1; i < splittedLine.size(); i++)
			_server._names.push_back(splittedLine[i]);
	}
	return ;
}

/*
*	sets the directives at default then reads the file
*	and set them accordingly exits if a parse_error is occured
*/

size_t	Config::parseLocation(std::vector<std::string> lines, size_t start, size_t end)
{
	std::vector<std::string>	splittedLine;

	location _location; /* = defaultLocation();*/
	while (start < end - 1)
	{
		splittedLine = splitSpaces(lines[start]);
		parseLocationDirectives(_location, splittedLine);
		start++;
	}
	return (end + 1);
}

/*
*	sets the location directives accordingly
*	exits if a parse_error is occured
*/

// WIP
void	Config::parseLocationDirectives(location _location, std::vector<std::string> splittedLine)
{
	parseDirective(splittedLine, false);
	(void)_location;
	(void)splittedLine;
}
