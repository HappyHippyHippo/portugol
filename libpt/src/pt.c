#include "internal/pt.h"

#include "internal/pt_error.h"
#include "internal/pt_runmode.h"

#include "internal/data/pt_data.h"
#include "internal/data/pt_data_pool.h"
#include "internal/data/pt_data_strategy.h"

/// @brief
pt_t pt =
{
    .error =
    {
        pt_error_get,
        pt_error_set,
        pt_error_clear
    },

    .runmode =
    {
        pt_runmode_get,
        pt_runmode_set
    },

    .data =
    {
        .pool =
        {
            pt_data_pool_get_by_type,
            pt_data_pool_get_by_name,
            pt_data_pool_add,
            pt_data_pool_clear
        },

        .strategy =
        {
            pt_data_strategy_add_method
        },

        pt_data_alloc_by_type,
        pt_data_alloc_by_name,
        pt_data_free,
        pt_data_get_size,
        pt_data_is_cast,
        pt_data_is_elevate,
        pt_data_get_cast,
        pt_data_cast,
        pt_data_cast_ex,
        pt_data_is_method,
        pt_data_get_method,
        pt_data_method,
        pt_data_method_ex
    }
};
