#include "CGI.hpp"

// ressource should be in _loc ?
CGI::CGI(std::string path, std::string ressource_path, location loc)
{
	_full_path = path;
	_ressource_path = ressource_path;
	_loc = loc;
}

//if need to del sthg
CGI::~CGI(void)
{
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
		//free args
	}
	return (readFile("tmp/cgi_file"));
}
