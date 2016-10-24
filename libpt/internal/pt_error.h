#pragma once

#include <stdint.h>

#include "pt/pt.h"

// -----------------------------------------------------------------------------
// INTERNAL FUNCTION ALLUSIONS
// -----------------------------------------------------------------------------

/// @brief
///
/// @return
pt_error_t
pt_error_get (void);

/// @brief
///
/// @param error
///
/// @return
pt_error_t
pt_error_set (const pt_error_t error);

/// @brief
///
/// @return
pt_error_t
pt_error_clear (void);
