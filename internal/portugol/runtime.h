#pragma once

#include <portugol/runtime.h>

typedef struct RuntimeEntry
{
    struct RuntimeEntry* prev;
    char* name;
    Variant value;
    int is_scope;
    int is_function;
    int is_returning;
} RuntimeEntry;

typedef struct
{
    int is_init;

    struct
    {
        RuntimeEntry* top;
        size_t size;
    } heap;

    struct
    {
        RuntimeEntry* top;
        size_t size;

        RuntimeEntry* function;
    } stack;
} Runtime;

/// @brief
void
runtime_init(void);

/// @brief
void
runtime_uninit(void);

/// @brief
///
/// @param name
/// @param size
/// @param type
/// @return
RuntimeEntry*
runtime_heap_push(const char* name,
                  const VType type);

/// @brief
///
/// @param name
/// @param size
/// @param type
/// @return
RuntimeEntry*
runtime_stack_push(const char* name,
                   const VType type);
