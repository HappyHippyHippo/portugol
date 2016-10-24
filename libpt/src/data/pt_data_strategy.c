#include <string.h>

#include "internal/data/pt_data_strategy.h"

// -----------------------------------------------------------------------------
// PRIVATE FUNCTION ALLUSION
// -----------------------------------------------------------------------------

/// @brief
///
/// @param entry1
/// @param entry2
///
/// @return
int
pt_data_strategy_compare_methods (pt_data_method_entry_t * entry1,
                                  pt_data_method_entry_t * entry2);

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
            pt_data_type_t * it_get_param = params;
            pt_data_type_t * it_method_param = it_method->params;
            while (* it_method_param)
            {
                // get the strategy of the requested method parameter
                pt_data_strategy_t * get_strategy = pt.data.pool.get_by_type(* it_get_param);

                // check if the iterated param is a equal level datatype or
                // can be elevated to the iterated method param datatype
                if (   * it_get_param == * it_method_param
                    || get_strategy->cb.is_elevate(get_strategy, * it_method_param))
                {
                    // param cycle step
                    it_get_param++;
                    it_method_param++;
                }
                else
                    break;
            }

            if (!* it_method_param)
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
    entry->next = NULL;
    entry->datatype = datatype;
    strcpy (entry->name, name);
    memcpy (entry->params, params, sizeof (pt_data_type_t) * entry->param_count);
    entry->cb = cb;

    // check if the strategy do not have any method registed
    if (strategy->methods)
    {
        int diff = 0;

        // check if the new method should be inserted at the method list head
        if ((diff = pt_data_strategy_compare_methods(entry, strategy->methods)) < 0)
        {
            // insert the created method into the strategy method list
            entry->next = strategy->methods;
            strategy->methods = entry;
        }
        else
        {
            // search for the orded position to insert the new method
            pt_data_method_entry_t * it = strategy->methods;
            while (it->next)
            {
                // check if the new method should be inserted at the iteration
                // point
                if ((diff = pt_data_strategy_compare_methods(entry, it->next)) < 0)
                {
                    // insert the created method into the strategy method list
                    entry->next = it->next;
                    it->next = entry;

                    break;
                }
                else
                    // search cycle iteration
                    it = it->next;
            }

            // check if the new method is to be inserted at the end of the list
            if (!it->next)
                it->next = entry;
        }
    }
    else
        // insert the created method into the strategy method list
        strategy->methods = entry;

    return strategy;
} /* end of : pt_data_strategy_t *
              pt_data_strategy_add_method (pt_data_strategy_t * strategy,
                                           pt_data_type_t datatype,
                                           const char * name,
                                           pt_data_type_t params[],
                                           pt_data_method_callback_t cb) */

int
pt_data_strategy_compare_methods (pt_data_method_entry_t * entry1,
                                  pt_data_method_entry_t * entry2)
{
    int diff = 0;

    // compare the two methods names
    diff = strcmp (entry1->name, entry2->name);
    if (diff != 0)
        return diff;

    // compare the two methods paameters list count
    diff = entry2->param_count - entry1->param_count;
    if (diff != 0)
        return diff;

    // method params comparisson cycle
    pt_data_type_t * it_entry1_param = entry1->params;
    pt_data_type_t * it_entry2_param = entry2->params;
    while (* it_entry1_param)
    {
        // compare the two parameters
        diff = * it_entry1_param - * it_entry2_param;
        if (diff != 0)
            return diff;

        // cycle iteration step
        it_entry1_param++;
        it_entry2_param++;
    }

    return 0;
} /* end of : int
              pt_data_strategy_compare_methods (pt_data_method_entry_t * entry1,
                                                pt_data_method_entry_t * entry2) */
