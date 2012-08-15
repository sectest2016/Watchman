#ifndef SECURE_T_MINUS_ONE
#define SECURE_T_MINUS_ONE

#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>
//#include <ctype.h>
//#include <string.h>
#include <stdarg.h>
#include <stdint.h>


//-----------------------------
//-----------------------------
//some common definitions
//-----------------------------
//-----------------------------
#define UNSAFE_SIZEOF(array) (sizeof(array)/sizeof(*(array)))

inline void sprintf_check_setup(char *dest, const char *fmt, ...) {
        printf("destination at address %x\n", dest);
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
	va_end (args);
}



//-----------------------------
//-----------------------------
//configure
//-----------------------------
//-----------------------------
//#define AGGRESSIVE_STACK_CHECKING
#define SUPER_AGGRESSIVE_STACK_CHECKING
//#define INSTRUMENTATION


//-----------------------------
//-----------------------------
//manually implemented early stack check
//-----------------------------
//-----------------------------
#ifdef __i386__
	//TODO look into xor %eax,%eax instead of mov
	#define STACK_CHECK_ASM \
	"mov $0x0,%eax\n" \
	"mov 0x2c(%esp),%edx\n" \
	"xor %gs:0x14,%edx;\n"  \
	"je . + 7\n" \
	"call __stack_chk_fail\n"
#elif defined __x86_64__
	#warning "secure.h not currenty implemented for i386"
#elif defined __powerpc64__
	#warning "secure.h not currenty implemented for powerpc64"
#elif defined __powerpc__
	#warning "secure.h not currenty implemented for powerpc"
#elif defined __sparc__ && defined __arch64__
	#warning "secure.h not currenty implemented for sparc 64"
#elif defined __sparc__
	#warning "secure.h not currenty implemented for sparc"
#elif defined __s390x__
	#warning "secure.h not currenty implemented for s390x"
#elif defined __s390__
	#warning "secure.h not currenty implemented for s390"
#elif defined __ia64__
	#warning "secure.h not currenty implemented for ia64"
#else
	extern uintptr_t __stack_chk_guard;
	# define STACK_CHK_GUARD __stack_chk_guard
#endif

#define STACK_CHECK \
__asm__ __volatile__( \
STACK_CHECK_ASM \
); 


//-----------------------------
//-----------------------------
//more canaries in more places
//-----------------------------
//-----------------------------
#ifdef SUPER_AGGRESSIVE_STACK_CHECKING 
#warning "SUPER_AGGRESSIVE_STACK_CHECKING on, this may impact performance"

/*#define scanf(...) \
scanf_check_setup(__VA_ARGS__); \
scanf(__VA_ARGS__); \*/

#define sprintf(...) \
sprintf(__VA_ARGS__); \
sprintf_check_setup(__VA_ARGS__); 

#endif /*SUPER_AGGRESSIVE_STACK_CHECKING*/


//-----------------------------
//-----------------------------
//apply the stack check a few more places
//-----------------------------
//-----------------------------
#ifdef AGGRESSIVE_STACK_CHECKING 
#warning "AGGRESSIVE_STACK_CHECKING on, this may impact performance"

#define scanf(...) \
scanf(__VA_ARGS__); \
STACK_CHECK

#define fscanf(...) \
fscanf(__VA_ARGS__); \
STACK_CHECK

#define gets(...) \
gets(__VA_ARGS__); \
STACK_CHECK

#endif /*AGGRESSIVE_STACK_CHECKING*/


//-----------------------------
//-----------------------------
//function instrumentation?
//-----------------------------
//-----------------------------
#ifdef INSTRUMENTATION
//turn on "-finstrument-functions" to use these
//XXX turn off if this isn't the gnu compiler?
//TODO can these be inlined?
//TODO make an option to turn these off

void __cyg_profile_func_enter(void *this_fn, void *call_site)
                              __attribute__((no_instrument_function));
void __cyg_profile_func_enter(void *this_fn, void *call_site) {
  printf("ENTER: %p, from %p\n", this_fn, call_site);
} /* __cyg_profile_func_enter */

void __cyg_profile_func_exit(void *this_fn, void *call_site)
                             __attribute__((no_instrument_function));
void __cyg_profile_func_exit(void *this_fn, void *call_site) {
  printf("EXIT:  %p, from %p\n", this_fn, call_site);
} /* __cyg_profile_func_enter */
#endif /*INSTRUMENTATION*/


//-----------------------------
//-----------------------------
//help protected objects in C++
//-----------------------------
//-----------------------------
#ifdef __GNUG__
	//put C++ specific stuff here
#endif /*__GNUG__*/

#endif /*SECURE_T_MINUS_ONE*/
