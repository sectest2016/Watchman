//-----------------------------
//-----------------------------
//apply the stack check a few more places
//-----------------------------
//-----------------------------
#ifdef AGGRESSIVE_STACK_CHECKING 
#warning "AGGRESSIVE_STACK_CHECKING on, this may impact performance"

//XXX these may not trigger in time with for loops that don't have parens

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

