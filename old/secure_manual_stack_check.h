//-----------------------------
//-----------------------------
//manually implemented early stack check
//-----------------------------
//-----------------------------

//TODO make a honey pot stack check fail

#define STACK_CHK_FAIL_ASM "CALL __stack_chk_fail\n"

#ifdef __i386__

	#define STACK_CHECK_ASM \
	"mov -0xc(%ebp),%edx\n" \
	"xor %gs:0x14,%edx;\n"  \
	"je . + 13\n" 		\
	"mov 0x2c(%esp),%edx\n" \
	"xor %gs:0x14,%edx;\n"  \
	"je . + 7\n" 		\
	STACK_CHK_FAIL_ASM

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
	#warning "secure.h not currenty implemented for this architecture"
#endif

#define STACK_CHECK_FAIL \
__asm__ __volatile__( \
STACK_CHK_FAIL_ASM \
)

#define STACK_CHECK \
__asm__ __volatile__( \
STACK_CHECK_ASM \
) 

