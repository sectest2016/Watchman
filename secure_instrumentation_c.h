//-----------------------------
//-----------------------------
//function instrumentation?
//-----------------------------
//-----------------------------
//turn on "-finstrument-functions" to use these
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define ___MAX_CANARIES 10000
static unsigned int executionCanary = 0x0;

unsigned* canaries[___MAX_CANARIES];
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
		int *ptr = (int*)malloc(sizeof(unsigned));
		if (NULL != ptr) 
		  	numCanaries++;
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
		if(*canaries[numCanaries] != executionCanary){
			STACK_CHECK_FAIL;
		}
		free(canaries[numCanaries]);
		numCanaries--;
	}
	else{
		canaryOverflow--;
	}
}


