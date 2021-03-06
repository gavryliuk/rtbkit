/* threads.h                                                       -*- C++ -*-
   Jeremy Barnes, 30 January 2005
   Copyright (c) 2005 Jeremy Barnes.  All rights reserved.

   This file is part of "Jeremy's Machine Learning Library", copyright (c)
   1999-2005 Jeremy Barnes.
   
   This program is available under the GNU General Public License, the terms
   of which are given by the file "license.txt" in the top level directory of
   the source code distribution.  If this file is missing, you have no right
   to use the program; please contact the author.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
   for more details.

   ---

   Catch-all include for architecture dependent threading constructions.
*/

#ifndef __arch__threads_h__
#define __arch__threads_h__ 1

#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <mutex>

typedef std::recursive_mutex Lock;
typedef std::unique_lock<Lock> Guard;

// c++14
//typedef std::shared_lock<Lock> Read_Guard;
//typedef std::unique_lock<Lock> Read_Guard;
//typedef std::unique_lock<Lock> Write_Guard;

inline pid_t gettid()
{
    return (pid_t) syscall(SYS_gettid);
}


#endif /* __arch__threads_h__ */
