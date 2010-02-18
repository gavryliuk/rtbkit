/* atomic_ops.h                                                    -*- C++ -*-
   Jeremy Barnes,24 October 2009
   Copyright (c) 2009 Jeremy Barnes.  All rights reserved.

   Atomic operations.
*/

#ifndef __arch__atomic_ops_h__
#define __arch__atomic_ops_h__

#include "cmp_xchg.h"
#include "jml/compiler/compiler.h"


namespace ML {


template<typename Val1, typename Val2>
void atomic_accumulate(Val1 & value, const Val2 & increment)
{
    Val1 old_val = value, new_val;
    do {
        new_val = old_val + increment;
    } while (!JML_LIKELY(cmp_xchg(value, old_val, new_val)));
}

template<typename Val1, typename Val2>
void atomic_accumulate(Val1 * old, const Val2 * increment, int n)
{
    for (unsigned i = 0;  i < n;  ++i)
        atomic_accumulate(old[i], increment[i]);
}

template<typename Val1, typename Val2>
void atomic_add(Val1 & val, const Val2 & amount)
{
    asm ("lock add %[amount], %[val]\n\t"
         : [val] "=m" (val)
         : [amount] "r" (amount)
         : "cc");
}

JML_ALWAYS_INLINE void memory_barrier()
{
    // GCC < 4.4 doesn't do this properly
    // See http://gcc.gnu.org/bugzilla/show_bug.cgi?id=36793
#if 0
    __sync_synchronize();
#else
    asm volatile ( "mfence; \n" );
#endif
}

} // file scope


#endif /* __arch__atomic_ops_h__ */
