#include <string.h>

#include "internal/data/pt_data_natural.h"
#include "internal/data/pt_data_strategy.h"

// -----------------------------------------------------------------------------
// INTERNAL FUNCTIONS
// -----------------------------------------------------------------------------

int
pt_data_natural_is_cast (pt_data_strategy_t * strategy,
                         pt_data_type_t datatype)
{
#ifndef NDEBUG
    // validate arguments
    if (!strategy)
    {
        pt.error.set (PT_ERROR_INVALID_POINTER);
        return 0;
    }

    if (datatype == PT_DATATYPE_UNKNOWN)
    {
        pt.error.set (PT_ERROR_INVALID_ARGUMENT);
        return 0;
    }
#endif

    // redirect
    return pt_data_natural_get_cast (strategy,
                                     datatype).cb != NULL;
} /* end of : int
              pt_data_natural_is_cast (pt_data_strategy_t * strategy,
                                       pt_data_type_t datatype) */

pt_data_method_t
pt_data_natural_get_cast (pt_data_strategy_t * strategy,
                          pt_data_type_t datatype)
{
    pt_data_method_t method = { NULL };

#ifndef NDEBUG
    // validate arguments
    if (!strategy)
    {
        pt.error.set (PT_ERROR_INVALID_POINTER);
        return method;
    }

    if (datatype == PT_DATATYPE_UNKNOWN)
    {
        pt.error.set (PT_ERROR_INVALID_ARGUMENT);
        return method;
    }
#endif

    // cast function search cycle
    pt_data_method_entry_t * it = strategy->methods;
    while (it)
    {
        if (   strcmp (it->name, PT_LANG_CAST) == 0
            && it->datatype == datatype)
        {
            method.cb = it->cb;
            return method;
        }
        it = it->next;
    }

    pt.error.set (PT_ERROR_NOT_FOUND);
    return method;
} /* end of : pt_data_method_t
              pt_data_natural_get_cast (pt_data_strategy_t * strategy,
                                        pt_data_type_t datatype) */

void **
pt_data_natural_cast (pt_data_strategy_t * strategy,
                      pt_data_type_t datatype,
                      void * src,
                      void ** dest)
{
#ifndef NDEBUG
    // validate arguments
    if (   !strategy
        || !src
        || !dest)
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

    // retrieve the method/cast to be called
    pt_data_method_t method = pt_data_natural_get_cast (strategy,
                                                        datatype);
    if (method.cb == NULL)
        return NULL;

    // redirect
    return pt_data_natural_cast_ex (strategy,
                                    method,
                                    src,
                                    dest);
} /* end of : void **
              pt_data_natural_cast (pt_data_strategy_t * strategy,
                                    pt_data_type_t datatype,
                                    void * src,
                                    void ** dest) */

void **
pt_data_natural_cast_ex (pt_data_strategy_t * strategy,
                         pt_data_method_t method,
                         void * src,
                         void ** dest)
{
#ifndef NDEBUG
    // validate arguments
    if (   !strategy
        || !method.cb
        || !src
        || !dest)
    {
        pt.error.set (PT_ERROR_INVALID_POINTER);
        return NULL;
    }
#endif

    // method call
    void ** args = { NULL };
    return method.cb (src,
                      args,
                      dest);
} /* end of : void **
              pt_data_natural_cast_ex (pt_data_strategy_t * strategy,
                                       pt_data_method_t method,
                                       void * src,
                                       void ** dest) */

int
pt_data_natural_is_method (pt_data_strategy_t * strategy,
                           const char * name,
                           pt_data_type_t params[])
{
#ifndef NDEBUG
    // validate arguments
    if (   !strategy
        || !name)
    {
        pt.error.set (PT_ERROR_INVALID_POINTER);
        return 0;
    }
#endif

    // check the existence of the method
    return pt_data_strategy_get_method (strategy,
                                        name,
                                        params) != NULL;
} /* end of : int
              pt_data_natural_is_method (pt_data_strategy_t * strategy,
                                         const char * name,
                                         pt_data_type_t params[]) */

pt_data_method_t
pt_data_natural_get_method (pt_data_strategy_t * strategy,
                            const char * name,
                            pt_data_type_t params[])
{
    pt_data_method_t method = { NULL };

#ifndef NDEBUG
    // validate arguments
    if (   !strategy
        || !name)
    {
        pt.error.set (PT_ERROR_INVALID_POINTER);
        return method;
    }
#endif

    // retrieve the requested method
    pt_data_method_entry_t * entry = NULL;
    if ((entry = pt_data_strategy_get_method (strategy,
                                              name,
                                              params)) != NULL)
        method.cb = entry->cb;

    return method;
} /* end of : pt_data_method_t
              pt_data_natural_get_method (pt_data_strategy_t * strategy,
                                          const char * name,
                                          pt_data_type_t params[]) */

void **
pt_data_natural_method (pt_data_strategy_t * strategy,
                        const char * name,
                        pt_data_type_t params[],
                        void * src,
                        void * args[],
                        void ** dest)
{
#ifndef NDEBUG
    // validate arguments
    if (   !strategy
        || !name
        || !src
        || !dest)
    {
        pt.error.set (PT_ERROR_INVALID_POINTER);
        return NULL;
    }
#endif

    // retrieve the method/cast to be called
    pt_data_method_t method = pt_data_natural_get_method (strategy,
                                                          name,
                                                          params);
    if (method.cb == NULL)
        return NULL;

    // redirect
    return pt_data_natural_method_ex (strategy,
                                      method,
                                      src,
                                      args,
                                      dest);
} /* end of : void **
              pt_data_natural_method (pt_data_strategy_t * strategy,
                                      const char * name,
                                      pt_data_type_t params[],
                                      void * src,
                                      void * args[],
                                      void ** dest) */

void **
pt_data_natural_method_ex (pt_data_strategy_t * strategy,
                           pt_data_method_t method,
                           void * src,
                           void * args[],
                           void ** dest)
{
#ifndef NDEBUG
    // validate arguments
    if (   !strategy
        || !method.cb
        || !src
        || !dest)
    {
        pt.error.set (PT_ERROR_INVALID_POINTER);
        return NULL;
    }
#endif

    // method call
    return method.cb (src,
                      args,
                      dest);
} /* end of : void **
              pt_data_natural_method_ex (pt_data_strategy_t * strategy,
                                         pt_data_method_t method,
                                         void * src,
                                         void * args[],
                                         void ** dest) */
