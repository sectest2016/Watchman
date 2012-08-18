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

class ___Canary{
unsigned int canary;
___Canary* test;

public:
	
	___Canary() __attribute__ ((no_instrument_function));

	___Canary(unsigned int check) __attribute__ ((no_instrument_function));

	void check() __attribute__ ((no_instrument_function));
};

___Canary :: ___Canary() 
{
	srand(time(NULL));
	canary = rand() % UINT_MAX + 1;
	test = NULL;
	//XXX is it possible to overwrite this with a repeating value?
	//XXX if so, the canary can be defeated (depends on object creation order?)
	test = new ___Canary(canary);
}

___Canary :: ___Canary(unsigned int check) : test(NULL), canary(check) 
{

}

void ___Canary :: check()
{
	if(test != NULL){
		if(test->canary != canary){
			STACK_CHECK_FAIL;
		}
	}	
}

___Canary* canaries[___MAX_CANARIES];
int numCanaries = 0;
//XXX test overflow system
int canaryOverflow = 0;

//TODO can these be inlined?
void __cyg_profile_func_enter(void *this_fn, void *call_site)
                              __attribute__((no_instrument_function));

void __cyg_profile_func_enter(void *this_fn, void *call_site) {
	//printf("ENTER: %p, from %p\n", this_fn, call_site);
	if(numCanaries != ___MAX_CANARIES && canaryOverflow == 0){
		canaries[numCanaries] = new ___Canary();  
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
		canaries[numCanaries-1]->check();  
		free(canaries[numCanaries]);
		numCanaries--;
	}
	else{
		canaryOverflow--;
	}
}


