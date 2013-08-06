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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//-----------------------------
//-----------------------------
//sοme cοmmοn definitiοns
//-----------------------------
//-----------------------------

#define UNSAFE_SIZEOF(array) (sizeof(array)/sizeof(*(array)))

//XXX if instrumentation is not enabled, this line should not be in the compilation
void pwned(char* msg) __attribute__((no_instrument_function));

void
__attribute__ ((noreturn))
pwned(char* msg)
{
	FILE* out = fopen("/dev/tty", "w");
	fprintf(out, "*** Watchman: %s ***: program terminated\n", msg);
	exit(1);
}

//no really, exit
__asm__ (
"nop\n"
"call exit\n"
"nop\n"
);

//XXX make a list of all unsafe functions to protect here
/*
This is the template to generate a check for
all easily patchable vulnerable functions.

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

*/
