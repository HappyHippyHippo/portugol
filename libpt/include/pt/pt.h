#pragma once

#include <stdint.h>
#include <stdlib.h>

#include "pt/pt_error.h"
#include "pt/pt_lang.h"
#include "pt/pt_runmode.h"

#include "pt/data/pt_data.h"
#include "pt/data/pt_data_strategy.h"
#include "pt/data/pt_data_type.h"

/// @brief
typedef struct
{
    /// @brief
    struct
    {
        /// @brief
        ///
        /// @return
        pt_error_t
        (* get) (void);

        /// @brief
        ///
        /// @param error
        ///
        /// @return
        pt_error_t
        (* set) (const pt_error_t error);

        /// @brief
        ///
        /// @return
        pt_error_t
        (* clear) (void);
    } error;

    /// @brief
    struct
    {
        /// @brief
        ///
        /// @return
        pt_runmode_t
        (* get) (void);

        /// @brief
        ///
        /// @param mode
        ///
        /// @return
        pt_runmode_t
        (* set) (const pt_runmode_t mode);
    } runmode;

    /// @brief
    struct
    {
        /// @brief
        struct {
            /// @brief
            ///
            /// @param datatype
            ///
            /// @return
            pt_data_strategy_t *
            (* get_by_type) (pt_data_type_t datatype);

            /// @brief
            ///
            /// @param name
            ///
            /// @return
            pt_data_strategy_t *
            (* get_by_name) (const char * name);

            /// @brief
            ///
            /// @param strategy
            ///
            /// @return
            pt_error_t
            (* add) (pt_data_strategy_t * strategy);

            /// @brief
            ///
            /// @return
            pt_error_t
            (* clear) (void);
        } pool;

        /// @brief
        struct {
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
            (* add_method) (pt_data_strategy_t * strategy,
                            pt_data_type_t datatype,
                            const char * name,
                            pt_data_type_t params[],
                            pt_data_method_callback_t cb);
        } strategy;

        /// @brief
        ///
        /// @param datatype
        ///
        /// @return
        pt_data_t
        (* alloc_by_type) (pt_data_type_t datatype);

        /// @brief
        ///
        /// @param name
        ///
        /// @return
        pt_data_t
        (* alloc_by_name) (const char * name);

        /// @brief
        ///
        /// @param data
        ///
        /// @return
        pt_error_t
        (* free) (pt_data_t * data);

        /// @brief
        ///
        /// @param data
        ///
        /// @return
        size_t
        (* get_size) (pt_data_t data);

        /// @brief
        ///
        /// @param data
        /// @param datatype
        ///
        /// @return
        int
        (* is_cast) (pt_data_t data,
                     pt_data_type_t datatype);

        /// @brief
        ///
        /// @param data
        /// @param datatype
        ///
        /// @return
        int
        (* is_elevate) (pt_data_t data,
                        pt_data_type_t datatype);

        /// @brief
        ///
        /// @param data
        /// @param datatype
        ///
        /// @return
        pt_data_method_t
        (* get_cast) (pt_data_t data,
                      pt_data_type_t datatype);

        /// @brief
        ///
        /// @param data
        /// @param datatype
        /// @param dest
        ///
        /// @return
        void **
        (* cast) (pt_data_t data,
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
        (* cast_ex) (pt_data_t data,
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
        (* is_method) (pt_data_t data,
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
        (* get_method) (pt_data_t data,
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
        (* method) (pt_data_t data,
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
        (* method_ex) (pt_data_t data,
                       pt_data_method_t method,
                       void * args[],
                       void ** dest);
    } data;
} pt_t;

/// @brief
extern pt_t pt;
