#include <math.h>
#include <stdio.h>
#include <string.h>

#include "internal/data/pt_data_natural.h"
#include "internal/data/type/pt_data_integer32.h"

// -----------------------------------------------------------------------------
// PRIVATE FUNCTIONS ALLUSIONS
// -----------------------------------------------------------------------------

/// @brief
///
/// @param strategy
///
/// @return
void *
pt_data_integer32_alloc (pt_data_strategy_t * strategy);

/// @brief
///
/// @param strategy
/// @param data
///
/// @return
pt_error_t
pt_data_integer32_free (pt_data_strategy_t * strategy,
                        void ** data);

/// @brief
///
/// @param strategy
///
/// @return
size_t
pt_data_integer32_get_init_size (pt_data_strategy_t * strategy);

/// @brief
///
/// @param strategy
/// @param data
///
/// @return
size_t
pt_data_integer32_get_current_size (pt_data_strategy_t * strategy,
                                    void * data);

/// @brief
///
/// @param src
/// @param args
/// @param dest
///
/// @return
void **
pt_data_integer32_cast_to_boolean (void * src,
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
pt_data_integer32_cast_to_bit8 (void * src,
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
pt_data_integer32_cast_to_integer8 (void * src,
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
pt_data_integer32_cast_to_bit16 (void * src,
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
pt_data_integer32_cast_to_integer16 (void * src,
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
pt_data_integer32_cast_to_bit32 (void * src,
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
pt_data_integer32_cast_to_bit64 (void * src,
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
pt_data_integer32_cast_to_integer64 (void * src,
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
pt_data_integer32_cast_to_float32 (void * src,
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
pt_data_integer32_cast_to_float64 (void * src,
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
pt_data_integer32_cast_to_text (void * src,
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
pt_data_integer32_sizeof (void * src,
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
pt_data_integer32_type (void * src,
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
pt_data_integer32_op_assign (void * src,
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
pt_data_integer32_op_add (void * src,
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
pt_data_integer32_op_subtract (void * src,
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
pt_data_integer32_op_multiply (void * src,
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
pt_data_integer32_op_divide (void * src,
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
pt_data_integer32_op_remainder (void * src,
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
pt_data_integer32_op_negative (void * src,
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
pt_data_integer32_op_power (void * src,
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
pt_data_integer32_op_equal (void * src,
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
pt_data_integer32_op_inequal (void * src,
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
pt_data_integer32_op_greater (void * src,
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
pt_data_integer32_op_greater_or_equal (void * src,
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
pt_data_integer32_op_lesser (void * src,
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
pt_data_integer32_op_lesser_or_equal (void * src,
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
pt_data_integer32_op_and (void * src,
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
pt_data_integer32_op_or (void * src,
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
pt_data_integer32_op_xor (void * src,
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
pt_data_integer32_op_negate (void * src,
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
pt_data_integer32_op_bit_and (void * src,
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
pt_data_integer32_op_bit_or (void * src,
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
pt_data_integer32_op_bit_xor (void * src,
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
pt_data_integer32_op_bit_negate (void * src,
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
pt_data_integer32_op_left_shift (void * src,
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
pt_data_integer32_op_right_shift (void * src,
                                  void ** args,
                                  void ** dest);

// -----------------------------------------------------------------------------
// INTERNAL FUNCTIONS
// -----------------------------------------------------------------------------

pt_data_strategy_t *
pt_data_integer32 (void) 
{
    pt_data_strategy_t * strategy = NULL;

    // allocate memory to the strategy structure
    if ((strategy = malloc (sizeof (pt_data_strategy_t))) == NULL) 
    {
        pt.error.set (PT_ERROR_NO_MEMORY);
        return NULL;
    }

    // allocate memory to the strategy name string
    size_t length = strlen (PT_LANG_INTEGER32) + 1;
    if ((strategy->name = malloc (length)) == NULL) 
    {
        free (strategy);
        pt.error.set (PT_ERROR_NO_MEMORY);
        return NULL;
    }

    // initialize the strategy structure
    strategy->datatype            = PT_DATATYPE_INTEGER32;
    strcpy (strategy->name, PT_LANG_INTEGER32);

    strategy->cb.alloc            = pt_data_integer32_alloc;
    strategy->cb.free             = pt_data_integer32_free;
    strategy->cb.get_init_size    = pt_data_integer32_get_init_size;
    strategy->cb.get_current_size = pt_data_integer32_get_current_size;

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

    // register the cast functions
    {
        pt_data_type_t params[] = { 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_BOOLEAN,
                                     PT_LANG_CAST,
                                     params,
                                     pt_data_integer32_cast_to_boolean);
    }
    {
        pt_data_type_t params[] = { 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_BIT8,
                                     PT_LANG_CAST,
                                     params,
                                     pt_data_integer32_cast_to_bit8);
    }
    {
        pt_data_type_t params[] = { 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_INTEGER8,
                                     PT_LANG_CAST,
                                     params,
                                     pt_data_integer32_cast_to_integer8);
    }
    {
        pt_data_type_t params[] = { 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_BIT16,
                                     PT_LANG_CAST,
                                     params,
                                     pt_data_integer32_cast_to_bit16);
    }
    {
        pt_data_type_t params[] = { 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_INTEGER16,
                                     PT_LANG_CAST,
                                     params,
                                     pt_data_integer32_cast_to_integer16);
    }
    {
        pt_data_type_t params[] = { 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_BIT32,
                                     PT_LANG_CAST,
                                     params,
                                     pt_data_integer32_cast_to_bit32);
    }
    {
        pt_data_type_t params[] = { 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_BIT64,
                                     PT_LANG_CAST,
                                     params,
                                     pt_data_integer32_cast_to_bit64);
    }
    {
        pt_data_type_t params[] = { 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_INTEGER64,
                                     PT_LANG_CAST,
                                     params,
                                     pt_data_integer32_cast_to_integer64);
    }
    {
        pt_data_type_t params[] = { 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_FLOAT32,
                                     PT_LANG_CAST,
                                     params,
                                     pt_data_integer32_cast_to_float32);
    }
    {
        pt_data_type_t params[] = { 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_FLOAT64,
                                     PT_LANG_CAST,
                                     params,
                                     pt_data_integer32_cast_to_float64);
    }
    {
        pt_data_type_t params[] = { 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_TEXT,
                                     PT_LANG_CAST,
                                     params,
                                     pt_data_integer32_cast_to_text);
    }

    // register the methods
    {
        pt_data_type_t params[] = { 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_INTEGER32,
                                     PT_LANG_SIZEOF,
                                     params,
                                     pt_data_integer32_sizeof);
    }
    {
        pt_data_type_t params[] = { 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_TEXT,
                                     PT_LANG_TYPE,
                                     params,
                                     pt_data_integer32_type);
    }

    // register the operators
    {
        pt_data_type_t params[] = { 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_INTEGER32,
                                     PT_LANG_ASSIGN,
                                     params,
                                     pt_data_integer32_op_assign);
    }
    {
        pt_data_type_t params[] = { PT_DATATYPE_INTEGER32, 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_INTEGER32,
                                     PT_LANG_ADD,
                                     params,
                                     pt_data_integer32_op_add);
    }
    {
        pt_data_type_t params[] = { PT_DATATYPE_INTEGER32, 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_INTEGER32,
                                     PT_LANG_SUBTRACT,
                                     params,
                                     pt_data_integer32_op_subtract);
    }
    {
        pt_data_type_t params[] = { PT_DATATYPE_INTEGER32, 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_INTEGER32,
                                     PT_LANG_MULTIPLY,
                                     params,
                                     pt_data_integer32_op_multiply);
    }
    {
        pt_data_type_t params[] = { PT_DATATYPE_INTEGER32, 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_INTEGER32,
                                     PT_LANG_DIVIDE,
                                     params,
                                     pt_data_integer32_op_divide);
    }
    {
        pt_data_type_t params[] = { PT_DATATYPE_INTEGER32, 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_INTEGER32,
                                     PT_LANG_REMAINDER,
                                     params,
                                     pt_data_integer32_op_remainder);
    }
    {
        pt_data_type_t params[] = { 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_INTEGER32,
                                     PT_LANG_NEGATIVE,
                                     params,
                                     pt_data_integer32_op_negative);
    }
    {
        pt_data_type_t params[] = { PT_DATATYPE_INTEGER32, 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_INTEGER32,
                                     PT_LANG_POWER,
                                     params,
                                     pt_data_integer32_op_power);
    }
    {
        pt_data_type_t params[] = { PT_DATATYPE_INTEGER32, 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_BOOLEAN,
                                     PT_LANG_EQUAL,
                                     params,
                                     pt_data_integer32_op_equal);
    }
    {
        pt_data_type_t params[] = { PT_DATATYPE_INTEGER32, 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_BOOLEAN,
                                     PT_LANG_INEQUAL,
                                     params,
                                     pt_data_integer32_op_inequal);
    }
    {
        pt_data_type_t params[] = { PT_DATATYPE_INTEGER32, 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_BOOLEAN,
                                     PT_LANG_GREATER,
                                     params,
                                     pt_data_integer32_op_greater);
    }
    {
        pt_data_type_t params[] = { PT_DATATYPE_INTEGER32, 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_BOOLEAN,
                                     PT_LANG_GREATER_OR_EQUAL,
                                     params,
                                     pt_data_integer32_op_greater_or_equal);
    }
    {
        pt_data_type_t params[] = { PT_DATATYPE_INTEGER32, 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_BOOLEAN,
                                     PT_LANG_LESSER,
                                     params,
                                     pt_data_integer32_op_lesser);
    }
    {
        pt_data_type_t params[] = { PT_DATATYPE_INTEGER32, 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_BOOLEAN,
                                     PT_LANG_LESSER_OR_EQUAL,
                                     params,
                                     pt_data_integer32_op_lesser_or_equal);
    }
    {
        pt_data_type_t params[] = { PT_DATATYPE_INTEGER32, 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_BOOLEAN,
                                     PT_LANG_AND,
                                     params,
                                     pt_data_integer32_op_and);
    }
    {
        pt_data_type_t params[] = { PT_DATATYPE_INTEGER32, 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_BOOLEAN,
                                     PT_LANG_OR,
                                     params,
                                     pt_data_integer32_op_or);
    }
    {
        pt_data_type_t params[] = { PT_DATATYPE_INTEGER32, 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_BOOLEAN,
                                     PT_LANG_XOR,
                                     params,
                                     pt_data_integer32_op_xor);
    }
    {
        pt_data_type_t params[] = { 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_INTEGER32,
                                     PT_LANG_NEGATE,
                                     params,
                                     pt_data_integer32_op_negate);
    }
    {
        pt_data_type_t params[] = { PT_DATATYPE_INTEGER32, 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_INTEGER32,
                                     PT_LANG_BIT_AND,
                                     params,
                                     pt_data_integer32_op_bit_and);
    }
    {
        pt_data_type_t params[] = { PT_DATATYPE_INTEGER32, 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_INTEGER32,
                                     PT_LANG_BIT_OR,
                                     params,
                                     pt_data_integer32_op_bit_or);
    }
    {
        pt_data_type_t params[] = { PT_DATATYPE_INTEGER32, 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_INTEGER32,
                                     PT_LANG_BIT_XOR,
                                     params,
                                     pt_data_integer32_op_bit_xor);
    }
    {
        pt_data_type_t params[] = { 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_INTEGER32,
                                     PT_LANG_BIT_NEGATE,
                                     params,
                                     pt_data_integer32_op_bit_negate);
    }
    {
        pt_data_type_t params[] = { PT_DATATYPE_INTEGER32, 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_INTEGER32,
                                     PT_LANG_LEFT_SHIFT,
                                     params,
                                     pt_data_integer32_op_left_shift);
    }
    {
        pt_data_type_t params[] = { PT_DATATYPE_INTEGER32, 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_INTEGER32,
                                     PT_LANG_RIGHT_SHIFT,
                                     params,
                                     pt_data_integer32_op_right_shift);
    }

    return strategy;
} /* end of : pt_data_strategy_t *
              pt_data_integer32 (void) */

// -----------------------------------------------------------------------------
// PRIVATE FUNCTIONS
// -----------------------------------------------------------------------------

void *
pt_data_integer32_alloc (pt_data_strategy_t * strategy)
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
    if ((data = calloc (1, sizeof(int32_t))) == NULL) 
    {
        pt.error.set (PT_ERROR_NO_MEMORY);
        return NULL;
    }

    return data;
} /* end of : void *
              pt_data_integer32_alloc (pt_data_strategy_t * strategy) */

pt_error_t
pt_data_integer32_free (pt_data_strategy_t * strategy,
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
              pt_data_integer32_free (pt_data_strategy_t * strategy,
                                      void ** data) */

size_t
pt_data_integer32_get_init_size (pt_data_strategy_t * strategy)
{
#ifndef NDEBUG
    // validate arguments
    if (!strategy) 
    {
        pt.error.set (PT_ERROR_INVALID_POINTER);
        return 0;
    }
#endif

    return sizeof (int32_t);
} /* end of : size_t
              pt_data_integer32_get_init_size (pt_data_strategy_t * strategy) */

size_t
pt_data_integer32_get_current_size (pt_data_strategy_t * strategy,
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

    return sizeof (int32_t);
} /* end of : size_t
              pt_data_integer32_get_current_size (pt_data_strategy_t * strategy,
                                                  void * data) */

void **
pt_data_integer32_cast_to_boolean (void * src,
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

    // perform the cast and store the resulting value into the dest pointer
    ** (uint8_t **) dest = (uint8_t) (* (int32_t *) src != 0);

    return dest;
} /* end of : void **
              pt_data_integer32_cast_to_boolean (void * src,
                                                 void ** args,
                                                 void ** dest) */

void **
pt_data_integer32_cast_to_bit8 (void * src,
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

    // perform the cast and store the resulting value into the dest pointer
    ** (uint8_t **) dest = (uint8_t) * (int32_t *) src;

    return dest;
} /* end of : void **
              pt_data_integer32_cast_to_bit8 (void * src,
                                              void ** args,
                                              void ** dest) */

void **
pt_data_integer32_cast_to_integer8 (void * src,
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

    // perform the cast and store the resulting value into the dest pointer
    ** (int8_t **) dest = (int8_t) * (int32_t *) src;

    return dest;
} /* end of : void **
              pt_data_integer32_cast_to_inteegr8 (void * src,
                                                  void ** args,
                                                  void ** dest) */

void **
pt_data_integer32_cast_to_bit16 (void * src,
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

    // perform the cast and store the resulting value into the dest pointer
    ** (uint16_t **) dest = (uint16_t) * (int32_t *) src;

    return dest;
} /* end of : void **
              pt_data_integer32_cast_to_bit16 (void * src,
                                               void ** args,
                                               void ** dest) */

void **
pt_data_integer32_cast_to_integer16 (void * src,
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

    // perform the cast and store the resulting value into the dest pointer
    ** (int16_t **) dest = (int16_t) * (int32_t *) src;

    return dest;
} /* end of : void **
              pt_data_integer32_cast_to_integer16 (void * src,
                                                   void ** args,
                                                   void ** dest) */

void **
pt_data_integer32_cast_to_bit32 (void * src,
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

    // perform the cast and store the resulting value into the dest pointer
    ** (uint32_t **) dest = (uint32_t) * (int32_t *) src;

    return dest;
} /* end of : void **
              pt_data_integer32_cast_to_bit32 (void * src,
                                               void ** args,
                                               void ** dest) */

void **
pt_data_integer32_cast_to_bit64 (void * src,
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

    // perform the cast and store the resulting value into the dest pointer
    ** (uint64_t **) dest = (uint64_t) * (int32_t *) src;

    return dest;
} /* end of : void **
              pt_data_integer32_cast_to_bit64 (void * src,
                                               void ** args,
                                               void ** dest) */

void **
pt_data_integer32_cast_to_integer64 (void * src,
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

    // perform the cast and store the resulting value into the dest pointer
    ** (int64_t **) dest = (int64_t) * (int32_t *) src;

    return dest;
} /* end of : void **
              pt_data_integer32_cast_to_integer64 (void * src,
                                                   void ** args,
                                                   void ** dest) */

void **
pt_data_integer32_cast_to_float32 (void * src,
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

    // perform the cast and store the resulting value into the dest pointer
    ** (float **) dest = (float) * (int32_t *) src;

    return dest;
} /* end of : void **
              pt_data_integer32_cast_to_float32 (void * src,
                                                 void ** args,
                                                 void ** dest) */

void **
pt_data_integer32_cast_to_float64 (void * src,
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

    // perform the cast and store the resulting value into the dest pointer
    ** (double **) dest = (double) * (int32_t *) src;

    return dest;
} /* end of : void **
              pt_data_integer32_cast_to_float64 (void * src,
                                                 void ** args,
                                                 void ** dest) */

void **
pt_data_integer32_cast_to_text (void * src,
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

    // reallocate the memory to store the cast text
    char * result = NULL;
    if ((result = realloc (* (char **) dest, 16)) == NULL)
    {
        pt.error.set (PT_ERROR_NO_MEMORY);
        return NULL;
    }

    // write the value into the cast string
    snprintf (result, 16, "%d", * (int32_t *) src);
    * (char **) dest = result;

    return dest;
} /* end of : void **
              pt_data_integer32_cast_to_text (void * src,
                                              void ** args,
                                              void ** dest) */

void **
pt_data_integer32_sizeof (void * src,
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

    ** (int32_t **) dest = sizeof (int32_t);

    return dest;
} /* end of : void **
              pt_data_integer32_sizeof (void * src,
                                        void ** args,
                                        void ** dest) */

void **
pt_data_integer32_type (void * src,
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
    snprintf (result, 16, "%s", PT_LANG_INTEGER32);
    * (char **) dest = result;

    return dest;
} /* end of : void **
              pt_data_integer32_type (void * src,
                                      void ** args,
                                      void ** dest) */

void **
pt_data_integer32_op_assign (void * src,
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

    ** (int32_t **) dest = * (int32_t *) src;

    return dest;
} /* end of : void **
              pt_data_integer32_op_assign (void * src,
                                           void ** args,
                                           void ** dest) */

void **
pt_data_integer32_op_add (void * src,
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

    ** (int32_t **) dest = * (int32_t *) src + * (int32_t *) args[0];

    return dest;
} /* end of : void **
              pt_data_integer32_op_add (void * src,
                                        void ** args,
                                        void ** dest) */

void **
pt_data_integer32_op_subtract (void * src,
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

    ** (int32_t **) dest = * (int32_t *) src - * (int32_t *) args[0];

    return dest;
} /* end of : void **
              pt_data_integer32_op_subtract (void * src,
                                             void ** args,
                                             void ** dest) */

void **
pt_data_integer32_op_multiply (void * src,
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

    ** (int32_t **) dest = * (int32_t *) src * * (int32_t *) args[0];

    return dest;
} /* end of : void **
              pt_data_integer32_op_multiply (void * src,
                                             void ** args,
                                             void ** dest) */

void **
pt_data_integer32_op_divide (void * src,
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

    // TODO : check for divide-by-zero at runtime

    ** (int32_t **) dest = * (int32_t *) src / * (int32_t *) args[0];

    return dest;
} /* end of : void **
              pt_data_integer32_op_divide (void * src,
                                           void ** args,
                                           void ** dest) */

void **
pt_data_integer32_op_remainder (void * src,
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

    // TODO : check for divide-by-zero at runtime

    ** (int32_t **) dest = * (int32_t *) src % * (int32_t *) args[0];

    return dest;
} /* end of : void **
              pt_data_integer32_op_remainder (void * src,
                                              void ** args,
                                              void ** dest) */

void **
pt_data_integer32_op_negative (void * src,
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

    ** (int32_t **) dest = - * (int32_t *) src;

    return dest;
} /* end of : void **
              pt_data_integer32_op_negative (void * src,
                                             void ** args,
                                             void ** dest) */

void **
pt_data_integer32_op_power (void * src,
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

    ** (int32_t **) dest = pow(* (int32_t *) src, * (int32_t *) args[0]);

    return dest;
} /* end of : void **
              pt_data_integer32_op_power (void * src,
                                          void ** args,
                                          void ** dest) */

void **
pt_data_integer32_op_equal (void * src,
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

    ** (uint8_t **) dest = * (int32_t *) src == * (int32_t *) args[0];

    return dest;
} /* end of : void **
              pt_data_integer32_op_equal (void * src,
                                          void ** args,
                                          void ** dest) */

void **
pt_data_integer32_op_inequal (void * src,
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

    ** (uint8_t **) dest = * (int32_t *) src != * (int32_t *) args[0];

    return dest;
} /* end of  void **
             pt_data_integer32_op_inequal (void * src,
                                           void ** args,
                                           void ** dest) */

void **
pt_data_integer32_op_greater (void * src,
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

    ** (uint8_t **) dest = * (int32_t *) src > * (int32_t *) args[0];

    return dest;
} /* end of : void **
              pt_data_integer32_op_greater (void * src,
                                            void ** args,
                                            void ** dest) */

void **
pt_data_integer32_op_greater_or_equal (void * src,
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

    ** (uint8_t **) dest = * (int32_t *) src >= * (int32_t *) args[0];

    return dest;
} /* end of : void **
              pt_data_integer32_op_greater_or_equal (void * src,
                                                     void ** args,
                                                     void ** dest) */

void **
pt_data_integer32_op_lesser (void * src,
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

    ** (uint8_t **) dest = * (int32_t *) src < * (int32_t *) args[0];

    return dest;
} /* end of : void **
              pt_data_integer32_op_lesser (void * src,
                                           void ** args,
                                           void ** dest) */

void **
pt_data_integer32_op_lesser_or_equal (void * src,
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

    ** (uint8_t **) dest = * (int32_t *) src <= * (int32_t *) args[0];

    return dest;
} /* end of : void **
              pt_data_integer32_op_lesser_or_equal (void * src,
                                                    void ** args,
                                                    void ** dest) */

void **
pt_data_integer32_op_and (void * src,
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

    ** (uint8_t **) dest = * (int32_t *) src && * (int32_t *) args[0];

    return dest;
} /* end of : void **
              pt_data_integer32_op_and (void * src,
                                        void ** args,
                                        void ** dest) */

void **
pt_data_integer32_op_or (void * src,
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

    ** (uint8_t **) dest = * (int32_t *) src || * (int32_t *) args[0];

    return dest;
} /* end of : void **
              pt_data_integer32_op_or (void * src,
                                       void ** args,
                                       void ** dest) */

void **
pt_data_integer32_op_xor (void * src,
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

    ** (uint8_t **) dest =    (  * (int32_t *) src &&   * (int32_t *) args[0])
                           || (! * (int32_t *) src && ! * (int32_t *) args[0]);

    return dest;
} /* end of : void **
              pt_data_integer32_op_xor (void * src,
                                        void ** args,
                                        void ** dest) */

void **
pt_data_integer32_op_negate (void * src,
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

    ** (int32_t **) dest = ! * (int32_t *) src;

    return dest;
} /* end of : void **
              pt_data_integer32_op_negate (void * src,
                                           void ** args,
                                           void ** dest) */

void **
pt_data_integer32_op_bit_and (void * src,
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

    ** (int32_t **) dest = * (int32_t *) src & * (int32_t *) args[0];

    return dest;
} /* end of : void **
              pt_data_integer32_op_bit_and (void * src,
                                            void ** args,
                                            void ** dest) */

void **
pt_data_integer32_op_bit_or (void * src,
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

    ** (int32_t **) dest = * (int32_t *) src | * (int32_t *) args[0];

    return dest;
} /* end of : void **
              pt_data_integer32_op_bit_or (void * src,
                                           void ** args,
                                           void ** dest) */

void **
pt_data_integer32_op_bit_xor (void * src,
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

    ** (int32_t **) dest = * (int32_t *) src ^ * (int32_t *) args[0];

    return dest;
} /* end of : void **
              pt_data_integer32_op_bit_xor (void * src,
                                            void ** args,
                                            void ** dest) */

void **
pt_data_integer32_op_bit_negate (void * src,
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

    ** (int32_t **) dest = ~ * (int32_t *) src;

    return dest;
} /* end of : void **
              pt_data_integer32_op_bit_negate (void * src,
                                               void ** args,
                                               void ** dest) */

void **
pt_data_integer32_op_left_shift (void * src,
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

    ** (int32_t **) dest = * (int32_t *) src << * (int32_t *) args[0];

    return dest;
} /* end of : void **
              pt_data_integer32_op_left_shift (void * src,
                                               void ** args,
                                               void ** dest) */

void **
pt_data_integer32_op_right_shift (void * src,
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

    ** (int32_t **) dest = * (int32_t *) src >> * (int32_t *) args[0];

    return dest;
} /* end of : void **
              pt_data_integer32_op_right_shift (void * src,
                                                void ** args,
                                                void ** dest) */
