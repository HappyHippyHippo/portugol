#pragma once

#include <portugol/runtime.h>

typedef struct Heap
{
    char* name;
    Variant value;

    struct Heap* prev;
} Heap;

typedef struct Stack
{
    char* name;
    Variant value;
    int is_scope;
    int is_function;
    int is_returning;

    struct Stack* prev;
} Stack;

struct Runtime
{
    Heap* heap;
    Stack* stack;
};
