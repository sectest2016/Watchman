//-----------------------------
//-----------------------------
//more canaries in more places
//-----------------------------
//-----------------------------
#ifdef SUPER_AGGRESSIVE_STACK_CHECKING 
#warning "SUPER_AGGRESSIVE_STACK_CHECKING on, this may impact performance"

//option 1, precesion but more modifications to original code
//TODO calculate how large we can actually make this?
#define MANUAL_STACK_COOKIE(buffer) \
char COOKIE##buffer[sizeof(_x)/sizeof(_x[0])] = { 0x00 };

//option 2, brute force
//TODO options for sizes?
/*#define MANUAL_STACK_COOKIES \
char COOKIE1[1] = { 0x00 }; \
char COOKIE2[2] = { 0x00, 0xff }; \
char COOKIE4[4] = { 0x00, 0xff, 0xff, 0xff }; \
char COOKIE8[8] = { 0x00, 0xff, 0xff, 0xff }; \ 
char COOKIE16[16] = { 0x00, 0xff, 0xff, 0xff }; \
char COOKIE32[32] = { 0x00, 0xff, 0xff, 0xff }; \
char COOKIE64[64] = { 0x00, 0xff, 0xff, 0xff }*/ 

//# define MANUAL_AGGRESSIVE_STACK_CHECK \
//if all cookies don't match, fail stack check

/*#define scanf(...) \
void* _x[] = { __VA_ARGS__ };   \
//find max safe writable addr
scanf(__VA_ARGS__); \*/

#define sprintf(...) \
sprintf(__VA_ARGS__); 

#endif /*SUPER_AGGRESSIVE_STACK_CHECKING*/
