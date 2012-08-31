/*
Whο cοmpiles yοur cοmpiler?
*/

#ifndef WATCHMAN
#define WATCHMAN

#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

//-----------------------------
//-----------------------------
//configure (put these in your main if you want them)
//-----------------------------
//-----------------------------
//#define AGGRESSIVE_STACK_CHECKING
//#define SUPER_AGGRESSIVE_STACK_CHECKING
//#define AGGRESSIVE_HEAP_CHECKING
//#define SUPER_AGGRESSIVE_HEAP_CHECKING_C
//#define SUPER_AGGRESSIVE_HEAP_CHECKING_CPP
//#define INSTRUMENTATION

//more parts of the library
#include "secure_manual_stack_check.h"
#include "secure_common.h"

#ifdef AGGRESSIVE_STACK_CHECKING 
#include "secure_aggressive_stack_check.h"
#endif /*AGGRESSIVE_STACK_CHECKING*/

//XXX PAID
#ifdef SUPER_AGGRESSIVE_STACK_CHECKING 
#include "paid_secure_super_aggressive_stack_checking.h"
#endif /*SUPER_AGGRESSIVE_STACK_CHECKING*/

//XXX not implemented, also probably the wrong configation name
#ifdef AGGRESSIVE_HEAP_CHECKING 
#include "paid_secure_object_protection.h"
#endif /*AGGRESSIVE_HEAP_CHECKING*/

//XXX PAID
#ifdef SUPER_AGGRESSIVE_HEAP_CHECKING_C
#include "paid_secure_heap_instrumentation_c.h"
#endif /*SUPER_AGGRESSIVE_HEAP_CHECKING_CPP*/

//XXX PAID? not going in 0.1, but might be free after that
#ifdef SUPER_AGGRESSIVE_HEAP_CHECKING_CPP 
#include "paid_secure_heap_instrumentation_cpp.h"
#endif /*SUPER_AGGRESSIVE_HEAP_CHECKING_CPP*/

#endif /*WATCHMAN*/
