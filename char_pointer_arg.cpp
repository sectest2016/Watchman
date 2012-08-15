#include <stdio.h>
#include <stdlib.h>

//patch
#include "secure.h"
#define AGGRESSIVE_STACK_CHECKING

int a(char* buff2){
    char buff[10];
    sprintf(buff, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaawhoami");
    system(buff2);
}

int main(){
    	char buff2[10] = "dir"; //works on windows and linux!
	a(buff2);
}
