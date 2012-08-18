//-----------------------------
//-----------------------------
//more canaries in more places
//-----------------------------
//-----------------------------
#ifdef SUPER_AGGRESSIVE_STACK_CHECKING 
#warning "SUPER_AGGRESSIVE_STACK_CHECKING on, this may impact performance"

#define MANUAL_STACK_COOKIE char COOKIE[11] = { 0xff, 0xff, 0xff, 0xff } 

void* protected_arrays[100];

void ___protect_arrays(int numArgs, ...){
	va_list args;
	va_start(args, numArgs);
	for (int j = 0; j < numArgs && j < 100; j++){
		unsigned addr = va_arg (args, int);
        	printf("argument at address %x\n", addr);
	}
	va_end (args);
}

void ___clear_protect_arrays(){

}

#define PROTECT_ARRAYS(...) \
void* _x[] = { __VA_ARGS__ };   \
___protect_arrays(sizeof(_x)/sizeof(_x[0]), __VA_ARGS__)

#define CLEAR_PROTECT_ARRAYS \
___clear_protect_arrays()

/*#define scanf(...) \
void* _x[] = { __VA_ARGS__ };   \
//find max safe writable addr
scanf(__VA_ARGS__); \*/

#define sprintf(...) \
sprintf(__VA_ARGS__); 


#endif /*SUPER_AGGRESSIVE_STACK_CHECKING*/

//TODO calculate highest safe address range to write, then store value
//at one more than that and compare on return
//XXX optimize this code
inline void check_unsafe_address(char *dest, const char *fmt, ...) {
        printf("destination at address %x\n", (int)dest);
	void* nextHighestAddress = 0x0; 
	int params = 0;
	for(int i = 0; fmt[i]; i++){
		if(fmt[i] == '%')
			params++;
	}

    	va_list args;
    	va_start(args, fmt);
	for (int j = 0; j < params; j++){
		unsigned addr = va_arg (args, int);
        	printf("argument at address %x\n", addr);
	}
	
	char valueAtNextHighestAddress = 0;
	unsigned char* nHAPtr = static_cast<unsigned char*>(nextHighestAddress);
	if(nextHighestAddress != 0x0){
		char valueAtNextHighestAddress = nHAPtr[0];
	}
	//sprintf here
	if(nextHighestAddress != 0x0){
		if(valueAtNextHighestAddress != nHAPtr[0])
			STACK_CHECK_FAIL;
	}
	
	sprintf(dest, fmt, args);

	va_end (args);
}
