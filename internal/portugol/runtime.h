#pragma once

#include <portugol/runtime.h>

typedef struct Stack
{
    char* name;
    Variant value;

    struct Stack* prev;
} Stack;

typedef struct Heap
{
    char* name;
    Variant value;

    struct Heap* prev;
} Heap;

typedef struct Scope
{
    struct Stack* stack;
    struct Scope* prev;
    int is_function;
} Scope;

struct Runtime
{
    Heap* heap;
    Stack* stack;
    Scope* scope;
};
