#include <mem.h>

/*******************************************************************************
 * PUBLIC FUNCTIONS
 ******************************************************************************/

void*
mem_malloc(size_t size)
{
    return malloc(size);
} /* end of : void*
              mem_malloc(size_t size) */

void*
mem_calloc(size_t nelem,
           size_t size)
{
    return calloc(nelem, size);
} /* end of : void*
              mem_calloc(size_t nelem,
                         size_t size) */

void*
mem_realloc(void* ptr,
            size_t size)
{
    return realloc(ptr, size);
} /* end of : void*
              mem_realloc(void* ptr,
                          size_t size) */

void
mem_free(void* ptr)
{
    free(ptr);
} /* end of : void
              mem_free(void* ptr) */
