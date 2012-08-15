//-----------------------------
//-----------------------------
//more canaries in more places
//-----------------------------
//-----------------------------
#ifdef SUPER_AGGRESSIVE_STACK_CHECKING 
#warning "SUPER_AGGRESSIVE_STACK_CHECKING on, this may impact performance"

#define MANUAL_STACK_COOKIE volatile char COOKIE[] = { 0xff, 0xff, 0xff, 0xff } 

/*#define scanf(...) \
scanf_check_setup(__VA_ARGS__); \
scanf(__VA_ARGS__); \*/

#define sprintf(...) \
sprintf(__VA_ARGS__); \
STACK_CHECK 


//sprintf_check_setup(__VA_ARGS__); 

#endif /*SUPER_AGGRESSIVE_STACK_CHECKING*/


