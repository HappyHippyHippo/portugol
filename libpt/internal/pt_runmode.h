#pragma once

#include <stdint.h>

#include "pt/pt.h"

// -----------------------------------------------------------------------------
// INTERNAL FUNCTION ALLUSIONS
// -----------------------------------------------------------------------------

/// @brief
///
/// @return
pt_runmode_t
pt_runmode_get (void);

/// @brief
///
/// @param runmode
///
/// @return
pt_runmode_t
pt_runmode_set (const pt_runmode_t runmode);
