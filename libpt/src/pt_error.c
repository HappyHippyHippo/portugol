#include "internal/pt_error.h"

// -----------------------------------------------------------------------------
// PRIVATE GLOBAL VARIABLES/SINGLETONS
// -----------------------------------------------------------------------------

/// @brief
pt_error_t pt_error = PT_ERROR_OK;

// -----------------------------------------------------------------------------
// INTERNAL FUNCTIONS
// -----------------------------------------------------------------------------

pt_error_t
pt_error_get (void)
{
    return pt_error;
} /* end of : pt_error_t
              pt_error_get (void) */

pt_error_t
pt_error_set (const pt_error_t error)
{
    return pt_error = error;
} /* end of : pt_error_t
              pt_error_set (const pt_error_t error) */

pt_error_t
pt_error_clear (void)
{
    return pt_error = PT_ERROR_OK;
} /* end of : pt_error_t
              pt_error_clear (void) */
