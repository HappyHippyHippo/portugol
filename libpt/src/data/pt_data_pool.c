#include <string.h>

#include "internal/data/pt_data_strategy.h"
#include "internal/data/type/pt_data_boolean.h"
#include "internal/data/type/pt_data_bit8.h"
#include "internal/data/type/pt_data_bit16.h"
#include "internal/data/type/pt_data_bit32.h"
#include "internal/data/type/pt_data_bit64.h"
#include "internal/data/type/pt_data_integer8.h"
#include "internal/data/type/pt_data_integer16.h"
#include "internal/data/type/pt_data_integer32.h"
#include "internal/data/type/pt_data_integer64.h"
#include "internal/data/type/pt_data_float32.h"
#include "internal/data/type/pt_data_float64.h"
#include "internal/data/type/pt_data_text.h"
#include "internal/data/type/pt_data_pointer.h"
#include "internal/data/type/pt_data_function.h"

// -----------------------------------------------------------------------------
// PRIVATE TYPEDEFS
// -----------------------------------------------------------------------------

/// @brief
typedef struct pt_data_pool_entry_t
{
    /// @brief
    struct pt_data_pool_entry_t * next;

    /// @brief
    pt_data_strategy_t * strategy;
} pt_data_pool_entry_t;

/// @brief
typedef struct pt_data_pool_t
{
    /// @brief
    int initialized;

    /// @brief
    size_t next_user_type;

    /// @brief
    pt_data_pool_entry_t * natural;

    /// @brief
    pt_data_pool_entry_t * user;
} pt_data_pool_t;

// -----------------------------------------------------------------------------
// PRIVATE VARIABLES
// -----------------------------------------------------------------------------

/// @brief
pt_data_pool_t pt_data_pool =
{
    0,
    0,
    NULL,
    NULL
};

// -----------------------------------------------------------------------------
// PRIVATE FUNCTIONS ALLUSIONS
// -----------------------------------------------------------------------------

/// @brief
///
/// @return
pt_error_t
pt_data_pool_init (void);

/// @brief
void
pt_data_pool_uninit (void);

/// @brief
///
/// @param strategy
///
/// @return
pt_error_t
pt_data_pool_add_natural (pt_data_strategy_t * strategy);

/// @brief
///
/// @return
pt_error_t
pt_data_pool_clear_natural (void);

// -----------------------------------------------------------------------------
// INTERNAL FUNCTIONS
// -----------------------------------------------------------------------------

pt_data_strategy_t *
pt_data_pool_get_by_type (pt_data_type_t datatype)
{
#ifndef NDEBUG
    // validate arguments
    if (datatype == PT_DATATYPE_UNKNOWN)
    {
        pt.error.set (PT_ERROR_INVALID_ARGUMENT);
        return NULL;
    }
#endif

    // singleton initialization
    if (   !pt_data_pool.initialized
        && pt_data_pool_init () != PT_ERROR_OK)
        return NULL;

    // natural datatypes strategy lookup cycle
    pt_data_pool_entry_t * it = pt_data_pool.natural;
    while (it)
    {
        // check if the iterated strategy is the searched one
        if (it->strategy->datatype == datatype)
            return it->strategy;
        it = it->next;
    }

    pt.error.set (PT_ERROR_NOT_FOUND);
    return NULL;
} /* end of : pt_data_strategy_t *
              pt_data_pool_get_by_type (pt_data_type_t datatype) */

pt_data_strategy_t *
pt_data_pool_get_by_name (const char * name)
{
#ifndef NDEBUG
    // validate arguments
    if (!name)
    {
        pt.error.set (PT_ERROR_INVALID_POINTER);
        return NULL;
    }
#endif

    // singleton initialization
    if (   !pt_data_pool.initialized
        && pt_data_pool_init () != PT_ERROR_OK)
        return NULL;

    pt_data_pool_entry_t * it = NULL;

    // natural datatypes strategy lookup cycle
    it = pt_data_pool.natural;
    while (it)
    {
        // check if the iterated strategy is the searched one
        if (strcmp (it->strategy->name, name) == 0)
            return it->strategy;
        it = it->next;
    }

    // user defined datatypes strategy lookup cycle
    it = pt_data_pool.user;
    while (it)
    {
        // check if the iterated strategy is the searched one
        if (strcmp (it->strategy->name, name) == 0)
            return it->strategy;
        it = it->next;
    }

    pt.error.set (PT_ERROR_NOT_FOUND);
    return NULL;
} /* end of : pt_data_strategy_t *
              pt_data_pool_get_by_name (const char * name) */

pt_error_t
pt_data_pool_add (pt_data_strategy_t * strategy)
{
#ifndef NDEBUG
    // validate arguments
    if (!strategy)
        return pt.error.set (PT_ERROR_INVALID_POINTER);
#endif

    // singleton initialization
    pt_error_t error;
    if (   !pt_data_pool.initialized
        && (error = pt_data_pool_init ()) != PT_ERROR_OK)
        return error;

    // allocate memory to the inserting strategy entry
    pt_data_pool_entry_t * entry = NULL;
    if ((entry = malloc (sizeof (pt_data_pool_entry_t))) == NULL)
        return pt.error.set (PT_ERROR_NO_MEMORY);

    // initialize the created entry
    entry->next = pt_data_pool.user;
    entry->strategy = strategy;

    // add the inserting entry at the list head position
    pt_data_pool.user = entry;

    return PT_ERROR_OK;
} /* end of : pt_error_t
              pt_data_pool_add (pt_data_strategy_t * strategy) */

pt_error_t
pt_data_pool_clear (void)
{
    // singleton initialization
    pt_error_t error;
    if (   !pt_data_pool.initialized
        && (error = pt_data_pool_init ()) != PT_ERROR_OK)
        return error;

    // strategies removal cycle
    while (pt_data_pool.user)
    {
        // remove head strategy from the list
        pt_data_pool_entry_t * del = pt_data_pool.user;
        pt_data_pool.user = del->next;

        // releasing the memory of the removed strategy and node
        pt_data_strategy_destroy(& del->strategy);
        free(del);
    }

    return PT_ERROR_OK;
} /* end of : pt_error_t
              pt_data_pool_clear (void) */

// -----------------------------------------------------------------------------
// PRIVATE FUNCTIONS ALLUSIONS
// -----------------------------------------------------------------------------

pt_error_t
pt_data_pool_init (void)
{
    // initialization check
    if (!pt_data_pool.initialized)
    {
        // define the base data type value to be assigned to the registed user
        // defined types
        pt_data_pool.next_user_type = PT_DATATYPE_USER_DEFINED;

        // insert language natural datatypes strategies
        pt_data_pool_add_natural(pt_data_boolean());
        pt_data_pool_add_natural(pt_data_bit8());
        pt_data_pool_add_natural(pt_data_bit16());
        pt_data_pool_add_natural(pt_data_bit32());
        pt_data_pool_add_natural(pt_data_bit64());
        pt_data_pool_add_natural(pt_data_integer8());
        pt_data_pool_add_natural(pt_data_integer16());
        pt_data_pool_add_natural(pt_data_integer32());
        pt_data_pool_add_natural(pt_data_integer64());
        pt_data_pool_add_natural(pt_data_float32());
        pt_data_pool_add_natural(pt_data_float64());
        pt_data_pool_add_natural(pt_data_text());
        pt_data_pool_add_natural(pt_data_pointer());
        pt_data_pool_add_natural(pt_data_function());

        // singleton uninitialization registration
        atexit(pt_data_pool_uninit);
        pt_data_pool.initialized = 1;
    }

    return PT_ERROR_OK;
} /* end of : pt_error_t
              pt_data_pool_init (void) */

void
pt_data_pool_uninit (void)
{
    // initialization check
    if (pt_data_pool.initialized)
    {
        // removal of the registed strategies
        pt_data_pool_clear();
        pt_data_pool_clear_natural();

        // flaging of the singleton initialization state
        pt_data_pool.initialized = 0;
    }
} /* end of : void
              pt_data_pool_uninit (void) */

pt_error_t
pt_data_pool_add_natural (pt_data_strategy_t * strategy)
{
#ifndef NDEBUG
    // validate arguments
    if (!strategy)
        return pt.error.set (PT_ERROR_INVALID_POINTER);
#endif

    // allocate memory to the inserting strategy entry
    pt_data_pool_entry_t * entry = NULL;
    if ((entry = malloc (sizeof (pt_data_pool_entry_t))) == NULL)
        return pt.error.set (PT_ERROR_NO_MEMORY);

    // initialize the created entry
    entry->next = pt_data_pool.natural;
    entry->strategy = strategy;

    // add the inserting entry at the list head position
    pt_data_pool.natural = entry;

    return PT_ERROR_OK;
} /* end of : pt_error_t
              pt_data_pool_add_natural (pt_data_strategy_t * strategy) */

pt_error_t
pt_data_pool_clear_natural (void)
{
    // strategies removal cycle
    while (pt_data_pool.natural)
    {
        // remove head strategy from the list
        pt_data_pool_entry_t * del = pt_data_pool.natural;
        pt_data_pool.natural = del->next;

        // releasing the memory of the removed strategy and node
        pt_data_strategy_destroy(& del->strategy);
        free(del);
    }

    return PT_ERROR_OK;
} /* end of : pt_error_t
              pt_data_pool_clear_natural (void) */
