// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <iostream>
# define PORT 8080

int main(int argc, char const *argv[])
{
	int					sock = 0;
	int					valread;
	struct sockaddr_in	serv_addr;
	std::string			message("GET /index.html HTTP/1.1\nUser-Agent: Ubuntu/18.04.5 LTS 64-bits\nHost: http://localhost:8080\nAccept-Language: en-US\nAccept-Charset: utf-8");
	std::string			message2("GET /indexlol.html HTTP/1.1\n   \n\n\n      \n    User-Agent: bonjour\n\n\n");
	char				buffer[10240] = {0};
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return (-1);
	}
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	// Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
	{
		printf("\nInvalid address/ Address not supported \n");
		return (-1);
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\nConnection Failed \n");
		return (-1);
	}
	send(sock, (char *)&message.at(0), message.size(), 0);
	std::cout << "GET message sent" << std::endl << std::endl;
	valread = read(sock , buffer, 10240);
	std::cout << buffer << std::endl;

	// send(sock, (char *)&message2.at(0), message2.size(), 0);
	// std::cout << "404 message sent" << std::endl << std::endl;
	// valread = read(sock , buffer, 10240);
	// std::cout << buffer << std::endl;
	// return (0);
}
