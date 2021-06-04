#include "../incs/Webserv.hpp"

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		std::cout << "ctrl-c detected, closing application..." << std::endl;
		throw std::exception();
	}
	if (signum == SIGQUIT)
	{
		std::cout << "ctrl-d detected, closing application..." << std::endl;
		throw std::exception();
	}
}
