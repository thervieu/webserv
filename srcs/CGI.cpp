#include "CGI.hpp"

// ressource should be in _loc ?
CGI::CGI(Request request, location loc)
{
	_request = request;
	_location = loc;
}

//if need to del sthg
CGI::~CGI(void)
{
}

char **CGI::getEnv(void)
{
	std::map<std::string, std::string> env;
	map['AUTH_TYPE'] = 
	map['CONTENT_LENGTH'] = 
	map['CONTENT_TYPE'] = 
	map['GATEWAY_INTERFACE'] = "CGI/1.1";
	map['PATH_INFO'] = _request.getURL(); // root + loc
	map['PATH_TRANSLATED'] = _request.getURL(); // root + loc
	map['QUERY_STRING'] = _request.getQuery();
	map['REMOTE_ADDR'] = _request.getClientIP();
	map['REMOTE_HOST'] = 
	map['REMOTE_IDENT'] = 
	map['REMOTE_USER'] = 
	map['REQUEST_METHOD'] = _request.getMethod();
	map['SCRIPT_NAME'] = 
	map['SERVER_NAME'] = _request.getConfig()._host;
	map['SERVER_PORT'] = _request.getConfig()._port;
	map['SERVER_PROTOCOL'] = "HTTP/1.1"
	map['SERVER_SOFTWARE'] = "Werbserv/1.1";
	


}

// some helpful links
// https://cmd.inp.nsk.su/old/cmd2/manuals/unix/UNIX_Unleashed/ch20.htm
// https://programmer.help/blogs/implement-simple-web-server-c-language.html
// https://www.classes.cs.uchicago.edu/archive/1999/winter/CS219/projects/project2/project2.html
std::string executeCGI(void)
{
	int _pipe[2];
	pid_t pid;
	int status;

	//get args into a char **

	char **env = getArgsEnv();

	if (pipe(_pipe) != 0)
	{
		std::cout << "pipe failed" << std::endl;
		exit(1);
	}
	
	pid = fork();

	if (pid == -1)
	{
		std::cout << "fork failed" << std::endl;
		exit(1);
	}
	if (pid == 0)
	{
		close (_pipe[1]);
		dup2(_pipe[0], 0);

		int _file_fd;

		_file_fd = open("/tmp/cgi_file", O_RDWR | O_CREAT | O_TRUNC | O_IRUSR | O_IWUSR)
		if (_file_fd == -1)
		{
			std::cout << "open failed" << std::endl;
			exit(1);
		}
		dup2(_file_fd, 1);
		dup2(_file_fd, 2);
		//int res = 0
		//res = execve(_full_path, exec_and_args, args);
		if (res == -1)
		{
			std::cout << "execve failed" << std::endl;
			exit(1);
		}
		close (_file_fd);
		close (_pipe[0]);
		// free args
		exit(1);
	}
	else
	{
		close(_pipe[0]);
		write(_pipe[1], content, content.length());
		close(_pipe[1]);
		waitpid(-1, NULL, 0); // wait for any child to die but since we only have one it's ok
		//free args
	}
	return (readFile("tmp/cgi_file"));
}
