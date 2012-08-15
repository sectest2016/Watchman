//-----------------------------
//-----------------------------
//some common definitions
//-----------------------------
//-----------------------------

#define UNSAFE_SIZEOF(array) (sizeof(array)/sizeof(*(array)))

inline void sprintf_check_setup(char *dest, const char *fmt, ...) {
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
