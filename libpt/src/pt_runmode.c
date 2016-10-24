#include "internal/pt_runmode.h"

// -----------------------------------------------------------------------------
// PRIVATE GLOBAL VARIABLES/SINGLETONS
// -----------------------------------------------------------------------------

/// @brief
pt_runmode_t pt_runmode = PT_RUNMODE_NORMAL;

// -----------------------------------------------------------------------------
// INTERNAL FUNCTIONS
// -----------------------------------------------------------------------------

pt_runmode_t
pt_runmode_get (void)
{
    return pt_runmode;
} /* end of : pt_runmode_t
              pt_runmode_get (void) */

pt_runmode_t
pt_runmode_set (const pt_runmode_t runmode)
{
    return pt_runmode = runmode;
} /* end of : pt_runmode_t
              pt_runmode_set (const pt_runmode_t runmode) */
