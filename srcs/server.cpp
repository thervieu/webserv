// Server side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <string>
#define PORT 8080

int main(int argc, char const *argv[])
{
	int					server_fd;
    int					new_socket;
	int					valread;
	struct sockaddr_in	address;
	int					opt = 1;
	int					addrlen = sizeof(address);
	char				*buff;
	std::string			message("Hello from server!");

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0)
	{
		perror("accept");
		exit(EXIT_FAILURE);
	}
	buff = static_cast<char *>(malloc(10000000));
	valread = read(new_socket, buff, 1024);
	std::cout << buff << std::endl;
	send(new_socket , &message.at(0) , message.size(), 0);
	std::cout << "Hello message sent" << std::endl;
	close(new_socket);
	return (0);
}
