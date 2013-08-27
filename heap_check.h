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

//TODO?optimization 1:
//pull down pointers to common malloc functions
//only setup heap canaries when those are called?

#define WATCHMAN_DEBUG
#define ___MAX_CANARIES 10000
static FILE* out = fopen("/dev/tty", "w");
struct heapList *heapStart = 0x0;
struct heapList *heapLast = 0x0;
struct heapList {
	void* address;
	//size_t size;
	//struct heapList *prev;
	struct heapList *next;
};
//void sig_handler(int);

//heap checks in another thread are turned off for now, we might add them later
/*void heap_check(){
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
}*/

/*void new_heap_check() {
	//TODO optimize this branch as unlikely (only happens once)
	if(numCanaries != ___MAX_CANARIES && canaryOverflow == 0){
		___canaries[numCanaries] = (unsigned long*)malloc(2*sizeof(unsigned long));
		#ifdef DEBUG_HEAP_CANARIES
		printf("made heap canary %x @ 0x%x size %x\n", executionCanary, ___canaries[numCanaries], sizeof(unsigned long));
		#endif //DEBUG_HEAP_CANARIES
	  	numCanaries++;
	}
	else{
		canaryOverflow++;
	}
}*/

/*void sig_handler(int sig) {
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
}*/

static void *(*old_malloc_hook)(size_t, const void *);
static void (* volatile old_free_hook) (void*, const void *);

static void *new_malloc_hook(size_t size, const void *caller) {
    	void *mem;
	__malloc_hook = old_malloc_hook;
	mem = malloc(size + sizeof(unsigned long) );

	struct heapList *heapNext = (struct heapList*)malloc(sizeof(struct heapList));
	heapNext->address = mem;
	
	if(heapStart == 0x0){
		heapStart = heapNext;
		heapLast = heapStart;
	}
	else{
		heapLast->next = heapNext;
		heapLast = heapNext;
	}

	//new_heap_check();
	#ifdef WATCHMAN_DEBUG
		fprintf(stdout, "%p: malloc(%zu) = %p\n", caller, size, mem);
		fprintf(stdout, "next: %p\n", heapLast->address);
	#endif /* WATCHMAN_DEBUG */
    	__malloc_hook = new_malloc_hook;
    	return mem;
}

static void new_free_hook (void *ptr, const void *caller){
	__malloc_hook = old_malloc_hook;
	__free_hook = old_free_hook;
	free(ptr);
	#ifdef WATCHMAN_DEBUG
		printf ("freed pointer %p from %p\n", ptr, caller);
	#endif /* WATCHMAN_DEBUG */
	__free_hook = new_free_hook;
	__malloc_hook = new_malloc_hook;
	}

static void init_my_hooks(void) {
    	old_malloc_hook = __malloc_hook;
	old_free_hook = __free_hook;
    	__malloc_hook = new_malloc_hook;
	__free_hook = new_free_hook;
}

//FIXME why is volatile keyword required here? we need to detect when this is required
void (* volatile __malloc_initialize_hook)(void) = init_my_hooks;

void __cyg_profile_func_enter(void *this_fn, void *call_site)
                              __attribute__((no_instrument_function));

void __cyg_profile_func_enter(void *this_fn, void *call_site) {
	//printf("ENTER: %p, from %p\n", this_fn, call_site);
	/*for(int i = 0; i < numCanaries; i++){
		//printf("Checking canary %i\n", i);
		if(*___canaries[i] != executionCanary){
			fprintf(out, "*** Watchman: heap smashing detected ***: program terminated\n");
			exit(1);
        	}
        }*/
	struct heapList *next = heapStart;
	while(next != 0x0){
		next = next->next;
	}
}

void __cyg_profile_func_exit(void *this_fn, void *call_site)
                             __attribute__((no_instrument_function));

void __cyg_profile_func_exit(void *this_fn, void *call_site) {
	//printf("EXIT: %p, from %p\n", this_fn, call_site);
}
