//-----------------------------
//-----------------------------
//function instrumentation?
//-----------------------------
//-----------------------------
//turn on "-finstrument-functions" to use these
#include <stdlib.h>
#include <time.h>
#include <limits.h>

//XXX override _start to enable early mcheck
//XXX http://learningpearls.blogspot.com/2011/02/start-function-inside-c.html

//XXX option 1
//XXX pull down pointers to common malloc functions
//XXX only setup heap canaries when those are called?

//XXX option 2 
//XXX only do this every other function call

//XXX option 3
//XXX leave some canaries behind (up to 1000? 100? configurable?) cycle the around and check them all every time

//XXX option 4
//XXX http://stackoverflow.com/questions/69859/how-could-i-intercept-linux-sys-calls/69884#69884

//#define DEBUG_HEAP_CANARIES
#define ___MAX_CANARIES 10000
#define ___MAX_HIBERNATION_CANARIES 100
#define ___MAX_DEEP_HIBERNATION_CANARIES 100
#define ___HIBERNATION_RATIO 100
#define ___DEEP_HIBERNATION_RATIO 100
static unsigned long executionCanary = 0x0;

unsigned long* ___canaries[___MAX_CANARIES];
unsigned long* ___hibernation_canaries[___MAX_CANARIES];
unsigned long* ___deep_hibernation_canaries[___MAX_CANARIES];
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
		//use http://www.kernel.org/doc/man-pages/online/pages/man3/posix_memalign.3.html instead of malloc
		___canaries[numCanaries] = (unsigned long*)malloc(2*sizeof(unsigned long));
		if (NULL != ___canaries[numCanaries]){ 
			*___canaries[numCanaries] = executionCanary;
			
			#ifdef DEBUG_HEAP_CANARIES
			printf("made heap canary %x @ 0x%x size %x\n", executionCanary, ___canaries[numCanaries], sizeof(unsigned long));
			#endif /*DEBUG_HEAP_CANARIES*/
		  	
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

		#ifdef DEBUG_HEAP_CANARIES
		printf("freed heap canary %x @ 0x%x\n", executionCanary, ___canaries[numCanaries-1]);
		#endif /*DEBUG_HEAP_CANARIES*/

		___canaries[numCanaries-1] = 0x0;
		numCanaries--;
	}
	else{
		canaryOverflow--;
	}
}


