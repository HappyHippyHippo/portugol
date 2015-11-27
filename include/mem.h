#pragma once

#include <stdlib.h>

/// @brief
///
/// @param size
/// @return
void*
mem_malloc(size_t size);

/// @brief
///
/// @param nsize
/// @param size
/// @return
void*
mem_calloc(size_t nelem,
           size_t size);

/// @brief
///
/// @param ptr
/// @param size
/// @return
void*
mem_realloc(void* ptr,
            size_t size);

/// @brief
///
/// @param ptr
void
mem_free(void* ptr);
