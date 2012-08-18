#!/bin/sh

#Watchman - A memory corruption detection and security system for GCC.
#Copyright (C) 2012 Eric Wimberley
#
#This program is free software; you can redistribute it and/or
#modify it under the terms of the GNU General Public License
#as published by the Free Software Foundation; either version 2
#of the License, or (at your option) any later version.
#
#This program is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.
#
#You should have received a copy of the GNU General Public License
#along with this program; if not, write to the Free Software
#Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.



FILES=$(echo *.c)

#TODO add ability to select watchman features as command arguments
for file in $FILES
    do
        echo "Patching $file with Watchman"

        mv $file $file.tmp
        sed '1i\
' $file.tmp > $file 
	rm $file.tmp
done
