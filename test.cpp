#include <stdio.h>

int main()
{
	char buff[30];
	printf("buffer is at %08x\n", buff);
	scanf("%s", buff);
	system(buff);
	return 0;
}

