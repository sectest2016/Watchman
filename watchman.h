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
