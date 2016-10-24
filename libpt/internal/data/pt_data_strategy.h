#pragma once

#include <stdlib.h>

#include "pt/pt.h"

// -----------------------------------------------------------------------------
// INTERNAL TYPEDEFS
// -----------------------------------------------------------------------------

/// @brief
typedef struct pt_data_method_entry_t pt_data_method_entry_t;

/// @brief
struct pt_data_strategy_t
{
    /// @brief
    pt_data_type_t datatype;

    /// @brief
    char * name;

    /// @brief
    struct {
        /// @brief
        ///
        /// @param strategy
        ///
        /// @return
        void *
        (* alloc) (pt_data_strategy_t * strategy);

        /// @brief
        ///
        /// @param strategy
        /// @param data
        ///
        /// @return
        pt_error_t
        (* free) (pt_data_strategy_t * strategy,
                  void ** data);

        /// @brief
        ///
        /// @param strategy
        ///
        /// @return
        size_t
        (* get_init_size) (pt_data_strategy_t * strategy);

        /// @brief
        ///
        /// @param strategy
        /// @param data
        ///
        /// @return
        size_t
        (* get_current_size) (pt_data_strategy_t * strategy,
                              void * data);


        /// @brief
        ///
        /// @param strategy
        /// @param datatype
        ///
        /// @return
        int
        (* is_cast) (pt_data_strategy_t * strategy,
                     pt_data_type_t datatype);

        /// @brief
        ///
        /// @param strategy
        /// @param datatype
        ///
        /// @return
        pt_data_method_t
        (* get_cast) (pt_data_strategy_t * strategy,
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
        (* cast) (pt_data_strategy_t * strategy,
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
        (* cast_ex) (pt_data_strategy_t * strategy,
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
        (* is_method) (pt_data_strategy_t * strategy,
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
        (* get_method) (pt_data_strategy_t * strategy,
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
        (* method) (pt_data_strategy_t * strategy,
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
        (* method_ex) (pt_data_strategy_t * strategy,
                       pt_data_method_t method,
                       void * src,
                       void * args[],
                       void ** dest);
    } cb;

    /// @brief
    pt_data_method_entry_t * methods;
};

/// @brief
struct pt_data_method_entry_t
{
    /// @brief
    struct pt_data_method_entry_t * next;

    /// @brief
    pt_data_type_t datatype;

    /// @brief
    char * name;

    /// @brief
    pt_data_type_t * params;

    /// @brief
    size_t param_count;

    /// @brief
    pt_data_method_callback_t cb;
};

// -----------------------------------------------------------------------------
// INTERNAL FUNCTION ALLUSIONS
// -----------------------------------------------------------------------------

/// @brief
///
/// @param strategy
///
/// @return
pt_error_t
pt_data_strategy_destroy (pt_data_strategy_t ** strategy);

/// @brief
///
/// @param strategy
/// @param name
/// @param params
///
/// @return
pt_data_method_entry_t *
pt_data_strategy_get_method (pt_data_strategy_t * strategy,
                             const char * name,
                             pt_data_type_t params[]);

/// @brief
///
/// @param strategy
/// @param datatype
/// @param name
/// @param params
/// @param cb
///
/// @return
pt_data_strategy_t *
pt_data_strategy_add_method (pt_data_strategy_t * strategy,
                             pt_data_type_t datatype,
                             const char * name,
                             pt_data_type_t params[],
                             pt_data_method_callback_t cb);
