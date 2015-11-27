#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <internal/portugol/runtime.h>
#include <internal/mem.h>

/*******************************************************************************
 * PUBLIC FUNCTIONS
 ******************************************************************************/

/* runtime singleton */
Runtime runtime = {0};

Variant*
runtime_add(const char* name,
            const VType type)
{
    /* initialize the runtime singleton */
    runtime_init();

    /* check if a stack scope as been already inserted in the runtime stack,
     * if not, insert into the runtime heap */
    if (runtime.stack.size == 0)
    {
        return runtime_heap_add(name, type);
    }

    return runtime_stack_add(name, type);
} /* end of : Variant*
              runtime_add(const char* name,
                          const VType type) */

Variant*
runtime_heap_add(const char* name,
                 const VType type)
{
    /* initialize the runtime singleton */
    runtime_init();

    /* insert a new heap entry in the runtime heap linked-list */
    RuntimeEntry* entry = runtime_heap_push(name, type);
    if (entry)
    {
        /* return the allocated data pointer */
        return &entry->value;
    }

    return NULL;
} /* end of : Variant*
              runtime_heap_add(const char* name,
                               const VType type) */

Variant*
runtime_stack_add(const char* name,
                  const VType type)
{
    /* initialize the runtime singleton */
    runtime_init();

    /* insert a new heap entry in the runtime heap linked-list */
    RuntimeEntry* entry = runtime_stack_push(name, type);
    if (entry)
    {
        /* initialize the stack entry */
        entry->is_scope = 0;
        entry->is_function = 0;
        entry->is_returning = 0;

        /* return the allocated data pointer */
        return &entry->value;
    }

    return NULL;
} /* end of : Variant*
              runtime_stack_add(const char* name,
                                const VType type) */

Variant*
runtime_stack_push_function(const char* name,
                            const VType type)
{
    /* initialize the runtime singleton */
    runtime_init();

    /* insert a new heap entry in the runtime heap linked-list */
    RuntimeEntry* entry = runtime_stack_push(name, type);
    if (entry)
    {
        /* initialize the stack entry */
        entry->is_scope = 1;
        entry->is_function = 1;
        entry->is_returning = 0;

        runtime.stack.function = entry;

        /* return the allocated data pointer */
        return &entry->value;
    }

    return NULL;
} /* end of : Variant*
              runtime_stack_push_function(const char* name,
                                          const VType type) */

void
runtime_stack_push_scope(void)
{
    /* initialize the runtime singleton */
    runtime_init();

    /* insert a new heap entry in the runtime heap linked-list */
    RuntimeEntry* entry = runtime_stack_push("*scope", VUNKNOWN);
    if (entry)
    {
        /* initialize the stack entry */
        entry->is_scope = 1;
        entry->is_function = 0;
        entry->is_returning = 0;
    }
} /* end of : void
              runtime_stack_push_scope(void) */

void
runtime_stack_pop(void)
{
    /* initialize the runtime singleton */
    runtime_init();

    /* stack function scope clearing cycle */
    while (   runtime.stack.top
           && !runtime.stack.top->is_scope)
    {
        /* remove the top entry from the runtime stack */
        RuntimeEntry* del = runtime.stack.top;
        runtime.stack.top = del->prev;

        /* clear the variant data */
        variant_uninit(&del->value);

        /* release the allocated memory */
        mem_free(del->name);
        mem_free(del);

        runtime.stack.size--;
    }

    /* remove the scope entry from the runtime stack */
    RuntimeEntry* del = runtime.stack.top;
    runtime.stack.top = del->prev;

    /* store a flag checking if the deleted scope is a function */
    int is_function = del->is_function;

    /* clear the variant data */
    variant_uninit(&del->value);

    /* release the allocated memory */
    mem_free(del->name);
    mem_free(del);

    runtime.stack.size--;

    /* check if is to recuperate the function pointer */
    if (is_function)
    {
        /* search for the last function scope node */
        runtime.stack.function = runtime.stack.top;
        while (   runtime.stack.function
               && !runtime.stack.function->is_function)
        {
            runtime.stack.function = runtime.stack.function->prev;
        }
    }
} /* end of : void
              runtime_stack_pop(void) */

Variant*
runtime_get(const char* name)
{
    /* initialize the runtime singleton */
    runtime_init();

    {
        /* search in the current function scope for the requested entry */
        RuntimeEntry* it = runtime.stack.top;
        while (   it
               && it != runtime.stack.function)
        {
            /* check the currently iterated entry */
            if (strcmp(it->name, name) == 0)
            {
                return &it->value;
            }

            /* search step */
            it = it->prev;
        }
    }

    {
        /* search in the heap for the requested entry */
        RuntimeEntry* it = runtime.heap.top;
        while (it)
        {
            /* check the currently iterated entry */
            if (strcmp(it->name, name) == 0)
            {
                return &it->value;
            }

            /* search step */
            it = it->prev;
        }
    }

    return NULL;
} /* end of : void*
              runtime_get(const char* name) */

Variant*
runtime_get_function_scope(void)
{
    /* initialize the runtime singleton */
    runtime_init();

    /* search for the runtime function scope */
    RuntimeEntry* it = runtime.stack.top;
    while (   it
           && it != runtime.stack.function)
    {
        it = it->prev;
    }

    if (it)
    {
        return &it->value;
    }

    return NULL;
} /* end of : Variant*
              runtime_get_function_scope(void) */

int
runtime_is_returning(void)
{
    /* initialize the runtime singleton */
    runtime_init();

    /* check if the current function scope is returning */
    return    runtime.stack.function != NULL
           && runtime.stack.function->is_returning;
} /* end of : int
              runtime_is_returning(void) */

void
runtime_set_returning(void)
{
    /* initialize the runtime singleton */
    runtime_init();

    /* set the current function scope to returning */
    if (runtime.stack.function)
    {
        runtime.stack.function->is_returning = 1;
    }
} /* end of : void
              runtime_set_returning(void) */

void
runtime_clear(void)
{
    /* initialize the runtime singleton */
    runtime_init();

    /* stack clearing cycle */
    while (runtime.stack.top)
    {
        /* remove the top entry from the runtime stack */
        RuntimeEntry* del = runtime.stack.top;
        runtime.stack.top = del->prev;

        /* clear the variant data */
        variant_uninit(&del->value);

        /* release the allocated memory */
        mem_free(del->name);
        mem_free(del);

        runtime.stack.size--;
    }
    runtime.stack.function = NULL;

    /* heap clearing cycle */
    while (runtime.heap.top)
    {
        /* remove the top entry from the runtime heap */
        RuntimeEntry* del = runtime.heap.top;
        runtime.heap.top = del->prev;

        /* clear the variant data */
        variant_uninit(&del->value);

        /* release the allocated memory */
        mem_free(del->name);
        mem_free(del);

        runtime.heap.size--;
    }
} /* end of : void
              runtime_clear(void) */

void
runtime_output(void)
{
    /* initialize the runtime singleton */
    runtime_init();

    printf("--- RUNTIME -------------------------------------------------------------\n");
    printf("--- HEAP    -------------------------------------------------------------\n");

    {
        RuntimeEntry* it = runtime.heap.top;
        while (it)
        {
            switch (it->value.type)
            {
                case VUNKNOWN:
                    printf(">>> %p [%d|%d|%d] %s\n",
                           (void*) it,
                           0,
                           0,
                           0,
                           it->name);
                    break;
                case VBOOLEAN:
                    printf(">>> %p [%d|%d|%d] %s > boolean(%s)\n",
                           (void*) it,
                           0,
                           0,
                           0,
                           it->name,
                           it->value.value.vboolean ? "true" : "false");
                    break;
                case VINT32:
                    printf(">>> %p [%d|%d|%d] %s > int32(%d)\n",
                           (void*) it,
                           0,
                           0,
                           0,
                           it->name,
                           it->value.value.vint32);
                    break;
                case VFLOAT32:
                    printf(">>> %p [%d|%d|%d] %s > float32(%f)\n",
                           (void*) it,
                           0,
                           0,
                           0,
                           it->name,
                           it->value.value.vfloat32);
                    break;
                case VTEXT:
                    printf(">>> %p [%d|%d|%d] %s > text(%s)\n",
                           (void*) it,
                           0,
                           0,
                           0,
                           it->name,
                           it->value.value.vtext);
                    break;
                case VPOINTER:
                    printf(">>> %p [%d|%d|%d] %s > pointer(%p)\n",
                           (void*) it,
                           0,
                           0,
                           0,
                           it->name,
                           it->value.value.vpointer);
                    break;
                case VFUNCTION:
                    printf(">>> %p [%d|%d|%d] %s > function(%p)\n",
                           (void*) it,
                           0,
                           0,
                           0,
                           it->name,
                           it->value.value.vfunction);
                    break;
                default:
                    break;
            }

            it = it->prev;
        }
    }

    printf("--- STACK   -------------------------------------------------------------\n");

    {
        RuntimeEntry* it = runtime.stack.top;
        while (it)
        {
            switch (it->value.type)
            {
                case VUNKNOWN:
                    printf(">>> %p [%d|%d|%d] %s\n",
                           (void*) it,
                           it->is_scope,
                           it->is_function,
                           it->is_returning,
                           it->name);
                    break;
                case VBOOLEAN:
                    printf(">>> %p [%d|%d|%d] %s > boolean(%s)\n",
                           (void*) it,
                           it->is_scope,
                           it->is_function,
                           it->is_returning,
                           it->name,
                           it->value.value.vboolean ? "true" : "false");
                    break;
                case VINT32:
                    printf(">>> %p [%d|%d|%d] %s > int32(%d)\n",
                           (void*) it,
                           it->is_scope,
                           it->is_function,
                           it->is_returning,
                           it->name,
                           it->value.value.vint32);
                    break;
                case VFLOAT32:
                    printf(">>> %p [%d|%d|%d] %s > float32(%f)\n",
                           (void*) it,
                           it->is_scope,
                           it->is_function,
                           it->is_returning,
                           it->name,
                           it->value.value.vfloat32);
                    break;
                case VTEXT:
                    printf(">>> %p [%d|%d|%d] %s > text(%s)\n",
                           (void*) it,
                           it->is_scope,
                           it->is_function,
                           it->is_returning,
                           it->name,
                           it->value.value.vtext);
                    break;
                case VPOINTER:
                    printf(">>> %p [%d|%d|%d] %s > pointer(%p)\n",
                           (void*) it,
                           it->is_scope,
                           it->is_function,
                           it->is_returning,
                           it->name,
                           it->value.value.vpointer);
                    break;
                case VFUNCTION:
                    printf(">>> %p [%d|%d|%d] %s > function(%p)\n",
                           (void*) it,
                           it->is_scope,
                           it->is_function,
                           it->is_returning,
                           it->name,
                           it->value.value.vfunction);
                    break;
            }

            it = it->prev;
        }
    }

    printf("-------------------------------------------------------------------------\n\n");
} /* end of : void
              runtime_output(void) */

/*******************************************************************************
 * INTERNAL FUNCTIONS
 ******************************************************************************/

void
runtime_init(void)
{
    /* check if the runtime singleton as already been initialized */
    if (!runtime.is_init)
    {
        memset(&runtime, 0, sizeof(Runtime));
        runtime.is_init = 1;

        /* register the singleton destruction function at app exit */
        atexit(runtime_uninit);
    }
} /* end of : void
              runtime_init(void) */

void
runtime_uninit(void)
{
    /* check if the runtime singleton as been initialized */
    if (runtime.is_init)
    {
        /* clear the runtime structures */
        runtime_clear();

        runtime.is_init = 0;
    }
} /* end of : void
              runtime_uninit(void) */

RuntimeEntry*
runtime_heap_push(const char* name,
                  const VType type)
{
    /* allocate memory to the heap entry */
    RuntimeEntry* entry;
    if ((entry = mem_malloc(sizeof(RuntimeEntry))) == NULL)
    {
        // TODO : report no memory failure
        return NULL;
    }

    /* allocate memory to the heap entry name */
    if ((entry->name = mem_malloc(strlen(name) + 1)) == NULL)
    {
        /* free the already allocated memory */
        mem_free(entry);

        // TODO : report no memory failure
        return NULL;
    }

    /* initialize the heap entry */
#ifdef _MSC_VER
    strcpy_s(entry->name, strlen(name) + 1, name);
#else
    strcpy(entry->name, name);
#endif /* _MSC_VER */
    entry->prev = NULL;

    /* initialize the stack entry variant */
    variant_init_type(&entry->value, type);

    /* check if the heap is empty */
    if (runtime.heap.top == NULL)
    {
        /* insert into the first position of the heap linked-list */
        runtime.heap.top = entry;
    }
    else
    {
        /* insert after the last position of the heap linked-list */
        entry->prev = runtime.heap.top;
        runtime.heap.top = entry;
    }

    runtime.heap.size++;

    return entry;
} /* end of : RuntimeEntry*
              runtime_heap_push(const char* name,
                                const VType type) */

RuntimeEntry*
runtime_stack_push(const char* name,
                   const VType type)
{
    /* allocate memory to the stack entry */
    RuntimeEntry* entry;
    if ((entry = mem_malloc(sizeof(RuntimeEntry))) == NULL)
    {
        // TODO : report no memory failure
        return NULL;
    }

    /* allocate memory to the stack entry name */
    if ((entry->name = mem_malloc(strlen(name) + 1)) == NULL)
    {
        /* free the already allocated memory */
        mem_free(entry);

        // TODO : report no memory failure
        return NULL;
    }

    /* initialize the stack entry */
#ifdef _MSC_VER
    strcpy_s(entry->name, strlen(name) + 1, name);
#else
    strcpy(entry->name, name);
#endif /* _MSC_VER */
    entry->prev = NULL;

    /* initialize the stack entry variant */
    variant_init_type(&entry->value, type);

    /* check if the stack is empty */
    if (runtime.stack.top == NULL)
    {
        /* insert into the first position of the stack linked-list */
        runtime.stack.top = entry;
    }
    else
    {
        /* insert after the last position of the stack linked-list */
        entry->prev = runtime.stack.top;
        runtime.stack.top = entry;
    }

    runtime.stack.size++;

    return entry;
} /* end of : RuntimeEntry*
              runtime_stack_push(const char* name,
                                 const VType type) */
