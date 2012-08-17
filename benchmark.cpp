#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

//patch
#define AGGRESSIVE_STACK_CHECKING
#include "watchman.h"

void b(){
    int iterations = 10;
    int i; 
    char buff[10] = "test1";
    char buff2[10] = "test2";
    char buff3[10] = "aaaaaaaaa";

    for(i = 0; i < iterations; i++)//{
    	sprintf(buff2, "%s", buff);
    //}
}

int a(){
    struct timeval start, end;
    //int iterations = 1000000000;
    int iterations = 1000;
    int i;
    char buff[10] = "test1";
    char buff2[10] = "test2";
    char buff3[10] = "aaaaaaaaa";

    gettimeofday(&start, NULL);
    for(i = 0; i < iterations; i++)//{
    	sprintf(buff2, "%s", buff);
    //}
    gettimeofday(&end, NULL);
    printf ("It took %ld seconds to run secure version of %i sprintfs.\n", ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)), iterations);

    #undef sprintf
    gettimeofday(&start, NULL);
    for(i = 0; i < iterations; i++)//{
    	sprintf(buff2, "%s", buff);
    //}
    gettimeofday(&end, NULL);
    printf ("It took %ld seconds to run unsecure version of %i sprintfs.\n", ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)), iterations);
}

int main(){
	a();
	b();
}
