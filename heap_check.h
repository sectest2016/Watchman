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
#include <sys/mman.h>

//FIXME is there a way to divide this up into header and body files?

//TODO?optimization 1:
//pull down pointers to common malloc functions
//only setup heap canaries when those are called?

//#define WATCHMAN_DEBUG
#define ___MAX_CANARIES 10000
static FILE* out = fopen("/dev/tty", "w");
struct heapList {
	void* address;
	size_t size;
};
static heapList* canaries[___MAX_CANARIES];
static int numCanaries = 0;

static void *(*old_malloc_hook)(size_t, const void *);
static void (* volatile old_free_hook) (void*, const void *);

static void *new_malloc_hook(size_t size, const void *caller) {
    	void *mem;
	__malloc_hook = old_malloc_hook;
	mem = malloc(size + sizeof(unsigned long) );

	canaries[numCanaries] = new heapList();  
	canaries[numCanaries]->address = mem;
	canaries[numCanaries]->size = size;
	unsigned long *canary = reinterpret_cast<long unsigned int *>(mem + size);
	*canary = reinterpret_cast<long unsigned int>(mem);
	#ifdef WATCHMAN_DEBUG
		//fprintf(stdout, "canary at %p is value %p\n", canary, *canary);

		for(int i = 0; i < numCanaries; i++){
			unsigned long *onCanary = reinterpret_cast<long unsigned int *>(canaries[i]->address + (size_t)canaries[i]->size);
			//fprintf(out, "Checking canary at %p with value %p and should be %p\n", onCanary, *onCanary, canaries[i]->address);
			if(onCanary != 0x0 && *onCanary != reinterpret_cast<long unsigned int>(canaries[i]->address)){
				fprintf(out, "*** Watchman: heap smashing detected in malloc ***: program terminated\n");
				exit(1);
        		}
	        }
	#endif /* WATCHMAN_DEBUG */
	if(numCanaries != ___MAX_CANARIES){
		numCanaries++;
	}
	else{
		//TODO maybe this should skip a few randomly...
		numCanaries = (numCanaries + 1) % ___MAX_CANARIES;
	}
	

	#ifdef WATCHMAN_DEBUG
		fprintf(stdout, "%p: malloc(%zu) = %p\n", caller, size, mem);
		//fprintf(stdout, "canary at: %p\n", (mem + size));
	#endif /* WATCHMAN_DEBUG */
 	__malloc_hook = new_malloc_hook;
    	return mem;
}

static void new_free_hook (void *ptr, const void *caller){
	__malloc_hook = old_malloc_hook;
	__free_hook = old_free_hook;
	free(ptr);
	for(int i = 0; i < numCanaries; i++){
		if(ptr == canaries[i]->address){
			canaries[i]->address = 0;
			canaries[i]->size = 0;
		}
	}
	#ifdef WATCHMAN_DEBUG
		//printf ("freed pointer %p from %p\n", ptr, caller);
	#endif /* WATCHMAN_DEBUG */
	__free_hook = new_free_hook;
	__malloc_hook = new_malloc_hook;	}

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
	for(int i = 0; i < numCanaries; i++){
        	unsigned long *onCanary = reinterpret_cast<long unsigned int *>(canaries[i]->address + (size_t)canaries[i]->size);
		if(onCanary != 0x0 && *onCanary != reinterpret_cast<long unsigned int>(canaries[i]->address)){
        		fprintf(stdout, "*** Watchman: heap smashing detected on function call ***: program terminated\n");
        		exit(1);
        	}
        }
}

void __cyg_profile_func_exit(void *this_fn, void *call_site)
                             __attribute__((no_instrument_function));

void __cyg_profile_func_exit(void *this_fn, void *call_site) {
	//printf("EXIT: %p, from %p\n", this_fn, call_site);
}
