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
//#define AGGRESSIVE_HEAP_CHECKING

//more parts of the library
#include "manual_stack_check.h"
#include "common.h"

#ifdef STACK_CHECKING 
#include "stack_check.h"
#endif /*STACK_CHECKING*/

#ifdef HEAP_CHECKING 
#include "heap_check.h"
#endif /*HEAP_CHECKING*/

#endif /*WATCHMAN*/
