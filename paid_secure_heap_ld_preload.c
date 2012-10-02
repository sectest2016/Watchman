#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <mcheck.h>

#define ___MAX_CANARIES 10000
#define ___MAX_HIBERNATION_CANARIES 100
#define ___MAX_DEEP_HIBERNATION_CANARIES 100
#define ___HIBERNATION_RATIO 100
#define ___DEEP_HIBERNATION_RATIO 100
unsigned long* ___canaries[___MAX_CANARIES];
unsigned long* ___hibernation_canaries[___MAX_CANARIES];
unsigned long* ___deep_hibernation_canaries[___MAX_CANARIES];
int numCanaries = 0;
//XXX test overflow system
int canaryOverflow = 0;




void *malloc(size_t size)
{
	puts("malloc(...)");
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

	printf("malloc(%d) = %p\n", size, ptr);     
	if(numCanaries != ___MAX_CANARIES && canaryOverflow == 0){
		*___canaries[numCanaries] = ptr;
		numCanaries++;
	}
	else{
		canaryOverflow++;
	}
	printf("malloc(%d) = %p\n", size, ptr);     

	return ptr;
}

void free(void *ptr)
{
	puts("free(...)");
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


	puts("checking heap magic");
	if(numCanaries != ___MAX_CANARIES && canaryOverflow == 0){
		numCanaries--;
		mcheck_status corrupt = mprobe(ptr);
	}
	else{
		canaryOverflow--;
	}

	puts("free(");
	//char ptrChr[64];
	//itoa((long)ptr, ptrChr, 16);
	//puts(ptrChr);
	puts(")\n");

	freep(ptr);
}
