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
pt_data_t
pt_data_alloc_by_type (pt_data_type_t datatype);

/// @brief
///
/// @param name
///
/// @return
pt_data_t
pt_data_alloc_by_name (const char * name);

/// @brief
///
/// @param data
///
/// @return
pt_error_t
pt_data_free (pt_data_t * data);

/// @brief
///
/// @param data
///
/// @return
size_t
pt_data_get_size (pt_data_t data);

/// @brief
///
/// @param data
/// @param datatype
///
/// @return
int
pt_data_is_cast (pt_data_t data,
                 pt_data_type_t datatype);

/// @brief
///
/// @param data
/// @param datatype
///
/// @return
int
pt_data_is_elevate (pt_data_t data,
                    pt_data_type_t datatype);

/// @brief
///
/// @param data
/// @param datatype
///
/// @return
pt_data_method_t
pt_data_get_cast (pt_data_t data,
                  pt_data_type_t datatype);

/// @brief
///
/// @param data
/// @param datatype
/// @param dest
///
/// @return
void **
pt_data_cast (pt_data_t data,
              pt_data_type_t datatype,
              void ** dest);

/// @brief
///
/// @param data
/// @param method
/// @param dest
///
/// @return
void **
pt_data_cast_ex (pt_data_t data,
                 pt_data_method_t method,
                 void ** dest);

/// @brief
///
/// @param data
/// @param name
/// @param params
///
/// @return
int
pt_data_is_method (pt_data_t data,
                   const char * name,
                   pt_data_type_t params[]);

/// @brief
///
/// @param data
/// @param name
/// @param params
///
/// @return
pt_data_method_t
pt_data_get_method (pt_data_t data,
                    const char * name,
                    pt_data_type_t params[]);

/// @brief
///
/// @param data
/// @param name
/// @param params
/// @param args
/// @param dest
///
/// @return
void **
pt_data_method (pt_data_t data,
                const char * name,
                pt_data_type_t params[],
                void * args[],
                void ** dest);

/// @brief
///
/// @param data
/// @param method
/// @param args
/// @param dest
///
/// @return
void **
pt_data_method_ex (pt_data_t data,
                   pt_data_method_t method,
                   void * args[],
                   void ** dest);
