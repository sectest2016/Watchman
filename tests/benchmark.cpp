/*
Watchman - A memory corruption detection and security system for GCC.
Copyright (C) 2012 Eric Wimberley

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

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
    int iterations = 1000000000;
    int i;
    char buff[10] = "test1";
    char buff2[10] = "test2";
    char buff3[10] = "aaaaaaaaa";

    gettimeofday(&start, NULL);
    for(i = 0; i < iterations; i++)//{
    	sprintf(buff2, "%s", buff);
    //}
    gettimeofday(&end, NULL);
    printf ("It took %ld seconds to run secure version of %i sprintfs.\n", ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)) / 100000, iterations);

    #undef sprintf
    gettimeofday(&start, NULL);
    for(i = 0; i < iterations; i++)//{
    	sprintf(buff2, "%s", buff);
    //}
    gettimeofday(&end, NULL);
    printf ("It took %ld seconds to run unsecure version of %i sprintfs.\n", ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)) / 100000, iterations);
}

int main(){
	a();
	b();
}
