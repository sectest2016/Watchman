//-----------------------------
//-----------------------------
//function instrumentation?
//-----------------------------
//-----------------------------
//turn on "-finstrument-functions" to use these
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <unistd.h>
#include <sys/types.h>

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

class ___Canary{
unsigned int canary;

public:
	
	___Canary() __attribute__ ((no_instrument_function));

	void check() __attribute__ ((no_instrument_function));
};

___Canary :: ___Canary() 
{
	canary = executionCanary;
}

void ___Canary :: check()
{
	if(executionCanary != canary){
		pwned("heap smashing detected");
	}
}

___Canary* canaries[___MAX_CANARIES];
int numCanaries = 0;
//XXX test overflow system
int canaryOverflow = 0;

void heap_check(){
	pid_t pID = fork();
	if(pID == 0){
		printf("Forked...\n");
		srand(time(NULL));
		executionCanary = rand() % UINT_MAX;
		printf("%x\n", executionCanary);
		//TODO check for terminate signal
		while(true){
			if(time(NULL) > lastTime + 10){
				lastTime = time(NULL);
				printf("%i\n", time(NULL));
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
	//printf("ENTER: %p, from %p\n", this_fn, call_site);
	//TODO optimize this branch as unlikely (only happens once)
	if(executionCanary == 0x0){
	}
	if(numCanaries != ___MAX_CANARIES && canaryOverflow == 0){
		canaries[numCanaries] = new ___Canary();  
	  	numCanaries++;
	}
	else{
		canaryOverflow++;
	}
}

void check_all_canaries() {
	//printf("EXIT:  %p, from %p\n", this_fn, call_site);
	if(numCanaries != ___MAX_CANARIES && canaryOverflow == 0){
		canaries[numCanaries-1]->check();  
		free(canaries[numCanaries-1]);
		canaries[numCanaries-1] = 0x0;
		numCanaries--;
	}
	else{
		canaryOverflow--;
	}
}


