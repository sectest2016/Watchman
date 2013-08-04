#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <mcheck.h>

#include "secure_common.h"
#include "paid_secure_heap_instrumentation_c.h"

void debugWatchman(){

}

void *malloc(size_t size)
{
	debugWatchman();
	#ifdef DEBUG
		puts("malloc(...)");
	#endif

	static void *(*mallocp)(size_t size);
	char *error;
	void *ptr;

	/* get address of libc malloc */
	if (!mallocp) {
		mallocp = dlsym(RTLD_NEXT, "malloc");
		if ((error = dlerror()) != NULL) {
			fputs(error, stderr);
			exit(1);
		}
	}
	ptr = mallocp(size);

	#ifdef DEBUG
		printf("malloc(%d) = %p\n", size, ptr);     
	#endif

	//**********************************************//
	//**********************************************//
	// Protected section				//
	//**********************************************//
	//**********************************************//
	if(executionCanary == 0x0){
		srand(time(NULL));
		executionCanary = rand() % UINT_MAX;
	}
	if(numCanaries != ___MAX_CANARIES && canaryOverflow == 0){
		___canaries[numCanaries] = (unsigned long*)mallocp(2*sizeof(unsigned long));
		if (NULL != ___canaries[numCanaries]){ 
			*___canaries[numCanaries] = executionCanary;
			
			#ifdef DEBUG_HEAP_CANARIES
			printf("made heap canary %x @ 0x%x size %x\n", executionCanary, ___canaries[numCanaries], sizeof(unsigned long));
			#endif //DEBUG_HEAP_CANARIES
		  	
			numCanaries++;
		}
	}
	else{
		canaryOverflow++;
	}
	//**********************************************//
	//**********************************************//
	// End protected section			//
	//**********************************************//
	//**********************************************//

	#ifdef DEBUG
		printf("malloc(%d) = %p\n", size, ptr);     
	#endif

	return ptr;
}

void free(void *ptr)
{
	debugWatchman();
	#ifdef DEBUG
	puts("free(...)");
	#endif

	static void (*freep)(void *);
	char *error;

	/* get address of libc free */
	if (!freep) {
		freep = dlsym(RTLD_NEXT, "free");
		if ((error = dlerror()) != NULL) {
			fputs(error, stderr);
			exit(1);
		}
	}

	#ifdef DEBUG
		puts("checking heap magic");
	#endif
	
	//**********************************************//
	//**********************************************//
	// Protected section				//
	//**********************************************//
	//**********************************************//
	if(numCanaries != 0 && numCanaries != ___MAX_CANARIES && canaryOverflow == 0){	
//		printf("\t%x :: %x\t", *___canaries[numCanaries-1], executionCanary);
		if(*___canaries[numCanaries-1] != executionCanary){
			//pwned("heap smashing detected");
			puts("heap smashing detected\n");
			exit(1);
		}
		//XXX getting stuff like *** glibc detected *** ./heap.bin: free(): invalid pointer: 0x09653028 *** here
		freep(___canaries[numCanaries-1]);

		#ifdef DEBUG_HEAP_CANARIES
		//printf("freed heap canary %x @ 0x%x\n", executionCanary, ___canaries[numCanaries-1]);
		#endif //DEBUG_HEAP_CANARIES

		___canaries[numCanaries-1] = 0x0;
		numCanaries--;
	}
	else{
		canaryOverflow--;
	}
	//**********************************************//
	//**********************************************//
	// End protected section			//
	//**********************************************//
	//**********************************************//

	#ifdef DEBUG
		puts("freed\n");
	#endif

	freep(ptr);
}
