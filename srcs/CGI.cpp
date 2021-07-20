#include "../incs/CGI.hpp"

// ressource should be in _loc ?
CGI::CGI(Request & request, location loc, std::string root)
{
	setRequest(request);
	// std::cout << "req root = |" << request.getConfig()._root << "|\n";
	// std::cout << "root = |" << _request.getConfig()._root << "|\n";
	this->_location = loc;
	this->_root = root;
}

void CGI::setRequest(Request & req)
{
	this->_request = req;
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
	env_map["CONTENT_LENGTH"] = _request.getContentLength().length() > 0 ? _request.getContentLength() : "0";
	env_map["CONTENT_TYPE"] = _request.getContentType();
	env_map["GATEWAY_INTERFACE"] = "CGI/1.1";
	if (this->_location._root.empty())
	{
		std::string root = _request.getConfig()._root.substr(0, _request.getConfig()._root.length() - 1);
		
		env_map["PATH_INFO"] = _request.getURL();
		env_map["SCRIPT_NAME"] = root + _location._name + (_location._name[_location._name.length() - 1] == '/' ? "" : "/") + str;
		env_map["SCRIPT_FILENAME"] = root + _location._name + (_location._name[_location._name.length() - 1] == '/' ? "" : "/") + str;
	}
	else
	{
		std::string root = this->_root.substr(1, _root.length() - 1);
		std::string better_pinfo = root;
		
		size_t pos =  0;
		pos = root.rfind("/");
		if (pos != std::string::npos)
			better_pinfo = root.substr(pos, root.size() - pos);

		env_map["PATH_INFO"] = _request.getURL();
		env_map["SCRIPT_NAME"] = root + (root[root.length() - 1] == '/' ? "" : "/") + str;
		env_map["SCRIPT_FILENAME"] = root + (root[root.length() - 1] == '/' ? "" : "/") + str;
	}
	env_map["QUERY_STRING"] = _request.getQuery();
	env_map["REMOTE_ADDR"] = _request.getClientIP();
	env_map["REMOTE_IDENT"] = "";
	env_map["REQUEST_METHOD"] = _request.getMethod();
	env_map["REQUEST_URI"] = _request.getURL();
	env_map["SERVER_NAME"] = _request.getConfig()._host;
	env_map["SERVER_PORT"] = intToString(_request.getConfig()._port);
	env_map["SERVER_PROTOCOL"] = "HTTP/1.1";
	env_map["SERVER_SOFTWARE"] = "Webserv/1.0";

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
	pid_t		pid;
	int			saveStdin;
	int			saveStdout;
	char		**env;
		
	std::string	rtnContent;

	env = this->getEnv(urlFile);

	saveStdin = dup(STDIN_FILENO);
	saveStdout = dup(STDOUT_FILENO);

	FILE	*fIn = tmpfile();
	FILE	*fOut = tmpfile();

	long	fdIn = fileno(fIn);
	long	fdOut = fileno(fOut);
	int		ret = 1;

	std::string root;
	if (this->_location._root.empty())
		root = "." + _request.getConfig()._root.substr(0, _request.getConfig()._root.length() - 1) + _location._name + (_location._name[_location._name.length() - 1] == '/' ? "" : "/");
	else
		root = this->_root + (_root[_root.length() - 1] == '/' ? "" : "/");
	write(fdIn, _request.getContent().c_str(), _request.getContent().size());
	lseek(fdIn, 0, SEEK_SET);

	pid = fork();

	if (pid == -1)
	{
		std::cerr << "Fork crashed." << std::endl;
		return ("Status: 500\r\n\r\n");
	}
	else if (pid == 0)
	{
		char **argv = (char **)malloc(sizeof(char *) * 3);
		
		dup2(fdIn, STDIN_FILENO);
		dup2(fdOut, STDOUT_FILENO);
		
		argv[0] = newStr(root + _location._cgi_path);
		argv[1] = newStr(root + urlFile);
		argv[2] = 0;
		execve((root +  _location._cgi_path).c_str(), argv, env);
		free(argv[0]);
		free(argv[1]);
		free(argv);
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
		throw std::exception();

	return (rtnContent);
}