#pragma once

#include <portugol/variant.h>

typedef struct Runtime Runtime;

Runtime*
runtime_create(void);

void
runtime_destroy(Runtime** runtime);

Variant*
runtime_get(Runtime* runtime,
            char* name);

Variant*
runtime_heap_push(Runtime* runtime,
                  char* name,
                  Variant value);

Variant
runtime_heap_pop(Runtime* runtime);

Variant*
runtime_stack_push(Runtime* runtime,
                   char* name,
                   Variant value);

Variant
runtime_stack_pop(Runtime* runtime);

Variant*
runtime_scope_get(Runtime* runtime);

Variant*
runtime_scope_push(Runtime* runtime,
                   int is_function);

Variant*
runtime_scope_push_named(Runtime* runtime,
                         int is_function,
                         char* name);

Variant
runtime_scope_pop(Runtime* runtime);

int
runtime_scope_is_returning(Runtime* runtime);

Runtime*
runtime_scope_set_returning(Runtime* runtime);

Runtime*
runtime_clear(Runtime* runtime);

void
runtime_print(Runtime* runtime);
