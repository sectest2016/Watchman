//-----------------------------
//-----------------------------
//more canaries in more places
//-----------------------------
//-----------------------------
#ifdef SUPER_AGGRESSIVE_STACK_CHECKING 
#warning "SUPER_AGGRESSIVE_STACK_CHECKING on, this may impact performance"

#define MANUAL_STACK_COOKIE char COOKIE[11] = { 0xff, 0xff, 0xff, 0xff } 

void ___protect_arrays(){

}

#define PROTECT_ARRAYS(__VA_ARGS__) \
___protect_arrays();

/*#define scanf(...) \
scanf_check_setup(__VA_ARGS__); \
scanf(__VA_ARGS__); \*/

#define sprintf(...) \
sprintf(__VA_ARGS__); 


//sprintf_check_setup(__VA_ARGS__); 

#endif /*SUPER_AGGRESSIVE_STACK_CHECKING*/


