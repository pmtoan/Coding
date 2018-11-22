/*	
	* basic socket program with c on window
	* run as a client
	* compile on window:	gcc -o client client.c -lws2_32
*/
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void initWSADATA()
{
	WSADATA wsa;
	printf("\nInitialising Winsock...\n");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
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
int connectTo(int socket, int port)
{
	struct sockaddr_in si;
	memset(&si, 0, sizeof(si));
	si.sin_family = PF_INET;
	si.sin_addr.s_addr = inet_addr("127.0.0.1");
	si.sin_port = htons(port);
	return connect(socket, (struct sockaddr *) &si, sizeof(si));
}
int say(int socket,const char* s)
{
	int result = send(socket, s, strlen(s), 0);
	if (result == -1)
	{
		printf("Error while talking to server\n");
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
	initWSADATA();
	int listener_d = initSocket();
	int connection = connectTo(listener_d, 30000);
	if (connection == -1)
	{
		puts("Can't connect with server ... ");
		exit(0);
	}
	puts("Connecting with server ... ");
	char* message = malloc(1000);
	while(1)
	{
		hear(listener_d, message, 1000);
		puts(message);
		fgets(message, 1000, stdin);
		say(listener_d, message);
		if (strstr(message, "exit") || strstr(message, "quit"))
		{
			hear(listener_d, message, 1000);
			puts(message);
			puts("Disconnect with server ... ");
			break;
		}
	}
	free(message);
	return 0;
}