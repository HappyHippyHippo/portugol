#pragma once

#include "pt/pt.h"

// -----------------------------------------------------------------------------
// INTERNAL FUNCTION ALLUSIONS
// -----------------------------------------------------------------------------

/// @brief
///
/// @param datatype
///
/// @return
pt_data_strategy_t *
pt_data_pool_get_by_type (pt_data_type_t datatype);

/// @brief
///
/// @param name
///
/// @return
pt_data_strategy_t *
pt_data_pool_get_by_name (const char * name);

/// @brief
///
/// @param strategy
///
/// @return
pt_error_t
pt_data_pool_add (pt_data_strategy_t * strategy);

/// @brief
///
/// @return
pt_error_t
pt_data_pool_clear (void);
