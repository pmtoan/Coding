#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

int initSocket()
{
	int s;
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0)
	{
		puts("Error initialize socket ...");
		exit(0);
	}
	puts("Socket have been created ... ");
	return s;
}

int bindToPort(int socket, int port)
{
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(port);
    if ((bind(socket, (struct sockaddr*)&server_addr,sizeof(server_addr))) < 0) 
    {
    	puts("Error while bind to port ... ");
        return -1;
    }
    return 1;
}

void listenClient(int socket, int number)
{
	listen(socket, number);
}

int say(int socket,const char* message)
{
	int result = send(socket, message, strlen(message), 0);
	if (result == -1)
	{
		printf("Error while talking to client\n");
	}
	return result;
}
int hear(int socket, char *buf, int len)
{
	char *s = buf;
	int slen = len;
	int c = recv(socket, s, slen, 0);
	if (c < 0)
		return c;
	else if (c == 0)
		buf[0] = '\0';
	else
		s[c-1]='\0';
	return len - slen;
}

int main()
{
	int server = initSocket();
	if (bindToPort(server, 30011) == -1)
		exit(-1);
	listenClient(server, 1);
	struct sockaddr_storage client_addr;
	unsigned int address_size = sizeof(client_addr);
	puts("Waiting for conection ... ");
	int connect;
	char* message = malloc(1000);
	while(1)
	{
		connect = accept(server,(struct sockaddr *)&client_addr,&address_size);
		if (connect < 0)
		{
			puts("Error step accept ... ");
			exit(-1);
		}
		puts("Connecting with client ... ");
		say(connect, "You are connecting with server ... \n");
		while (1)
		{
			hear(connect, message, 1000);
			if (strstr(message, "exit") || strstr(message, "quit"))
			{
				puts("Disconnect with client ... ");
				say(connect, "goodbye!\r\n");
				close(connect);
				break;
			}
			printf("%s\n", message);
			fgets(message, 1000, stdin);
			say(connect, message);
		}
	}
	free(message);
	return 0;
}