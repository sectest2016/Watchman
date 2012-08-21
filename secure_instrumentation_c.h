//-----------------------------
//-----------------------------
//function instrumentation?
//-----------------------------
//-----------------------------
//turn on "-finstrument-functions" to use these
#include <stdlib.h>
#include <time.h>
#include <limits.h>

//option 1
//XXX pull down pointers to common malloc functions
//XXX only setup heap canaries when those are called?

//option 2 
//XXX only do this every other function call

//option 3
//XXX leave some canaries behind (up to 1000? 100? configurable?) cycle the around and check them all every time

#define ___MAX_CANARIES 10000
static int executionCanary = 0x0;

int* ___canaries[___MAX_CANARIES];
int numCanaries = 0;
//XXX test overflow system
int canaryOverflow = 0;

//TODO can these be inlined?
void __cyg_profile_func_enter(void *this_fn, void *call_site)
                              __attribute__((no_instrument_function));

void __cyg_profile_func_enter(void *this_fn, void *call_site) {
	//printf("ENTER: %p, from %p\n", this_fn, call_site);
	if(executionCanary == 0x0){
		srand(time(NULL));
		executionCanary = rand() % UINT_MAX;
	}
	if(numCanaries != ___MAX_CANARIES && canaryOverflow == 0){
		___canaries[numCanaries] = (int*)malloc(sizeof(int));
		if (NULL != ___canaries[numCanaries]){ 
			*___canaries[numCanaries] = executionCanary;
			printf("made heap canary %x @ 0x%x to %x\n", executionCanary, ___canaries[numCanaries], ___canaries[numCanaries]+sizeof(int));
		  	numCanaries++;
		}
	}
	else{
		canaryOverflow++;
	}
}

void __cyg_profile_func_exit(void *this_fn, void *call_site)
                             __attribute__((no_instrument_function));

void __cyg_profile_func_exit(void *this_fn, void *call_site) {
	//printf("EXIT:  %p, from %p\n", this_fn, call_site);
	if(numCanaries != ___MAX_CANARIES && canaryOverflow == 0){
		if(*___canaries[numCanaries-1] != executionCanary){
			pwned("heap smashing detected");
		}
		//XXX getting stuff like *** glibc detected *** ./heap.bin: free(): invalid pointer: 0x09653028 *** here
		free(___canaries[numCanaries-1]);
		printf("freed heap canary %x @ 0x%x\n", executionCanary, ___canaries[numCanaries-1]);
		___canaries[numCanaries-1] = 0x0;
		numCanaries--;
	}
	else{
		canaryOverflow--;
	}
}


