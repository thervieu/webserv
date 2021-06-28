#include "../incs/CGI.hpp"

// ressource should be in _loc ?
CGI::CGI(Request & request, location loc)
{
	setRequest(request);
	// std::cout << "req root = |" << request.getConfig()._root << "|\n";
	// std::cout << "root = |" << _request.getConfig()._root << "|\n";
	_location = loc;
}

void CGI::setRequest(Request & req)
{
	_request = req;
}

//if need to del sthg
CGI::~CGI(void)
{
}

std::string intToString(size_t n)
{
	std::ostringstream convert;

	convert << n;
	return (convert.str());
}

char **CGI::getEnv(std::string str)
{
	std::map<std::string, std::string> env_map;

	env_map["REDIRECT_STATUS"] = "200";

	env_map["AUTH_TYPE"] = "";
	env_map["CONTENT_LENGTH"] = _request.getContentLength();
	env_map["CONTENT_TYPE"] = _request.getContentType();
	env_map["GATEWAY_INTERFACE"] = "CGI/1.1";
	
	std::string root = this->_location._root;
	
	// std::cout << "PATH_INFO = " << root + _location._name + str << "\n";
	env_map["PATH_INFO"] = root + _location._name + str;
	env_map["PATH_TRANSLATED"] = root + _location._name + str;
	env_map["QUERY_STRING"] = _request.getQuery();
	env_map["REMOTE_ADDR"] = _request.getClientIP();
	env_map["REMOTE_IDENT"] = "";
	env_map["REQUEST_METHOD"] = _request.getMethod();
	env_map["SCRIPT_NAME"] = _location._cgi_path;
	env_map["SCRIPT_FILENAME"] = "." + root + _location._name + _location._cgi_path;
	env_map["SERVER_NAME"] = _request.getConfig()._host;
	env_map["SERVER_PORT"] = intToString(_request.getConfig()._port);
	env_map["SERVER_PROTOCOL"] = "HTTP/1.1";
	env_map["SERVER_SOFTWARE"] = "Werbserv/1.1";

	char	**env = new char*[env_map.size() + 1];
	int	j = 0;
	for (std::map<std::string, std::string>::const_iterator i = env_map.begin(); i != env_map.end(); i++)
	{
		std::string	element = i->first + "=" + i->second;
		// std::cout << "elt = |" << element << "|\n";
		env[j] = new char[element.size() + 1];
		env[j] = strcpy(env[j], (const char*)element.c_str());
		j++;
	}
	env[j] = NULL;
	return (env);
}

// some helpful links
// https://cmd.inp.nsk.su/old/cmd2/manuals/unix/UNIX_Unleashed/ch20.htm
// https://programmer.help/blogs/implement-simple-web-server-c-language.html
// https://www.classes.cs.uchicago.edu/archive/1999/winter/CS219/projects/project2/project2.html


#include <cerrno>

char *newStr(std::string src)
{
	char *rtn;

	if (!(rtn = (char *)malloc(sizeof(char) * (src.size() + 1))))
		return (0);
	for (size_t i = 0; i < src.size(); ++i)
		rtn[i] = src[i];
	rtn[src.size()] = 0;
	return (rtn);
}

std::string		CGI::executeCGI(std::string urlFile)
{
	int		ret = 1;

	pid_t		pid;
	int			saveStdin;
	int			saveStdout;
	char		**env;
		
	std::string	rtnContent;

	env = getEnv(urlFile);

	saveStdin = dup(STDIN_FILENO);
	saveStdout = dup(STDOUT_FILENO);

	FILE	*fIn = tmpfile();
	FILE	*fOut = tmpfile();

	long	fdIn = fileno(fIn);
	long	fdOut = fileno(fOut);


	saveStdin = dup(STDIN_FILENO);
	saveStdout = dup(STDOUT_FILENO);

	write(fdIn, _request.getContent().c_str(), _request.getContent().size());
	lseek(fdIn, 0, SEEK_SET);

	pid = fork();
	std::string root = this->_location._upload_path;
	char **argv = (char**)malloc(sizeof(char *) * 3);
	argv[0] = newStr("/etc/alternatives/php-cgi");
	argv[1] = newStr("." + root);
	argv[2] = NULL;
	// std::cout << "argv = |" << std::string(argv[0]) << "| |" << std::string(argv[1]) << "|\n";
		

	if (pid == -1)
	{
		std::cerr << "Fork crashed." << std::endl;
		return ("Status: 500\r\n\r\n");
	}
	else if (pid == 0)
	{
		// std::cout << "son process" << "\n";
		char * const * nll = NULL;

		dup2(fdIn, STDIN_FILENO);
		dup2(fdOut, STDOUT_FILENO);
		
		if (_location._cgi_path.substr(_location._cgi_path.rfind("."), 4).compare(".php") == 0)
			execve(argv[0], argv, env);
		else
			execve(("." + this-> _location._cgi_path).c_str(), nll, env);
		// exit(0);
	}
	else
	{
		char	buffer[CGI_BUFFER_SIZE] = {0};

		waitpid(-1, NULL, 0);
		lseek(fdOut, 0, SEEK_SET);

		ret = 1;
		while (ret > 0)
		{
			memset(buffer, 0, CGI_BUFFER_SIZE);
			ret = read(fdOut, buffer, CGI_BUFFER_SIZE - 1);
			rtnContent += buffer;
		}
	}

	dup2(saveStdin, STDIN_FILENO);
	dup2(saveStdout, STDOUT_FILENO);
	fclose(fIn);
	fclose(fOut);
	close(fdIn);
	close(fdOut);
	close(saveStdin);
	close(saveStdout);

	for (size_t i = 0; env[i]; i++)
		delete[] env[i];
	delete[] env;

	if (!pid)
		exit(0);

	return (rtnContent);
}