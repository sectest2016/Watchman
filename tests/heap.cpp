#include <stdio.h>
#include <stdlib.h>

#define SUPER_AGGRESSIVE_HEAP_CHECKING
#include "watchman.h"

class Test{
public:

void a(){
	scanf("%s", buffer);
}

private:
char buffer[10];
};

class Command{
public:

Command(){
	command[0] = 'l';
	command[1] = 's';
	command[2] = '\0';
}

void a(){
	system(command);
}

private:
char command[10];
};

int main(){
	Test* aTest = new Test();
	Command* c1 = new Command();
	Command* c2 = new Command();
	Command* c3 = new Command();
	Command* c4 = new Command();
	free(c1);
	aTest->a();
	c1->a();
	c2->a();
	c3->a();
	c4->a();
}
