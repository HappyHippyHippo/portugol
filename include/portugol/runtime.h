#pragma once

#include <stdint.h>

#include <portugol/variant.h>

/// @brief
///
/// @param name
/// @param type
/// @return
Variant*
runtime_add(const char* name,
            const VType type);

/// @brief
///
/// @param name
/// @return
#define runtime_add_boolean(name) \
    (runtime_add(name,            \
                 VBOOLEAN))

/// @brief
///
/// @param name
/// @return
#define runtime_add_int32(name) \
    (runtime_add(name,          \
                 VINT32))

/// @brief
///
/// @param name
/// @return
#define runtime_add_float32(name) \
    (runtime_add(name,            \
                 VFLOAT32))

/// @brief
///
/// @param name
/// @return
#define runtime_add_text(name) \
    (runtime_add(name,         \
                 VTEXT))

/// @brief
///
/// @param name
/// @return
#define runtime_add_pointer(name) \
    (runtime_add(name,            \
                 VPOINTER))

/// @brief
///
/// @param name
/// @return
#define runtime_add_function(name) \
    (runtime_add(name,             \
                 VFUNCTION))

/// @brief
///
/// @param name
/// @param type
/// @return
Variant*
runtime_heap_add(const char* name,
                 const VType type);

/// @brief
///
/// @param name
/// @return
#define runtime_heap_add_boolean(name) \
    (runtime_heap_add(name,            \
                      VBOOLEAN))

/// @brief
///
/// @param name
/// @return
#define runtime_heap_add_int32(name) \
    (runtime_heap_add(name,          \
                      VINT32))

/// @brief
///
/// @param name
/// @return
#define runtime_heap_add_float32(name) \
    (runtime_heap_add(name,            \
                      VFLOAT32))

/// @brief
///
/// @param name
/// @return
#define runtime_heap_add_text(name) \
    (runtime_heap_add(name,         \
                      VTEXT))

/// @brief
///
/// @param name
/// @return
#define runtime_heap_add_pointer(name) \
    (runtime_heap_add(name,            \
                      VPOINTER))

/// @brief
///
/// @param name
/// @return
#define runtime_heap_add_function(name) \
    (runtime_heap_add(name,             \
                      VFUNCTION))

/// @brief
///
/// @param name
/// @param type
/// @return
Variant*
runtime_stack_add(const char* name,
                  const VType type);

/// @brief
///
/// @param name
/// @return
#define runtime_stack_add_boolean(name) \
    (runtime_stack_add(name,            \
                       VBOOLEAN))

/// @brief
///
/// @param name
/// @return
#define runtime_stack_add_int32(name) \
    (runtime_stack_add(name,          \
                       VINT32))

/// @brief
///
/// @param name
/// @return
#define runtime_stack_add_float32(name) \
    (runtime_stack_add(name,            \
                       VFLOAT32))

/// @brief
///
/// @param name
/// @return
#define runtime_stack_add_text(name) \
    (runtime_stack_add(name,         \
                       VTEXT))

/// @brief
///
/// @param name
/// @return
#define runtime_stack_add_pointer(name) \
    (runtime_stack_add(name,            \
                       VPOINTER))

/// @brief
///
/// @param name
/// @return
#define runtime_stack_add_function(name) \
    (runtime_stack_add(name,             \
                       VFUNCTION))

/// @brief
///
/// @param name
/// @param type
/// @return
Variant*
runtime_stack_push_function(const char* name,
                            const VType type);

/// @brief
///
/// @param name
/// @return
#define runtime_stack_push_function_boolean(name) \
    (runtime_stack_push_function(name,            \
                                 VBOOLEAN))

/// @brief
///
/// @param name
/// @return
#define runtime_stack_push_function_int32(name) \
    (runtime_stack_push_function(name,          \
                                 VINT32))

/// @brief
///
/// @param name
/// @return
#define runtime_stack_push_function_float32(name) \
    (runtime_stack_push_function(name,            \
                                 VFLOAT32))

/// @brief
///
/// @param name
/// @return
#define runtime_stack_push_function_text(name) \
    (runtime_stack_push_function(name,         \
                                 VTEXT))

/// @brief
///
/// @param name
/// @return
#define runtime_stack_push_function_pointer(name) \
    (runtime_stack_push_function(name,            \
                                 VPOINTER))

/// @brief
///
/// @param name
/// @return
#define runtime_stack_push_function_function(name) \
    (runtime_stack_push_function(name,             \
                                 VFUNCTION))

/// @brief
void
runtime_stack_push_scope(void);

/// @brief
void
runtime_stack_pop(void);

/// @brief
///
/// @param name
/// @return
Variant*
runtime_get(const char* name);

/// @brief
///
/// @param name
/// @return
Variant*
runtime_get_function_scope(void);

/// @brief
///
/// @return
int
runtime_is_returning(void);

/// @brief
void
runtime_set_returning(void);

/// @brief
void
runtime_clear(void);

/// @brief
void
runtime_output(void);
