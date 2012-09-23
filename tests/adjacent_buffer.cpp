#include <stdio.h>
#include <stdlib.h>

//patch
#define SUPER_AGGRESSIVE_STACK_CHECKING
#include "watchman.h"

int a(){
    SHOTGUN_STACK_COOKIES_CHAR;
    char buff_bad[25] = "aaaaaaaaaa/bin/sh";
    //TODO if these are the same size, the shotgun method fails
    char buff[10];
    char buff2[4] = "dir"; //works on windows and linux!
    sprintf(buff, "%s", buff_bad);
    system(buff2);
}

int main(){
	a();
}
