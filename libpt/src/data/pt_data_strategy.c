#include <string.h>

#include "internal/data/pt_data_strategy.h"

// -----------------------------------------------------------------------------
// INTERNAL FUNCTIONS
// -----------------------------------------------------------------------------

pt_error_t
pt_data_strategy_destroy (pt_data_strategy_t ** strategy)
{
#ifndef NDEBUG
    // validate arguments
    if (   !strategy
        || !(*strategy))
        return pt.error.set (PT_ERROR_INVALID_POINTER);
#endif

    // auxiliary local pointer
    pt_data_strategy_t * aux = * strategy;

    // strategy method removal/destruction cycle
    while (aux->methods)
    {
        // remove the method at the list head
        pt_data_method_entry_t * del = aux->methods;
        aux->methods = aux->methods->next;

        // release the memory allocated to the method
        free (del->name);
        free (del->params);
        free (del);
    }

    // release the memory allocated to the strategy
    free (aux->name);
    free (aux);
    * strategy = NULL;

    return PT_ERROR_OK;
} /* end of : pt_error_t
              pt_data_strategy_destroy (pt_data_strategy_t ** strategy) */

pt_data_method_entry_t *
pt_data_strategy_get_method (pt_data_strategy_t * strategy,
                             const char * name,
                             pt_data_type_t params[])
{
#ifndef NDEBUG
    // validate arguments
    if (   !strategy
        || !name)
    {
        pt.error.set (PT_ERROR_INVALID_POINTER);
        return NULL;
    }
#endif

    // calculate the size of the params list
    size_t param_count = 0;
    for (pt_data_type_t * it = params; * it; it++, param_count++)
        /* void */;

    // method search cycle
    pt_data_method_entry_t * it_method = strategy->methods;
    while (it_method)
    {
        // check if the name of the iterated method is the same of the method
        // required
        if (   strcmp (it_method->name, name) == 0
            && it_method->param_count <= param_count)
        {
            // param list validation cycle
            pt_data_type_t * it_param = it_method->params;
            while (* it_param)
            {
                // param cycle step
                it_param++;
            }

            // TODO : remove this :D - not parsing params
            return it_method;
        }

        // cycle iteration
        it_method = it_method->next;
    }

    pt.error.set (PT_ERROR_NOT_FOUND);
    return NULL;
} /* end of : pt_data_method_entry_t *
              pt_data_strategy_get_method (pt_data_strategy_t * strategy,
                                           const char * name,
                                           pt_data_type_t params[]) */

pt_data_strategy_t *
pt_data_strategy_add_method (pt_data_strategy_t * strategy,
                             pt_data_type_t datatype,
                             const char * name,
                             pt_data_type_t params[],
                             pt_data_method_callback_t cb)
{
#ifndef NDEBUG
    // validate arguments
    if (   !strategy
        || !name
        || !cb)
    {
        pt.error.set (PT_ERROR_INVALID_POINTER);
        return NULL;
    }

    if (datatype == PT_DATATYPE_UNKNOWN)
    {
        pt.error.set (PT_ERROR_INVALID_ARGUMENT);
        return NULL;
    }
#endif

    pt_data_method_entry_t * entry = NULL;

    // allocate memory to the new method entry
    if ((entry = malloc (sizeof (pt_data_method_entry_t))) == NULL)
    {
        pt.error.set (PT_ERROR_NO_MEMORY);
        return NULL;
    }

    // allocate memory the the method name
    size_t length = strlen (name) + 1;
    if ((entry->name = malloc (length)) == NULL)
    {
        free (entry);

        pt.error.set (PT_ERROR_NO_MEMORY);
        return NULL;
    }

    // calculate the size of the params list
    entry->param_count = 0;
    for (pt_data_type_t * it = params; * it; it++, entry->param_count++)
        /* void */;
    
    // allocate memory to the params list
    if ((entry->params = calloc (entry->param_count + 1,
                                 sizeof (pt_data_type_t))) == NULL)
    {
        free (entry->name);
        free (entry);

        pt.error.set (PT_ERROR_NO_MEMORY);
        return NULL;
    }

    // fill the created method entry structure
    entry->next = strategy->methods;
    entry->datatype = datatype;
    strcpy (entry->name, name);
    memcpy (entry->params, params, sizeof(pt_data_type_t) * entry->param_count);
    entry->cb = cb;

    // insert the created method into the strategy method list
    strategy->methods = entry;

    return strategy;
} /* end of : pt_data_strategy_t *
              pt_data_strategy_add_method (pt_data_strategy_t * strategy,
                                           pt_data_type_t datatype,
                                           const char * name,
                                           pt_data_type_t params[],
                                           pt_data_method_callback_t cb) */
