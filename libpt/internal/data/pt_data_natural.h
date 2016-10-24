#pragma once

#include <stdlib.h>

#include "pt/pt.h"

// -----------------------------------------------------------------------------
// INTERNAL FUNCTION ALLUSIONS
// -----------------------------------------------------------------------------

/// @brief
///
/// @param strategy
/// @param datatype
///
/// @return
int
pt_data_natural_is_cast (pt_data_strategy_t * strategy,
                         pt_data_type_t datatype);

/// @brief
///
/// @param strategy
/// @param datatype
///
/// @return
pt_data_method_t
pt_data_natural_get_cast (pt_data_strategy_t * strategy,
                          pt_data_type_t datatype);

/// @brief
///
/// @param strategy
/// @param datatype
/// @param src
/// @param dest
///
/// @return
void **
pt_data_natural_cast (pt_data_strategy_t * strategy,
                      pt_data_type_t datatype,
                      void * src,
                      void ** dest);

/// @brief
///
/// @param strategy
/// @param method
/// @param src
/// @param dest
///
/// @return
void **
pt_data_natural_cast_ex (pt_data_strategy_t * strategy,
                         pt_data_method_t method,
                         void * src,
                         void ** dest);

/// @brief
///
/// @param strategy
/// @param name
/// @param params
///
/// @return
int
pt_data_natural_is_method (pt_data_strategy_t * strategy,
                           const char * name,
                           pt_data_type_t params[]);

/// @brief
///
/// @param strategy
/// @param name
/// @param params
///
/// @return
pt_data_method_t
pt_data_natural_get_method (pt_data_strategy_t * strategy,
                            const char * name,
                            pt_data_type_t params[]);

/// @brief
///
/// @param strategy
/// @param name
/// @param params
/// @param src
/// @param args
/// @param dest
///
/// @return
void **
pt_data_natural_method (pt_data_strategy_t * strategy,
                        const char * name,
                        pt_data_type_t params[],
                        void * src,
                        void * args[],
                        void ** dest);

/// @brief
///
/// @param strategy
/// @param method
/// @param src
/// @param args
/// @param dest
///
/// @return
void **
pt_data_natural_method_ex (pt_data_strategy_t * strategy,
                           pt_data_method_t method,
                           void * src,
                           void * args[],
                           void ** dest);
