#include <error.h>

int _error = 0;

int
error_get(void)
{
    return _error;
} /* end of : int
              error_get(void) */

int
error_set(const int error)
{
    return _error = error;
} /* end of : int
              error_set(const int error) */

int
error_clear(void)
{
    return _error = 0;
} /* end of : int
              error_clear(void) */
