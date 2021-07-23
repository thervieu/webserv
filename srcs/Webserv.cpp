#include "../incs/Webserv.hpp"
#include "../incs/Server.hpp"
#include "../incs/Response.hpp"

bool		isSkippable(std::string line)
{
	if (line[0] == '\n' || line[0] == '#')
		return (true);
	return (false);
}

std::string		readFile(std::string _fileName)
{
	char buffer[BUFFER_SIZE + 1];
	std::string rtn("");
	int rtn_value;
	int fd;

	fd = open(_fileName.c_str(), O_RDONLY);
	if (fd < -1)
	{
		std::cout << "Error: couldn't open " << _fileName << std::endl;
		throw std::exception();
	}
	while ((rtn_value = read(fd, &buffer, BUFFER_SIZE)) > 0)
	{
		rtn += buffer;
	}
	if (rtn_value < 0)
	{
		std::cout << "Error: problem when reading " << _fileName << std::endl;
		throw std::exception();
	}
	close(fd);
	return (rtn);
}

std::vector<std::string>	splitSpaces(std::string line)
{
	std::vector<std::string>	rtn_vector;
	int i = 0;
	int j;

	while (line[i])
	{
		j = 0;
		while (std::isspace(line[i]))
			i++;
		while (line[i + j] && !std::isspace(line[i + j]))
			j++;
		if (j != 0)
			rtn_vector.push_back(std::string(line, i, j));
		if (!line[i + j])
			break;
		i = i + j + 1;
	}
	return (rtn_vector);
}

std::vector<std::string>	createVectorLines(std::string file)
{
	std::vector<std::string> rtn;
	size_t	i = 0;
	size_t	j;
	while (file[i])
	{
		j = 0;
		if (file[i] == '\n')
			i++;
		while (std::isspace(file[i]))
			i++;
		while (file[i + j] && file[i + j] != '\n' && file[i + j] != '#')
			j++;
		if (j != 0)
			rtn.push_back(std::string(file, i, j));
		if (!file[i + j])
			break;
		else if (file[i + j] == '#')
			while (file[i + j] && file[i + j] != '\n')
				j++;
		i = i + j + 1;
	}
	return (rtn);
}

int			main(int ac, char **av)
{
	std::string config_file;

	if (ac == 1)
	{
		config_file = "./confs/default_configuration.conf";
		std::cout << "since no configuration file was given as first argument, we will use default_configuration.conf\n";
	}
	else if (ac == 2)
		config_file = av[1];
	else
	{
		std::cout << "Format: ./webserv [path_to_configuration_file]" << std::endl;
		return (1);
	}
	try
	{
		Config		config(config_file);
		Server		server;

		signal(SIGINT, signal_handler);
		signal(SIGQUIT, signal_handler);
		try
		{
			for (size_t i = 0; i < config.getServers().size(); i++)
				server.addSocket(new Socket(config.getServers()[i]));
			server.select_loop();
		}
		catch(const std::exception& e)
		{
			std::cerr << "Server closing now" << std::endl;
			server.endServer();
			return (1);
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << "Config Error, closing now" << std::endl;
		return (1);
	}
	return (0);
}
