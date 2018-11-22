#include "stdio.h"
#include "signal.h"

int loop = 1;

void on_sig()
{
	printf("Program exit\n");
	loop = 0;
}

int main(int argc, char const *argv[])
{
	signal(SIGTERM, on_sig);
	while(loop)
	{

	}
	return 0;
}