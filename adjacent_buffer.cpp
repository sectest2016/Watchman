#include <stdio.h>
#include <stdlib.h>

//patch
#define SUPER_AGGRESSIVE_STACK_CHECKING
#include "secure.h"

int a(){
    SHOTGUN_STACK_COOKIES;
    char buff_bad[25] = "aaaaaaaaaawhoami";
    char buff[10];
    char buff2[10] = "dir"; //works on windows and linux!
    //PROTECT_ARRAYS(buff, buff2);
    sprintf(buff, "%s", buff_bad);
    system(buff2);
    //CLEAR_PROTECT_ARRAYS;
}

int main(){
	a();
}
