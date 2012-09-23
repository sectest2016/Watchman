//-----------------------------
//-----------------------------
//more canaries in more places
//-----------------------------
//-----------------------------
#warning "SUPER_AGGRESSIVE_STACK_CHECKING on, this may impact performance"

//TODO initialize stack cookie bytes
#define MANUAL_STACK_COOKIE_INIT \
srand(time(NULL)); \
executionCanary = rand() % UINT_MAX;

//option 1, precesion but more modifications to original code
//TODO calculate how large we can actually make this?
//TODO this doesn't actually work yet
#define MANUAL_STACK_COOKIE(buffer) \
char ___COOKIE##buffer[sizeof(_x)/sizeof(_x[0])] = { 0x00, 0xff, 0xff, 0xff };

//XXX use prime number lengths for cookies?

//option 2, brute force
//XXX generate random numbers
//FIXME use mprotect? http://en.wikibooks.org/wiki/C_Programming/POSIX_Reference/sys/mman.h/mprotect
//FIXME also look at http://www.kernel.org/doc/man-pages/online/pages/man2/mprotect.2.html
#define SHOTGUN_STACK_COOKIES_CHAR \
int ___numCookies = 7; \
char ___COOKIE4[4] = { 0x00, 0xff, 0xff, 0xff }; \
char ___COOKIE6[6] = { 0x00, 0xff, 0xff, 0xff }; \
char ___COOKIE8[8] = { 0x00, 0xff, 0xff, 0xff }; \ 
char ___COOKIE10[10] = { 0x00, 0xff, 0xff, 0xff }; \ 
char ___COOKIE16[16] = { 0x00, 0xff, 0xff, 0xff }; \
char ___COOKIE32[32] = { 0x00, 0xff, 0xff, 0xff }; \
char ___COOKIE64[64] = { 0x00, 0xff, 0xff, 0xff }; \
char* ___COOKIES[]  = {___COOKIE4, ___COOKIE6, ___COOKIE8, ___COOKIE10, ___COOKIE16, ___COOKIE16, ___COOKIE32, ___COOKIE64}

//option 3
//XXX use alloca to dynamically allocate cookie on stack? possibly use instrumentation
//XXX shotgun technique could then be moved to the free version

#define CHECK_SHOTGUN_STACK_COOKIES \
for(int ___onCookie = 0; ___onCookie < ___numCookies; ___onCookie++){ \
if(___COOKIES[___onCookie][0] != 0x00)\
pwned("stack smashing caught early"); \
}

//# define MANUAL_AGGRESSIVE_STACK_CHECK \
//if all cookies don't match, fail stack check

/*#define scanf(...) \
void* _x[] = { __VA_ARGS__ };   \
//find max safe writable addr
scanf(__VA_ARGS__); \*/

#define sprintf(...) \
sprintf(__VA_ARGS__); \
CHECK_SHOTGUN_STACK_COOKIES

