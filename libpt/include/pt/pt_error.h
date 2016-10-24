#pragma once

/// @brief
typedef enum
{
    PT_ERROR_OK                         = 0,
    PT_ERROR_NOT_IMPLEMENTED            = -1,
    PT_ERROR_NO_MEMORY                  = -2,

    PT_ERROR_INVALID_POINTER            = -10,
    PT_ERROR_INVALID_ARGUMENT           = -11,

    PT_ERROR_EMPTY                      = -20,
    PT_ERROR_FULL                       = -21,
    PT_ERROR_NOT_FOUND                  = -22,
    PT_ERROR_DUPLICATE                  = -23
} pt_error_t;
