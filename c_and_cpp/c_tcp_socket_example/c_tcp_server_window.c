/*	
	* basic socket program with c on window
	* run as a server
	* compile on window:	gcc -o socket socket.c -lws2_32
*/
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <windows.h>
#include <sys/types.h>

void initWSADATA()
{
	WSADATA wsa;
	printf("\nInitialising Winsock...\n");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d", WSAGetLastError());
        return;
    }
    printf("Initialised Winsock.\n");
}
int initSocket()
{
	int listener_d = socket(AF_INET, SOCK_STREAM, 0);
	if (listener_d == -1)
	{
		printf("can't create socket\n");
		exit(0);
	}
	return listener_d;
}
void bindToPort(int socket, int port)
{
	struct sockaddr_in name;
	name.sin_family = PF_INET;
	name.sin_port = htons(port);
	name.sin_addr.s_addr = htonl(INADDR_ANY);
	int c = bind(socket, (struct sockaddr *) &name, sizeof(name));
	if (c == -1)
	{
		printf("Can't bind to socket\n");
		exit(0);
	}
	if (listen(socket, 10) == -1)
	{
		printf("can't listen\n");
		exit(0);
	}

}
int say(int socket,const char* s)
{
	int result = send(socket, s, strlen(s), 0);
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

void closeConection(int socket)
{
	say(socket, "Bye\r\n");
	closesocket(socket);
}

int main()
{
	initWSADATA();
	int listener_d = initSocket();
	bindToPort(listener_d, 30000);
	struct sockaddr_storage client_addr;
	unsigned int address_size = sizeof(client_addr);
	puts("Waiting for conection");
	char* message = malloc(1000);
	while(1)
	{
		int connect_d = accept(listener_d, (struct sockaddr *)&client_addr, &address_size);
		if (connect_d == -1)
		{
			printf("Can't open secondary socket");
			exit(0);
		}
		hear(connect_d, message, 1000);
		
		closesocket(connect_d);
	}	
	return 0;
}