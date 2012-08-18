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
	
	___Canary() __attribute__ ((no_instrument_function));

	___Canary(unsigned int check) __attribute__ ((no_instrument_function));

	void check() __attribute__ ((no_instrument_function));
};

___Canary :: ___Canary() 
{
	srand(time(NULL));
	canary = rand() % UINT_MAX + 1;
	//debug value
	//canary = 0xffffffff;
	test = NULL;
	//test = new ___Canary(canary);
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

//XXX set this to max stack size?
___Canary* canaries[100];
int numCanaries = 0;

void __cyg_profile_func_enter(void *this_fn, void *call_site)
                              __attribute__((no_instrument_function));

void __cyg_profile_func_enter(void *this_fn, void *call_site) {
	//printf("ENTER: %p, from %p\n", this_fn, call_site);
	canaries[numCanaries] = new ___Canary();  
  	numCanaries++;
}

void __cyg_profile_func_exit(void *this_fn, void *call_site)
                             __attribute__((no_instrument_function));

void __cyg_profile_func_exit(void *this_fn, void *call_site) {
	//printf("EXIT:  %p, from %p\n", this_fn, call_site);
	canaries[numCanaries-1]->check();  
	free(canaries[numCanaries]);
	numCanaries--;
}


