#include "internal/data/pt_data.h"
#include "internal/data/pt_data_strategy.h"

// -----------------------------------------------------------------------------
// INTERNAL FUNCTIONS
// -----------------------------------------------------------------------------

pt_data_t
pt_data_alloc_by_type (pt_data_type_t datatype)
{
    // structure initialization
    pt_data_t data = { NULL, pt.data.pool.get_by_type (datatype) };
    if (data.strategy)
        data.data = data.strategy->cb.alloc (data.strategy);

    return data;
} /* end of : pt_data_t
              pt_data_alloc_by_type (pt_data_type_t datatype) */

pt_data_t
pt_data_alloc_by_name (const char * name)
{
    // structure initialization
    pt_data_t data = { NULL, pt.data.pool.get_by_name (name) };
    if (data.strategy)
        data.data = data.strategy->cb.alloc (data.strategy);

    return data;
} /* end of : pt_data_t
              pt_data_alloc_by_name (const char * name) */

pt_error_t
pt_data_free (pt_data_t * data)
{
#ifndef NDEBUG
    // validate arguments
    if (   !data
        || !data->strategy)
        return pt.error.set (PT_ERROR_INVALID_POINTER);
#endif

    // redirect
    return data->strategy->cb.free (data->strategy,
                                    & data->data);
} /* end of : pt_error_t
              pt_data_free (pt_data_t * data) */

size_t
pt_data_get_size (pt_data_t data)
{
#ifndef NDEBUG
    // validate arguments
    if (!data.strategy)
    {
        pt.error.set (PT_ERROR_INVALID_POINTER);
        return 0;
    }
#endif

    // redirect
    return data.strategy->cb.get_current_size (data.strategy,
                                               data.data);
} /* end of : size_t
              pt_data_get_size (pt_data_t data) */

int
pt_data_is_cast (pt_data_t data,
                 pt_data_type_t datatype)
{
#ifndef NDEBUG
    // validate arguments
    if (!data.strategy)
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
    return data.strategy->cb.is_cast (data.strategy,
                                      datatype);
} /* end of : int
              pt_data_is_cast (pt_data_t data,
                               pt_data_type_t datatype) */

int
pt_data_is_elevate (pt_data_t data,
                    pt_data_type_t datatype)
{
#ifndef NDEBUG
    // validate arguments
    if (!data.strategy)
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

    // check if the datatpe of the base data is not a user defined datatype,
    // meaning that any user defined type can be elevated if there is a cast for
    // it, and the target datatype is lower than the base datatype
    if (   data.strategy->datatype <= PT_DATATYPE_USER_DEFINED
        && datatype <= data.strategy->datatype)
        return 0;

    // redirect
    return data.strategy->cb.is_cast (data.strategy,
                                      datatype);
} /* end of : int
              pt_data_is_elevate (pt_data_t data,
                                  pt_data_type_t datatype) */

pt_data_method_t
pt_data_get_cast (pt_data_t data,
                  pt_data_type_t datatype)
{
#ifndef NDEBUG
    pt_data_method_t method = { NULL };

    // validate arguments
    if (!data.strategy)
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

    // redirect
    return data.strategy->cb.get_cast (data.strategy,
                                       datatype);
} /* end of : pt_data_method_t
              pt_data_get_cast (pt_data_t data,
                                pt_data_type_t datatype) */

void **
pt_data_cast (pt_data_t data,
              pt_data_type_t datatype,
              void ** dest)
{
#ifndef NDEBUG
    // validate arguments
    if (   !data.strategy
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

    // redirect
    return data.strategy->cb.cast (data.strategy,
                                   datatype,
                                   data.data,
                                   dest);
} /* end of : void **
              pt_data_cast (pt_data_t data,
                            pt_data_type_t datatype,
                            void ** dest) */

void **
pt_data_cast_ex (pt_data_t data,
                 pt_data_method_t method,
                 void ** dest)
{
#ifndef NDEBUG
    // validate arguments
    if (   !data.strategy
        || !method.cb
        || !dest)
    {
        pt.error.set (PT_ERROR_INVALID_POINTER);
        return NULL;
    }
#endif

    // redirect
    return data.strategy->cb.cast_ex (data.strategy,
                                      method,
                                      data.data,
                                      dest);
} /* end of : void **
              pt_data_cast_ex (pt_data_t data,
                               pt_data_method_t method,
                               void ** dest) */

int
pt_data_is_method (pt_data_t data,
                   const char * name,
                   pt_data_type_t params[])
{
#ifndef NDEBUG
    // validate arguments
    if (   !data.strategy
        || !name)
    {
        pt.error.set (PT_ERROR_INVALID_POINTER);
        return 0;
    }
#endif

    // redirect
    return data.strategy->cb.is_method (data.strategy,
                                        name,
                                        params);
} /* end of : int
              pt_data_is_method (pt_data_t data,
                                 const char * name,
                                 pt_data_type_t params[]) */

pt_data_method_t
pt_data_get_method (pt_data_t data,
                    const char * name,
                    pt_data_type_t params[])
{
#ifndef NDEBUG
    pt_data_method_t method = { NULL };

    // validate arguments
    if (   !data.strategy
        || !name)
    {
        pt.error.set (PT_ERROR_INVALID_POINTER);
        return method;
    }
#endif

    // redirect
    return data.strategy->cb.get_method (data.strategy,
                                         name,
                                         params);
} /* end of : pt_data_method_t
              pt_data_get_method (pt_data_t data,
                                  const char * name,
                                  pt_data_type_t params[]) */

void **
pt_data_method (pt_data_t data,
                const char * name,
                pt_data_type_t params[],
                void * args[],
                void ** dest)
{
#ifndef NDEBUG
    // validate arguments
    if (   !data.strategy
        || !name
        || !dest)
    {
        pt.error.set (PT_ERROR_INVALID_POINTER);
        return NULL;
    }
#endif

    // redirect
    return data.strategy->cb.method (data.strategy,
                                     name,
                                     params,
                                     data.data,
                                     args,
                                     dest);
} /* end of : void **
              pt_data_method (pt_data_t data,
                              const char * name,
                              pt_data_type_t params[],
                              void * args[],
                              void ** dest) */

void **
pt_data_method_ex (pt_data_t data,
                   pt_data_method_t method,
                   void * args[],
                   void ** dest)
{
#ifndef NDEBUG
    // validate arguments
    if (   !data.strategy
        || !method.cb
        || !dest)
    {
        pt.error.set (PT_ERROR_INVALID_POINTER);
        return NULL;
    }
#endif

    // redirect
    return data.strategy->cb.method_ex (data.strategy,
                                        method,
                                        data.data,
                                        args,
                                        dest);
} /* end of : void **
              pt_data_method_ex (pt_data_t data,
                                 pt_data_method_t method,
                                 void * args[],
                                 void ** dest) */
