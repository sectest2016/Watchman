#include <stdio.h>
#include <stdlib.h>

//patch
#define SUPER_AGGRESSIVE_STACK_CHECKING
#include "secure.h"

int a(){
    char buff_bad[25] = "aaaaaaaaaawhoami";
    char buff[10];
    char buff2[10] = "dir"; //works on windows and linux!
    sprintf(buff, "%s", buff_bad);
    system(buff2);
}

int main(){
	a();
}
