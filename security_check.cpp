#include <stdio.h>
#include <stdlib.h>

//patch
#include "secure.h"

int a(){
    char buff[10] = "test1";
    char buff2[10] = "test2";
    char buff3[20];
    char buff4[10] = "dir"; //works on windows and linux!
    //scanf("%s%10c", buff, buff2);
    for(int i = 0; i < 10; i++)//{
    	sprintf(buff3, "%s %s", buff, buff2);
    //}
    system(buff4);
}

int main(){
	a();
}
