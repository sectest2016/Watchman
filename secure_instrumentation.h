//-----------------------------
//-----------------------------
//function instrumentation?
//-----------------------------
//-----------------------------
//turn on "-finstrument-functions" to use these
//XXX turn off if this isn't the gnu compiler?
//TODO can these be inlined?
#include <stdlib.h>
#include <time.h>
#include <limits.h>

class ___Canary{
unsigned int canary;
___Canary* test;

public:

	___Canary(){
		srand(time(NULL));
		canary = rand() % UINT_MAX + 1;
		test = new ___Canary(canary);
	}

	___Canary(unsigned int test) : test(NULL), canary(test){

	}

	void check(){
		if(test != NULL){
		
		}
	}

};

void __cyg_profile_func_enter(void *this_fn, void *call_site)
                              __attribute__((no_instrument_function));

void __cyg_profile_func_enter(void *this_fn, void *call_site) {
	printf("ENTER: %p, from %p\n", this_fn, call_site);
	___Canary* canary = new ___Canary();  
  
}

void __cyg_profile_func_exit(void *this_fn, void *call_site)
                             __attribute__((no_instrument_function));

void __cyg_profile_func_exit(void *this_fn, void *call_site) {
	printf("EXIT:  %p, from %p\n", this_fn, call_site);
}


