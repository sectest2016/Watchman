#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//-----------------------------
//-----------------------------
//sοme cοmmοn definitiοns
//-----------------------------
//-----------------------------

#define UNSAFE_SIZEOF(array) (sizeof(array)/sizeof(*(array)))

void
__attribute__ ((noreturn))
pwned(char* msg)
{
	FILE* out = fopen("/dev/tty", "w");
	fprintf(out, "*** Watchman: %s ***: program terminated\n", msg);
	exit(1);
}

//no really, exit
__asm__ (
"nop\n"
"call exit\n"
"nop\n"
);

//XXX make a list of all unsafe functions to protect here
/*
This is the template to generate a check for
all easily patchable vulnerable functions.

#define fgets(...) \
{ fgets(__VA_ARGS__); \
STACK_CHECK; }

#define fscanf(...) \
{ fscanf(__VA_ARGS__); \
STACK_CHECK; }

#define fwrite(...) \
{ fwrite(__VA_ARGS__); \
STACK_CHECK; }

//XXX is this needed?
#define gets(...) \
{ gets(__VA_ARGS__); \
STACK_CHECK; }

#define scanf(...) \
{ scanf(__VA_ARGS__); \
STACK_CHECK; }

#define sprintf(...) \
{ sprintf(__VA_ARGS__); \
STACK_CHECK; }

#define sscanf(...) \
{ sscanf(__VA_ARGS__); \
STACK_CHECK; }

#define strcat(...) \
{ strcat(__VA_ARGS__); \
STACK_CHECK; }

#define strcpy(...) \
{ strcpy(__VA_ARGS__); \
STACK_CHECK; }

#define strecpy(...) \
{ strecpy(__VA_ARGS__); \
STACK_CHECK; }

#define streadd(...) \
{ streadd(__VA_ARGS__); \
STACK_CHECK; }

#define strcat(...) \
{ strcat(__VA_ARGS__); \
STACK_CHECK; }

#define strtrns(...) \
{ strtrns(__VA_ARGS__); \
STACK_CHECK; }

#define vfprintf(...) \
{ vfprintf(__VA_ARGS__); \
STACK_CHECK; }

#define vsprintf(...) \
{ vsprintf(__VA_ARGS__); \
STACK_CHECK; }

*/
