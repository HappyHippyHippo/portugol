#pragma once

/// @brief
typedef struct pt_data_strategy_t pt_data_strategy_t;

/// @brief
///
/// @param src
/// @param args
/// @param dest
///
/// @return
typedef
    void **
    (* pt_data_method_callback_t) (void * src,
                                   void ** args,
                                   void ** dest);

/// @brief
typedef struct
{
    /// @brief
    pt_data_method_callback_t cb;
} pt_data_method_t;
