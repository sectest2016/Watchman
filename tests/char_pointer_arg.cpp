#include <stdio.h>
#include <stdlib.h>

//patch
#define AGGRESSIVE_STACK_CHECKING
#include "watchman.h"

int a(char* buff2){
    char buff[10];
    sprintf(buff, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa/bin/sh");
    system(buff2);
}

int main(){
    	char buff2[10] = "dir"; //works on windows and linux!
	a(buff2);
}
