//-----------------------------
//-----------------------------
//apply the stack check a few more places
//-----------------------------
//-----------------------------
#warning "AGGRESSIVE_STACK_CHECKING on, this may impact performance"

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

