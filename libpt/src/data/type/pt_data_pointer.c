#include <math.h>
#include <stdio.h>
#include <string.h>

#include "internal/data/pt_data_natural.h"
#include "internal/data/type/pt_data_pointer.h"

// -----------------------------------------------------------------------------
// PRIVATE FUNCTIONS ALLUSIONS
// -----------------------------------------------------------------------------

/// @brief
///
/// @param strategy
///
/// @return
void *
pt_data_pointer_alloc (pt_data_strategy_t * strategy);

/// @brief
///
/// @param strategy
/// @param data
///
/// @return
pt_error_t
pt_data_pointer_free (pt_data_strategy_t * strategy,
                      void ** data);

/// @brief
///
/// @param strategy
///
/// @return
size_t
pt_data_pointer_get_init_size (pt_data_strategy_t * strategy);

/// @brief
///
/// @param strategy
/// @param data
///
/// @return
size_t
pt_data_pointer_get_current_size (pt_data_strategy_t * strategy,
                                  void * data);

/// @brief
///
/// @param src
/// @param args
/// @param dest
///
/// @return
void **
pt_data_pointer_sizeof (void * src,
                        void ** args,
                        void ** dest);

/// @brief
///
/// @param src
/// @param args
/// @param dest
///
/// @return
void **
pt_data_pointer_type (void * src,
                      void ** args,
                      void ** dest);

/// @brief
///
/// @param src
/// @param args
/// @param dest
///
/// @return
void **
pt_data_pointer_op_assign (void * src,
                           void ** args,
                           void ** dest);

/// @brief
///
/// @param src
/// @param args
/// @param dest
///
/// @return
void **
pt_data_pointer_op_equal (void * src,
                          void ** args,
                          void ** dest);

/// @brief
///
/// @param src
/// @param args
/// @param dest
///
/// @return
void **
pt_data_pointer_op_inequal (void * src,
                            void ** args,
                            void ** dest);

// -----------------------------------------------------------------------------
// INTERNAL FUNCTIONS
// -----------------------------------------------------------------------------

pt_data_strategy_t *
pt_data_pointer (void) 
{
    pt_data_strategy_t * strategy = NULL;

    // allocate memory to the strategy structure
    if ((strategy = malloc (sizeof (pt_data_strategy_t))) == NULL) 
    {
        pt.error.set (PT_ERROR_NO_MEMORY);
        return NULL;
    }

    // allocate memory to the strategy name string
    size_t length = strlen (PT_LANG_POINTER) + 1;
    if ((strategy->name = malloc (length)) == NULL) 
    {
        free (strategy);
        pt.error.set (PT_ERROR_NO_MEMORY);
        return NULL;
    }

    // initialize the strategy structure
    strategy->datatype            = PT_DATATYPE_POINTER;
    strcpy (strategy->name, PT_LANG_POINTER);

    strategy->cb.alloc            = pt_data_pointer_alloc;
    strategy->cb.free             = pt_data_pointer_free;
    strategy->cb.get_init_size    = pt_data_pointer_get_init_size;
    strategy->cb.get_current_size = pt_data_pointer_get_current_size;

    strategy->cb.is_cast          = pt_data_natural_is_cast;
    strategy->cb.is_elevate       = pt_data_natural_is_elevate;
    strategy->cb.get_cast         = pt_data_natural_get_cast;
    strategy->cb.cast             = pt_data_natural_cast;
    strategy->cb.cast_ex          = pt_data_natural_cast_ex;
    strategy->cb.is_method        = pt_data_natural_is_method;
    strategy->cb.get_method       = pt_data_natural_get_method;
    strategy->cb.method           = pt_data_natural_method;
    strategy->cb.method_ex        = pt_data_natural_method_ex;

    strategy->methods = NULL;

    // register the methods
    {
        pt_data_type_t params[] = { 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_INTEGER32,
                                     PT_LANG_SIZEOF,
                                     params,
                                     pt_data_pointer_sizeof);
    }
    {
        pt_data_type_t params[] = { 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_TEXT,
                                     PT_LANG_TYPE,
                                     params,
                                     pt_data_pointer_type);
    }

    // register the operators
    {
        pt_data_type_t params[] = { 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_POINTER,
                                     PT_LANG_ASSIGN,
                                     params,
                                     pt_data_pointer_op_assign);
    }
    {
        pt_data_type_t params[] = { PT_DATATYPE_POINTER, 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_BOOLEAN,
                                     PT_LANG_EQUAL,
                                     params,
                                     pt_data_pointer_op_equal);
    }
    {
        pt_data_type_t params[] = { PT_DATATYPE_POINTER, 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_BOOLEAN,
                                     PT_LANG_INEQUAL,
                                     params,
                                     pt_data_pointer_op_inequal);
    }

    return strategy;
} /* end of : pt_data_strategy_t *
              pt_data_pointer (void) */

// -----------------------------------------------------------------------------
// PRIVATE FUNCTIONS
// -----------------------------------------------------------------------------

void *
pt_data_pointer_alloc (pt_data_strategy_t * strategy)
{
#ifndef NDEBUG
    // validate arguments
    if (!strategy) 
    {
        pt.error.set (PT_ERROR_INVALID_POINTER);
        return NULL;
    }
#endif

    // allocate memory to the data
    void * data = NULL;
    if ((data = calloc (1, sizeof(void *))) == NULL) 
    {
        pt.error.set (PT_ERROR_NO_MEMORY);
        return NULL;
    }

    return data;
} /* end of : void *
              pt_data_pointer_alloc (pt_data_strategy_t * strategy) */

pt_error_t
pt_data_pointer_free (pt_data_strategy_t * strategy,
                      void ** data)
{
#ifndef NDEBUG
    // validate arguments
    if (   !strategy
        || !data)
        return pt.error.set (PT_ERROR_INVALID_POINTER);
#endif

    // pointer validation
    if (*data)
    {
        // release the allocated memory
        free (*data);
        *data = NULL;
    }

    return PT_ERROR_OK;
} /* end of : pt_error_t
              pt_data_pointer_free (pt_data_strategy_t * strategy,
                                    void ** data) */

size_t
pt_data_pointer_get_init_size (pt_data_strategy_t * strategy)
{
#ifndef NDEBUG
    // validate arguments
    if (!strategy) 
    {
        pt.error.set (PT_ERROR_INVALID_POINTER);
        return 0;
    }
#endif

    return sizeof (void *);
} /* end of : size_t
              pt_data_pointer_get_init_size (pt_data_strategy_t * strategy) */

size_t
pt_data_pointer_get_current_size (pt_data_strategy_t * strategy,
                                  void * data)
{
#ifndef NDEBUG
    // validate arguments
    if (   !strategy
        || !data)
    {
        pt.error.set (PT_ERROR_INVALID_POINTER);
        return 0;
    }
#endif

    return sizeof (void *);
} /* end of : size_t
              pt_data_pointer_get_current_size (pt_data_strategy_t * strategy,
                                                void * data) */

void **
pt_data_pointer_sizeof (void * src,
                        void ** args,
                        void ** dest)
{
#ifndef NDEBUG
    // validate arguments
    if (   !src
        || !dest)
    {
        pt.error.set (PT_ERROR_INVALID_POINTER);
        return NULL;
    }
#endif

    ** (int32_t **) dest = sizeof (void *);

    return dest;
} /* end of : void **
              pt_data_pointer_sizeof (void * src,
                                      void ** args,
                                      void ** dest) */

void **
pt_data_pointer_type (void * src,
                      void ** args,
                      void ** dest)
{
#ifndef NDEBUG
    // validate arguments
    if (   !src
        || !dest)
    {
        pt.error.set (PT_ERROR_INVALID_POINTER);
        return NULL;
    }
#endif

    // reallocate the memory to store the datatype name text
    char * result = NULL;
    if ((result = realloc (* (char **) dest, 16)) == NULL)
    {
        pt.error.set (PT_ERROR_NO_MEMORY);
        return NULL;
    }

    // write the datatype text into the reallocated memory
    snprintf (result, 16, "%s", PT_LANG_POINTER);
    * (char **) dest = result;

    return dest;
} /* end of : void **
              pt_data_pointer_type (void * src,
                                    void ** args,
                                    void ** dest) */

void **
pt_data_pointer_op_assign (void * src,
                           void ** args,
                           void ** dest)
{
#ifndef NDEBUG
    // validate arguments
    if (   !src
        || !dest)
    {
        pt.error.set (PT_ERROR_INVALID_POINTER);
        return NULL;
    }
#endif

    ** (void ***) dest = * (void **) src;

    return dest;
} /* end of : void **
              pt_data_pointer_op_assign (void * src,
                                         void ** args,
                                         void ** dest) */

void **
pt_data_pointer_op_equal (void * src,
                          void ** args,
                          void ** dest)
{
#ifndef NDEBUG
    // validate arguments
    if (   !src
        || !args
        || !args[0]
        || !dest)
    {
        pt.error.set (PT_ERROR_INVALID_POINTER);
        return NULL;
    }
#endif

    ** (uint8_t **) dest = * (void **) src == * (void **) args[0];

    return dest;
} /* end of : void **
              pt_data_pointer_op_equal (void * src,
                                        void ** args,
                                        void ** dest) */

void **
pt_data_pointer_op_inequal (void * src,
                            void ** args,
                            void ** dest)
{
#ifndef NDEBUG
    // validate arguments
    if (   !src
        || !args
        || !args[0]
        || !dest)
    {
        pt.error.set (PT_ERROR_INVALID_POINTER);
        return NULL;
    }
#endif

    ** (uint8_t **) dest = * (void **) src != * (void **) args[0];

    return dest;
} /* end of  void **
             pt_data_pointer_op_inequal (void * src,
                                         void ** args,
                                         void ** dest) */
