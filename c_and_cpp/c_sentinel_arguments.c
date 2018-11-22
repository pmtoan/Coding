/*
*	C sentinel is a form of passing parameters to a function without specifying how many parameters
*/

#include "stdio.h"
#include "stdarg.h"

void print(const char* first, ... ) __attribute__(( sentinel ));
void print(const char* first, ... )
{
	va_list ap;
	const char* temp;
	if (!first)
		return;
	printf("%s\n", first);
	va_start(ap, first);
	while(1)
	{
		temp = va_arg(ap, const char*);
		if (temp == 0)
			break;
		printf("%s\n", temp);
	}
	va_end(ap);
}

void main()
{
	print("i am toan", "i'm 19 years old", NULL);
}
