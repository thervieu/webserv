#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <sys/stat.h>
# include <ctime>
# include <sys/time.h>
# include <signal.h>
# include <cstdio>
# include <sstream>
# include <ostream>
# include <iostream>
# include <iomanip>

# include <string>
# include <vector>

# include "Config.hpp"

std::vector<std::string>	createVectorLines(std::string file);
std::vector<std::string>	splitSpaces(std::string line);
std::string					readFile(std::string _fileName);
void						signal_handler(int signum);

#define BUFFER_SIZE 10000

#endif