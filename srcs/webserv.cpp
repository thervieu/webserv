#include "../incs/webserv.hpp"

bool		isSkippable(std::string line)
{
	if (line[0] == '\n' || line[0] == '#')
		return (true);
	return (false);
}

std::vector<std::string>	breakDown(std::vector<std::string> previousVector, std::string line)
{
	size_t	i = 0;
	size_t	j;
	std::vector<std::string> newVector = previousVector;
	while (line[i])
	{
		j = 0;
		while (std::isspace(line[i]))
			i++;
		while (line[i + j] && !std::isspace(line[i + j]) && line[i + j] != '#')
			j++;
		if (!line[i + j] || line[i + j] == '#')
		{
			newVector.push_back(std::string(line, i, j));
			break;
		}
		newVector.push_back(std::string(line, i, j));
		i = i + j + 1;
	}
	return (newVector);
}

int			main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Format: ./webserv [path_to_configuration_file]" << std::endl;
		return (1);
	}
	std::ifstream config_file(av[1]);

	if (!config_file)
	{
		std::cout << "Could not open " << av[1] << std::endl;
		return (1);
	}

	std::string line;
	std::vector<std::string> _configFile;
	while (getline(config_file, line))
	{
		if (isSkippable(line))
			continue;
		_configFile = breakDown(_configFile, line);
	}
	size_t size = _configFile.size();
	size_t i = 0;
	while (i < size)
	{
		std::cout << _configFile[i] << " - ";
		i++;
	}
	return (0);
}