#pragma once

#include <portugol/runtime.h>

typedef struct Stack
{
    char* name;
    Variant value;

    struct Stack* prev;
} Stack;

typedef struct Scope
{
    struct Stack* stack;
    struct Scope* prev;
} Scope;

struct Runtime
{
    Stack* stack;
    Scope* scope;
};
