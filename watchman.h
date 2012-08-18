/*
Watchman - A memory corruption detection and security system for GCC.
Copyright (C) 2012 Eric Wimberley

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

/*
Who compiles your compiler?
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
//#define INSTRUMENTATION

//more parts of the library
#include "secure_manual_stack_check.h"
#include "secure_common.h"

//XXX is this needed?
//#include "secure_instrumentation.h"

#ifdef AGGRESSIVE_STACK_CHECKING 
#include "secure_aggressive_stack_check.h"
#endif /*AGGRESSIVE_STACK_CHECKING*/

//XXX PAID
#ifdef SUPER_AGGRESSIVE_STACK_CHECKING 
#include "paid_secure_super_aggressive_stack_checking.h"
#endif /*SUPER_AGGRESSIVE_STACK_CHECKING*/

//XXX PAID
#ifdef AGGRESSIVE_HEAP_CHECKING 
#include "secure_object_protection.h"
#endif /*AGGRESSIVE_HEAP_CHECKING*/

#endif /*WATCHMAN*/
