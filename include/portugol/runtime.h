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
runtime_push(Runtime* runtime,
             char* name,
             Variant value);

Variant
runtime_pop(Runtime* runtime);

Runtime*
runtime_clear(Runtime* runtime);

Variant*
runtime_push_scope(Runtime* runtime);

Variant*
runtime_push_scope_named(Runtime* runtime,
                         char* name);

Variant*
runtime_get_scope(Runtime* runtime);

Variant
runtime_pop_scope(Runtime* runtime);

void
runtime_print(Runtime* runtime);
