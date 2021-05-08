#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>	//inet_addr
#include <unistd.h>

void func(int socket_desc)
{
	char buff[50];
	int n;
	for (;;)
	{
		bzero(buff, sizeof(buff));
		printf("Please enter message: ");
		n = 0;
		while ((buff[n++] = getchar()) != '\n');

		write(socket_desc, buff, sizeof(buff));
		bzero(buff, sizeof(buff));
		read(socket_desc, buff, sizeof(buff));
		printf("From Server : %s", buff);
		if ((strncmp(buff, "exit", 4)) == 0)
		{
			printf("Client exit...\n");
		break;
		}
	}
}

int main()
{
	int socket_desc, conn;
	struct sockaddr_in server, client; 
	
	//Create socket 
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket...\n");
		exit(0);
	}
	else
		printf("Socket successfully created...\n");
	bzero(&server, sizeof(server));


	//Assign IP, PORT
	server.sin_family = AF_INET;
	server.sin_port = htons(8888);
	server.sin_addr.s_addr = inet_addr("192.168.56.103");

	//Connect client socket to server socket
	if (connect(socket_desc , (struct sockaddr *)&server, sizeof(server)) !=0)
	{
		printf("Connection with server failed...\n");
		exit(0);
	}

	else
		printf("Connected to the server...\n");

	
	//Func for chat
	func(socket_desc);

	//Close socket
	close(socket_desc);

}
