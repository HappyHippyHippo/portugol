#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <internal/portugol/runtime.h>

#define SCOPE_RETURN "retorna"

Runtime*
runtime_create(void)
{
    Runtime* runtime;
    if ((runtime = malloc(sizeof(Runtime))) != NULL)
    {
        runtime->stack = NULL;
        runtime->scope = NULL;
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

    Stack* it = runtime->stack;
    while (it != NULL)
    {
        if (strcmp(name, it->name) == 0)
            return &it->value;
        it = it->prev;
    }

    return NULL;
}

Variant*
runtime_push(Runtime* runtime,
             char* name,
             Variant value)
{
    if (runtime == NULL || name == NULL)
        return NULL;

    Stack* stack;
    if ((stack = malloc(sizeof(Stack))) == NULL)
        return NULL;

    stack->name = name;
    stack->value = variant_copy(value);
    stack->prev = runtime->stack;

    runtime->stack = stack;

    return &stack->value;
}

Variant
runtime_pop(Runtime* runtime)
{
    if (runtime == NULL || runtime->stack == NULL)
        return variant_init_int32(0);

    Variant result = runtime->stack->value;

    Stack* del = runtime->stack;
    runtime->stack = runtime->stack->prev;
    free(del);

    return result;
}

Runtime*
runtime_clear(Runtime* runtime)
{
    if (runtime == NULL)
        return runtime;

    while (runtime->stack != NULL)
    {
        Variant var = runtime_pop(runtime);
        variant_uninit(&var);
    }

    while (runtime->scope != NULL)
    {
        Scope* del = runtime->scope;
        runtime->scope = runtime->scope->prev;
        free(del);
    }

    return runtime;
}

Variant*
runtime_push_scope(Runtime* runtime)
{
    return runtime_push_scope_named(runtime, SCOPE_RETURN);
}

Variant*
runtime_push_scope_named(Runtime* runtime,
                         char* name)
{
    if (runtime == NULL)
        return NULL;

    Stack* stack;
    if ((stack = malloc(sizeof(Stack))) == NULL)
        return NULL;

    Scope* scope;
    if ((scope = malloc(sizeof(Scope))) == NULL)
    {
        free(stack);
        return NULL;
    }

    stack->name = name;
    stack->value = variant_init_int32(0);
    stack->prev = runtime->stack;
    runtime->stack = stack;

    scope->stack = stack;
    scope->prev = runtime->scope;
    runtime->scope = scope;

    return NULL;
}

Variant*
runtime_get_scope(Runtime* runtime)
{
    if (runtime == NULL)
        return NULL;

    return &runtime->scope->stack->value;
}

Variant
runtime_pop_scope(Runtime* runtime)
{
    if (runtime == NULL && runtime->scope->stack)
        return variant_init_int32(0);

    while (runtime->stack != runtime->scope->stack)
    {
        Variant var = runtime_pop(runtime);
        variant_uninit(&var);
    }

    Scope* del = runtime->scope;
    runtime->scope = runtime->scope->prev;
    free(del);

    return runtime_pop(runtime);
}

void
runtime_print(Runtime* runtime)
{
    if (runtime == NULL)
        return;

    printf("------------------ RUNTIME STACK ------------------\n");
    Stack* stack = runtime->stack;
    Scope* scope = runtime->scope;
    while (stack != NULL)
    {
        switch (stack->value.type)
        {
            case VBOOLEAN:
                printf("%p, %10s -> %10d", (void*) stack, stack->name, stack->value.value.boolean);
                break;
            case VINT32:
                printf("%p, %10s -> %10d", (void*) stack, stack->name, stack->value.value.int32);
                break;
            case VFLOAT32:
                printf("%p, %10s -> %10f", (void*) stack, stack->name, stack->value.value.float32);
                break;
            case VTEXT:
                printf("%p, %10s -> %10s", (void*) stack, stack->name, stack->value.value.text);
                break;
        }

        if (scope != NULL && stack == scope->stack)
            printf(" (scope)");

        printf("\n");
        stack = stack->prev;
    }
    printf("---------------------------------------------------\n");
}
