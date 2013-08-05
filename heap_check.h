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
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <unistd.h>
#include <malloc.h>
#include <signal.h>

//option 1
//XXX pull down pointers to common malloc functions
//XXX only setup heap canaries when those are called?

//option 2
//XXX can I detect if this is an object function or not?

//option 3 
//XXX only do this every other function call

#define ___MAX_CANARIES 10000
static unsigned int executionCanary = 0x0;
static int lastTime = 0;
void sig_handler(int);
unsigned long* ___canaries[___MAX_CANARIES];
int numCanaries = 0;
//XXX test overflow system
int canaryOverflow = 0;

void heap_check(){
	pid_t pID = fork();
	if(pID == 0){
		signal(SIGSEGV, sig_handler);
		signal(SIGABRT, sig_handler);
		signal(SIGTERM, sig_handler);
		printf("Forked...\n");
		srand(time(NULL));
		executionCanary = rand() % UINT_MAX;
		printf("%x\n", executionCanary);
		//TODO check for terminate signal
		while(true){
			if(time(NULL) > lastTime + 0){
				lastTime = time(NULL);
				//printf("%i\n", time(NULL));
				//slow this down
				//new_heap_check();
			}
		}
		exit(0);
	}
	else if(pID < 0){
		printf("Watchman: failure to fork!\n");
	}
	else{
		printf("Forking from main thread...\n");
		return;
	}
}

void new_heap_check() {
	//TODO optimize this branch as unlikely (only happens once)
	if(numCanaries != ___MAX_CANARIES && canaryOverflow == 0){
		___canaries[numCanaries] = (unsigned long*)malloc(2*sizeof(unsigned long));
		#ifdef DEBUG_HEAP_CANARIES
		printf("made heap canary %x @ 0x%x size %x\n", executionCanary, ___canaries[numCanaries], sizeof(unsigned long));
		#endif /*DEBUG_HEAP_CANARIES*/
	  	numCanaries++;
	}
	else{
		canaryOverflow++;
	}
}

void check_all_canaries() {
	for(int i = 0; i < numCanaries; i++){
		//canaries[i]->check();
		//___canaries[i]...
	}
}

void sig_handler(int sig) {
	switch (sig) {
	case SIGTERM:
		abort();
	case SIGABRT:
		abort();
	case SIGSEGV:
		abort();
	default:
		abort();
	}
}

static void *(*old_malloc_hook)(size_t, const void *);

static void *new_malloc_hook(size_t size, const void *caller) {
    	void *mem;
	__malloc_hook = old_malloc_hook;
	mem = malloc(size);
	new_heap_check();
    	fprintf(stderr, "%p: malloc(%zu) = %p\n", caller, size, mem);
    	__malloc_hook = new_malloc_hook;
    	return mem;
}

static void init_my_hooks(void) {
    	old_malloc_hook = __malloc_hook;
    	__malloc_hook = new_malloc_hook;
}

//FIXME why is volatile keyword required here? we need to detect when this is required
void (* volatile __malloc_initialize_hook)(void) = init_my_hooks;

void __cyg_profile_func_enter(void *this_fn, void *call_site)
                              __attribute__((no_instrument_function));

void __cyg_profile_func_enter(void *this_fn, void *call_site) {
	//printf("ENTER: %p, from %p\n", this_fn, call_site);
	for(int i = 0; i < numCanaries; i++){
		//printf("Checking canary %i\n", i);
		if(*___canaries[i] != executionCanary){
                	pwned("heap smashing detected");
        	}
        }
}

void __cyg_profile_func_exit(void *this_fn, void *call_site)
                             __attribute__((no_instrument_function));

void __cyg_profile_func_exit(void *this_fn, void *call_site) {
	printf("EXIT:  %p, from %p\n", this_fn, call_site);
}
