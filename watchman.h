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
//configure (put these in your main if you want them)
//-----------------------------
//-----------------------------
//#define AGGRESSIVE_STACK_CHECKING
//#define SUPER_AGGRESSIVE_STACK_CHECKING
//#define INSTRUMENTATION

//more parts of the library
#include "secure_manual_stack_check.h"
#include "secure_common.h"
//#include "secure_instrumentation.h"
#include "secure_object_protection.h"

#ifdef AGGRESSIVE_STACK_CHECKING 
#include "secure_aggressive_stack_check.h"
#endif /*AGGRESSIVE_STACK_CHECKING*/

//XXX PAID
#ifdef SUPER_AGGRESSIVE_STACK_CHECKING 
#include "paid_secure_super_aggressive_stack_checking.h"
#endif /*SUPER_AGGRESSIVE_STACK_CHECKING*/

#endif /*SECURE_T_MINUS_ONE*/
