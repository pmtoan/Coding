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
int say(int socket,const char* message)
{
	int result = send(socket, message, strlen(message), 0);
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
	int server = initSocket();
	struct sockaddr_in si;
	memset(&si, 0, sizeof(si));
	si.sin_family = AF_INET;
	si.sin_addr.s_addr = inet_addr("127.0.0.1");
	si.sin_port = htons(30011);
	if (connect(server, (struct sockaddr *) &si, sizeof(si)) == -1)
	{
		puts("Can't connect to server ... ");
		exit(0);
	}
	puts("Connecting with server ... ");
	char* message = malloc(1000);
	while(1)
	{
		hear(server, message, 1000);
		puts(message);
		fgets(message, 1000, stdin);
		say(server, message);
		if (strstr(message, "exit") || strstr(message, "quit"))
		{
			hear(server, message, 1000);
			puts(message);
			puts("Disconnect with server ... ");
			break;
		}
	}
	free(message);
	return 0;
}