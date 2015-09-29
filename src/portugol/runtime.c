#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <internal/portugol/ast.h>
#include <internal/portugol/runtime.h>

#define SCOPE_RETURN "retorna"

Runtime*
runtime_create(void)
{
    Runtime* runtime;
    if ((runtime = malloc(sizeof(Runtime))) != NULL)
    {
        runtime->heap  = NULL;
        runtime->stack = NULL;
    }

    return runtime;
}

void
runtime_destroy(Runtime** runtime)
{
    if (runtime == NULL || *runtime == NULL)
        return;

    runtime_clear(*runtime);
    free(*runtime);
    *runtime = NULL;
}

Variant*
runtime_get(Runtime* runtime,
            char* name)
{
    if (runtime == NULL || name == NULL)
        return NULL;

    Stack* it_stack = runtime->stack;
    while (it_stack != NULL && !it_stack->is_function)
    {
        if (strcmp(name, it_stack->name) == 0)
            return &it_stack->value;
        it_stack = it_stack->prev;
    }

    Heap* it_heap = runtime->heap;
    while (it_heap != NULL)
    {
        if (strcmp(name, it_heap->name) == 0)
            return &it_heap->value;
        it_heap = it_heap->prev;
    }

    return NULL;
}

Variant*
runtime_heap_push(Runtime* runtime,
                  char* name,
                  Variant value)
{
    if (runtime == NULL || name == NULL)
        return NULL;

    Heap* heap;
    if ((heap = malloc(sizeof(Heap))) == NULL)
        return NULL;

    heap->name  = name;
    heap->value = variant_copy(value);
    heap->prev  = runtime->heap;

    runtime->heap = heap;

    return &heap->value;
}

Variant
runtime_heap_pop(Runtime* runtime)
{
    if (runtime == NULL || runtime->heap == NULL)
        return variant_init_int32(0);

    Variant result = runtime->heap->value;

    Heap* del = runtime->heap;
    runtime->heap = runtime->heap->prev;
    free(del);

    return result;
}

Variant*
runtime_stack_push(Runtime* runtime,
                   char* name,
                   Variant value)
{
    if (runtime == NULL || name == NULL)
        return NULL;

    Stack* stack;
    if ((stack = malloc(sizeof(Stack))) == NULL)
        return NULL;

    stack->name         = name;
    stack->value        = variant_copy(value);
    stack->is_scope     = 0;
    stack->is_function  = 0;
    stack->is_returning = 0;
    stack->prev         = runtime->stack;

    runtime->stack      = stack;

    return &stack->value;
}

Variant
runtime_stack_pop(Runtime* runtime)
{
    if (runtime == NULL || runtime->stack == NULL)
        return variant_init_int32(0);

    Variant result = runtime->stack->value;

    Stack* del = runtime->stack;
    runtime->stack = runtime->stack->prev;
    free(del);

    return result;
}

Variant*
runtime_scope_get(Runtime* runtime)
{
    if (runtime == NULL)
        return NULL;

    Stack* stack = runtime->stack;
    while (stack != NULL && !stack->is_function)
        stack = stack->prev;

    if (stack)
        return &stack->value;

    return NULL;
}

Variant*
runtime_scope_push(Runtime* runtime,
                   int is_function)
{
    return runtime_scope_push_named(runtime, is_function, SCOPE_RETURN);
}

Variant*
runtime_scope_push_named(Runtime* runtime,
                         int is_function,
                         char* name)
{
    if (runtime == NULL)
        return NULL;

    Stack* stack;
    if ((stack = malloc(sizeof(Stack))) == NULL)
        return NULL;

    stack->name         = name;
    stack->value        = variant_init_int32(0);
    stack->is_scope     = 1;
    stack->is_function  = is_function;
    stack->is_returning = 0;
    stack->prev         = runtime->stack;

    runtime->stack      = stack;

    return &stack->value;
}

Variant
runtime_scope_pop(Runtime* runtime)
{
    if (runtime == NULL && runtime->stack)
        return variant_init_int32(0);

    while (runtime->stack && !runtime->stack->is_scope)
    {
        Variant var = runtime_stack_pop(runtime);
        variant_uninit(&var);
    }

    return runtime_stack_pop(runtime);
}

int
runtime_scope_is_returning(Runtime* runtime)
{
    if (runtime == NULL)
        return 0;

    Stack* stack = runtime->stack;
    while (stack != NULL && !stack->is_function)
        stack = stack->prev;

    if (stack)
        return stack->is_returning;

    return 0;
}

Runtime*
runtime_scope_set_returning(Runtime* runtime)
{
    if (runtime == NULL)
        return NULL;

    Stack* stack = runtime->stack;
    while (stack != NULL && !stack->is_function)
        stack = stack->prev;

    if (stack)
        stack->is_returning = 1;

    return runtime;
}

Runtime*
runtime_clear(Runtime* runtime)
{
    if (runtime == NULL)
        return runtime;

    while (runtime->heap != NULL)
    {
        Variant var = runtime_heap_pop(runtime);
        variant_uninit(&var);
    }

    while (runtime->stack != NULL)
    {
        Variant var = runtime_stack_pop(runtime);
        variant_uninit(&var);
    }

    return runtime;
}

void
runtime_print(Runtime* runtime)
{
    if (runtime == NULL)
        return;

    printf("------------------------------- RUNTIME HEAP ------------------------------\n");
    Heap* heap = runtime->heap;
    while (heap != NULL)
    {
        switch (heap->value.type)
        {
            case VBOOLEAN:
                printf("%18p [0:0] %20s ->  boolean(%d)",
                       (void*) heap,
                       heap->name,
                       heap->value.value.boolean);
                break;
            case VINT32:
                printf("%18p [0:0] %20s ->    int32(%d)",
                       (void*) heap,
                       heap->name,
                       heap->value.value.int32);
                break;
            case VFLOAT32:
                printf("%18p [0:0] %20s ->  float32(%f)",
                       (void*) heap,
                       heap->name,
                       heap->value.value.float32);
                break;
            case VTEXT:
                printf("%18p [0:0] %20s ->     text(%s)",
                       (void*) heap,
                       heap->name,
                       heap->value.value.text);
                break;
            case VFUNCTION:
                printf("%18p [0:0] %20s -> function(%p)",
                       (void*) heap,
                       heap->name,
                       (void*) heap->value.value.function);
                break;
            default:
                break;
        }

        printf("\n");
        heap = heap->prev;
    }
    printf("---------------------------------------------------------------------------\n");
    printf("\n");

    printf("------------------------------ RUNTIME STACK ------------------------------\n");
    Stack* stack = runtime->stack;
    while (stack != NULL)
    {
        switch (stack->value.type)
        {
            case VBOOLEAN:
                printf("%18p [%d:%d] %20s ->  boolean(%d)",
                       (void*) stack,
                       stack->is_scope,
                       stack->is_function,
                       stack->name,
                       stack->value.value.boolean);
                break;
            case VINT32:
                printf("%18p [%d:%d] %20s ->    int32(%d)",
                       (void*) stack,
                       stack->is_scope,
                       stack->is_function,
                       stack->name,
                       stack->value.value.int32);
                break;
            case VFLOAT32:
                printf("%18p [%d:%d] %20s ->  float32(%f)",
                       (void*) stack,
                       stack->is_scope,
                       stack->is_function,
                       stack->name,
                       stack->value.value.float32);
                break;
            case VTEXT:
                printf("%18p [%d:%d] %20s ->     text(%s)",
                       (void*) stack,
                       stack->is_scope,
                       stack->is_function,
                       stack->name,
                       stack->value.value.text);
                break;
            case VFUNCTION:
                printf("%18p [%d:%d] %20s -> function(%p)",
                       (void*) stack,
                       stack->is_scope,
                       stack->is_function,
                       stack->name,
                       (void*) stack->value.value.function);
                break;
            default:
                break;
        }

        printf("\n");
        stack = stack->prev;
    }
    printf("---------------------------------------------------------------------------\n");
    printf("\n");
}
