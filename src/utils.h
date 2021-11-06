#ifndef _UTILS_H
#define _UTILS_H
#include <stdio.h>
#include <assert.h>

#ifdef DEBUG_BUILD
#  define debug_assert(condition) assert(condition)
#else /* DEBUG_BUILD */
#  define debug_assert(condition)
#endif /* DEBUG_BUILD */

#endif /* _UTILS_H */
