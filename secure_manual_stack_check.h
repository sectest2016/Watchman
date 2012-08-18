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


//-----------------------------
//-----------------------------
//manually implemented early stack check
//-----------------------------
//-----------------------------

//TODO make a honey pot stack check fail

#define STACK_CHK_FAIL_ASM "CALL __stack_chk_fail\n"

#ifdef __i386__

	//v1
	//TODO look into xor %eax,%eax instead of mov
	//TODO is mov 0x0 eax needed at all?
	//XXX it seems the canary might be in a couple of places, check both places? TEST THIS MORE
	/*#define STACK_CHECK_ASM \
	"mov $0x0,%eax\n" 	  \
	"mov 0x2c(%esp),%edx\n"   \
	"xor %gs:0x14,%edx;\n"    \
	"je . + 7\n" 		  \
	STACK_CHK_FAIL_ASM*/


	//v2
	/*#define STACK_CHECK_ASM \
	"mov $0x0,%eax\n" 	  \
	"mov -0xc(%ebp),%edx\n"   \
	"xor %gs:0x14,%edx;\n"    \
	"je . + 7\n" 		  \
	STACK_CHK_FAIL_ASM*/

	//v3
	#define STACK_CHECK_ASM \
	"mov -0xc(%ebp),%edx\n" \
	"xor %gs:0x14,%edx;\n"  \
	"je . + 13\n" 		\
	"mov 0x2c(%esp),%edx\n" \
	"xor %gs:0x14,%edx;\n"  \
	"je . + 7\n" 		\
	STACK_CHK_FAIL_ASM


#elif defined __x86_64__
	#warning "secure.h not currenty implemented for i386"
#elif defined __powerpc64__
	#warning "secure.h not currenty implemented for powerpc64"
#elif defined __powerpc__
	#warning "secure.h not currenty implemented for powerpc"
#elif defined __sparc__ && defined __arch64__
	#warning "secure.h not currenty implemented for sparc 64"
#elif defined __sparc__
	#warning "secure.h not currenty implemented for sparc"
#elif defined __s390x__
	#warning "secure.h not currenty implemented for s390x"
#elif defined __s390__
	#warning "secure.h not currenty implemented for s390"
#elif defined __ia64__
	#warning "secure.h not currenty implemented for ia64"
#else
	extern uintptr_t __stack_chk_guard;
	# define STACK_CHK_GUARD __stack_chk_guard
#endif

#define STACK_CHECK_FAIL \
__asm__ __volatile__( \
STACK_CHK_FAIL_ASM \
)

#define STACK_CHECK \
__asm__ __volatile__( \
STACK_CHECK_ASM \
) 

