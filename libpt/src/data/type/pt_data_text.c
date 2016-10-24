#include <math.h>
#include <stdio.h>
#include <string.h>

#include "internal/data/pt_data_natural.h"
#include "internal/data/type/pt_data_text.h"

// -----------------------------------------------------------------------------
// PRIVATE FUNCTIONS ALLUSIONS
// -----------------------------------------------------------------------------

/// @brief
///
/// @param strategy
///
/// @return
void *
pt_data_text_alloc (pt_data_strategy_t * strategy);

/// @brief
///
/// @param strategy
/// @param data
///
/// @return
pt_error_t
pt_data_text_free (pt_data_strategy_t * strategy,
                   void ** data);

/// @brief
///
/// @param strategy
///
/// @return
size_t
pt_data_text_get_init_size (pt_data_strategy_t * strategy);

/// @brief
///
/// @param strategy
/// @param data
///
/// @return
size_t
pt_data_text_get_current_size (pt_data_strategy_t * strategy,
                               void * data);

/// @brief
///
/// @param src
/// @param args
/// @param dest
///
/// @return
void **
pt_data_text_cast_to_boolean (void * src,
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
pt_data_text_cast_to_bit8 (void * src,
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
pt_data_text_cast_to_integer8 (void * src,
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
pt_data_text_cast_to_bit16 (void * src,
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
pt_data_text_cast_to_integer16 (void * src,
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
pt_data_text_cast_to_bit32 (void * src,
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
pt_data_text_cast_to_integer32 (void * src,
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
pt_data_text_cast_to_bit64 (void * src,
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
pt_data_text_cast_to_integer64 (void * src,
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
pt_data_text_cast_to_float32 (void * src,
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
pt_data_text_cast_to_float64 (void * src,
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
pt_data_text_sizeof (void * src,
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
pt_data_text_type (void * src,
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
pt_data_text_op_assign (void * src,
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
pt_data_text_op_add (void * src,
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
pt_data_text_op_equal (void * src,
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
pt_data_text_op_inequal (void * src,
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
pt_data_text_op_greater (void * src,
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
pt_data_text_op_greater_or_equal (void * src,
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
pt_data_text_op_lesser (void * src,
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
pt_data_text_op_lesser_or_equal (void * src,
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
pt_data_text_op_and (void * src,
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
pt_data_text_op_or (void * src,
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
pt_data_text_op_xor (void * src,
                     void ** args,
                     void ** dest);

// -----------------------------------------------------------------------------
// INTERNAL FUNCTIONS
// -----------------------------------------------------------------------------

pt_data_strategy_t *
pt_data_text (void) 
{
    pt_data_strategy_t * strategy = NULL;

    // allocate memory to the strategy structure
    if ((strategy = malloc (sizeof (pt_data_strategy_t))) == NULL) 
    {
        pt.error.set (PT_ERROR_NO_MEMORY);
        return NULL;
    }

    // allocate memory to the strategy name string
    size_t length = strlen (PT_LANG_TEXT) + 1;
    if ((strategy->name = malloc (length)) == NULL) 
    {
        free (strategy);
        pt.error.set (PT_ERROR_NO_MEMORY);
        return NULL;
    }

    // initialize the strategy structure
    strategy->datatype            = PT_DATATYPE_TEXT;
    strcpy (strategy->name, PT_LANG_TEXT);

    strategy->cb.alloc            = pt_data_text_alloc;
    strategy->cb.free             = pt_data_text_free;
    strategy->cb.get_init_size    = pt_data_text_get_init_size;
    strategy->cb.get_current_size = pt_data_text_get_current_size;

    strategy->cb.is_cast          = pt_data_natural_is_cast;
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
                                     pt_data_text_cast_to_boolean);
    }
    {
        pt_data_type_t params[] = { 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_BIT8,
                                     PT_LANG_CAST,
                                     params,
                                     pt_data_text_cast_to_bit8);
    }
    {
        pt_data_type_t params[] = { 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_INTEGER8,
                                     PT_LANG_CAST,
                                     params,
                                     pt_data_text_cast_to_integer8);
    }
    {
        pt_data_type_t params[] = { 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_BIT16,
                                     PT_LANG_CAST,
                                     params,
                                     pt_data_text_cast_to_bit16);
    }
    {
        pt_data_type_t params[] = { 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_INTEGER16,
                                     PT_LANG_CAST,
                                     params,
                                     pt_data_text_cast_to_integer16);
    }
    {
        pt_data_type_t params[] = { 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_BIT32,
                                     PT_LANG_CAST,
                                     params,
                                     pt_data_text_cast_to_bit32);
    }
    {
        pt_data_type_t params[] = { 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_INTEGER32,
                                     PT_LANG_CAST,
                                     params,
                                     pt_data_text_cast_to_integer32);
    }
    {
        pt_data_type_t params[] = { 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_BIT64,
                                     PT_LANG_CAST,
                                     params,
                                     pt_data_text_cast_to_bit64);
    }
    {
        pt_data_type_t params[] = { 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_INTEGER64,
                                     PT_LANG_CAST,
                                     params,
                                     pt_data_text_cast_to_integer64);
    }
    {
        pt_data_type_t params[] = { 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_FLOAT32,
                                     PT_LANG_CAST,
                                     params,
                                     pt_data_text_cast_to_float32);
    }
    {
        pt_data_type_t params[] = { 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_FLOAT64,
                                     PT_LANG_CAST,
                                     params,
                                     pt_data_text_cast_to_float64);
    }

    // register the methods
    {
        pt_data_type_t params[] = { 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_INTEGER32,
                                     PT_LANG_SIZEOF,
                                     params,
                                     pt_data_text_sizeof);
    }
    {
        pt_data_type_t params[] = { 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_TEXT,
                                     PT_LANG_TYPE,
                                     params,
                                     pt_data_text_type);
    }

    // register the operators
    {
        pt_data_type_t params[] = { 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_TEXT,
                                     PT_LANG_ASSIGN,
                                     params,
                                     pt_data_text_op_assign);
    }
    {
        pt_data_type_t params[] = { PT_DATATYPE_TEXT, 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_TEXT,
                                     PT_LANG_ADD,
                                     params,
                                     pt_data_text_op_add);
    }
    {
        pt_data_type_t params[] = { PT_DATATYPE_TEXT, 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_BOOLEAN,
                                     PT_LANG_EQUAL,
                                     params,
                                     pt_data_text_op_equal);
    }
    {
        pt_data_type_t params[] = { PT_DATATYPE_TEXT, 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_BOOLEAN,
                                     PT_LANG_INEQUAL,
                                     params,
                                     pt_data_text_op_inequal);
    }
    {
        pt_data_type_t params[] = { PT_DATATYPE_TEXT, 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_BOOLEAN,
                                     PT_LANG_GREATER,
                                     params,
                                     pt_data_text_op_greater);
    }
    {
        pt_data_type_t params[] = { PT_DATATYPE_TEXT, 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_BOOLEAN,
                                     PT_LANG_GREATER_OR_EQUAL,
                                     params,
                                     pt_data_text_op_greater_or_equal);
    }
    {
        pt_data_type_t params[] = { PT_DATATYPE_TEXT, 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_BOOLEAN,
                                     PT_LANG_LESSER,
                                     params,
                                     pt_data_text_op_lesser);
    }
    {
        pt_data_type_t params[] = { PT_DATATYPE_TEXT, 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_BOOLEAN,
                                     PT_LANG_LESSER_OR_EQUAL,
                                     params,
                                     pt_data_text_op_lesser_or_equal);
    }
    {
        pt_data_type_t params[] = { PT_DATATYPE_TEXT, 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_BOOLEAN,
                                     PT_LANG_AND,
                                     params,
                                     pt_data_text_op_and);
    }
    {
        pt_data_type_t params[] = { PT_DATATYPE_TEXT, 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_BOOLEAN,
                                     PT_LANG_OR,
                                     params,
                                     pt_data_text_op_or);
    }
    {
        pt_data_type_t params[] = { PT_DATATYPE_TEXT, 0 };
        pt_data_strategy_add_method (strategy,
                                     PT_DATATYPE_BOOLEAN,
                                     PT_LANG_XOR,
                                     params,
                                     pt_data_text_op_xor);
    }

    return strategy;
} /* end of : pt_data_strategy_t *
              pt_data_text (void) */

// -----------------------------------------------------------------------------
// PRIVATE FUNCTIONS
// -----------------------------------------------------------------------------

void *
pt_data_text_alloc (pt_data_strategy_t * strategy)
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
    if ((data = calloc (1, sizeof(char))) == NULL) 
    {
        pt.error.set (PT_ERROR_NO_MEMORY);
        return NULL;
    }

    return data;
} /* end of : void *
              pt_data_text_alloc (pt_data_strategy_t * strategy) */

pt_error_t
pt_data_text_free (pt_data_strategy_t * strategy,
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
              pt_data_text_free (pt_data_strategy_t * strategy,
                                 void ** data) */

size_t
pt_data_text_get_init_size (pt_data_strategy_t * strategy)
{
#ifndef NDEBUG
    // validate arguments
    if (!strategy) 
    {
        pt.error.set (PT_ERROR_INVALID_POINTER);
        return 0;
    }
#endif

    return sizeof (char);
} /* end of : size_t
              pt_data_text_get_init_size (pt_data_strategy_t * strategy) */

size_t
pt_data_text_get_current_size (pt_data_strategy_t * strategy,
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

    return strlen ((char *) data);
} /* end of : size_t
              pt_data_text_get_current_size (pt_data_strategy_t * strategy,
                                             void * data) */

void **
pt_data_text_cast_to_boolean (void * src,
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

    // check if there is a text and is not the language false default text
    ** (uint8_t **) dest = 0;
    if (   * (char *) src != 0
        && strcmp ((char *) src, PT_LANG_FALSE) != 0)
        ** (uint8_t **) dest = 1;

    return dest;
} /* end of : void **
              pt_data_text_cast_to_boolean (void * src,
                                            void ** args,
                                            void ** dest) */

void **
pt_data_text_cast_to_bit8 (void * src,
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

    // read the numeric value from the text
    sscanf ((char *) src, "%hhu", * (uint8_t **) dest);

    return dest;
} /* end of : void **
              pt_data_text_cast_to_bit8 (void * src,
                                         void ** args,
                                         void ** dest) */

void **
pt_data_text_cast_to_integer8 (void * src,
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

    // read the numeric value from the text
    sscanf ((char *) src, "%hhd", * (int8_t **) dest);

    return dest;
} /* end of : void **
              pt_data_text_cast_to_inteegr8 (void * src,
                                             void ** args,
                                             void ** dest) */

void **
pt_data_text_cast_to_bit16 (void * src,
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

    // read the numeric value from the text
    sscanf ((char *) src, "%hu", * (uint16_t **) dest);

    return dest;
} /* end of : void **
              pt_data_text_cast_to_bit16 (void * src,
                                          void ** args,
                                          void ** dest) */

void **
pt_data_text_cast_to_integer16 (void * src,
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

    // read the numeric value from the text
    sscanf ((char *) src, "%hd", * (int16_t **) dest);

    return dest;
} /* end of : void **
              pt_data_text_cast_to_integer16 (void * src,
                                              void ** args,
                                              void ** dest) */

void **
pt_data_text_cast_to_bit32 (void * src,
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

    // read the numeric value from the text
    sscanf ((char *) src, "%u", * (uint32_t **) dest);

    return dest;
} /* end of : void **
              pt_data_text_cast_to_bit32 (void * src,
                                          void ** args,
                                          void ** dest) */

void **
pt_data_text_cast_to_integer32 (void * src,
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

    // read the numeric value from the text
    sscanf ((char *) src, "%d", * (int32_t **) dest);

    return dest;
} /* end of : void **
              pt_data_text_cast_to_integer32 (void * src,
                                              void ** args,
                                              void ** dest) */

void **
pt_data_text_cast_to_bit64 (void * src,
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

    // read the numeric value from the text
    sscanf ((char *) src, "%lu", * (uint64_t **) dest);

    return dest;
} /* end of : void **
              pt_data_text_cast_to_bit64 (void * src,
                                          void ** args,
                                          void ** dest) */

void **
pt_data_text_cast_to_integer64 (void * src,
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

    // read the numeric value from the text
    sscanf ((char *) src, "%ld", * (int64_t **) dest);

    return dest;
} /* end of : void **
              pt_data_text_cast_to_integer64 (void * src,
                                              void ** args,
                                              void ** dest) */

void **
pt_data_text_cast_to_float32 (void * src,
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

    // read the numeric value from the text
    sscanf ((char *) src, "%f", * (float **) dest);

    return dest;
} /* end of : void **
              pt_data_text_cast_to_float32 (void * src,
                                            void ** args,
                                            void ** dest) */

void **
pt_data_text_cast_to_float64 (void * src,
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

    // read the numeric value from the text
    sscanf ((char *) src, "%lf", * (double **) dest);

    return dest;
} /* end of : void **
              pt_data_text_cast_to_float64 (void * src,
                                            void ** args,
                                            void ** dest) */

void **
pt_data_text_sizeof (void * src,
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

    ** (int32_t **) dest = strlen (src);

    return dest;
} /* end of : void **
              pt_data_text_sizeof (void * src,
                                   void ** args,
                                   void ** dest) */

void **
pt_data_text_type (void * src,
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
    snprintf (result, 16, "%s", PT_LANG_TEXT);
    * (char **) dest = result;

    return dest;
} /* end of : void **
              pt_data_text_type (void * src,
                                 void ** args,
                                 void ** dest) */

void **
pt_data_text_op_assign (void * src,
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

    // determine the length of the source text
    size_t length = strlen((void *) src);

    // reallocate the destination memory
    char * result = NULL;
    if ((result = realloc (* (char **) dest, length + 1)) == NULL)
    {
        pt.error.set (PT_ERROR_NO_MEMORY);
        return NULL;
    }

    // copy the source text to the reallocated memory
    strcpy (result, (char *) src);
    * (char **) dest = result;

    return dest;
} /* end of : void **
              pt_data_text_op_assign (void * src,
                                      void ** args,
                                      void ** dest) */

void **
pt_data_text_op_add (void * src,
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

    // determine the length of the source and argument text
    size_t src_length = strlen (src);
    size_t arg_length = strlen (args[0]);

    // reallocate the destination memory
    char * result = NULL;
    if ((result = realloc (* (char **) dest, src_length + arg_length + 1)) == NULL)
    {
        pt.error.set (PT_ERROR_NO_MEMORY);
        return NULL;
    }

    // copy the source and destination text to the reallocated memory
    strcpy (result, (char *) src);
    strcpy (result + src_length, (char *) args[0]);
    * (char **) dest = result;

    return dest;
} /* end of : void **
              pt_data_text_op_add (void * src,
                                   void ** args,
                                   void ** dest) */

void **
pt_data_text_op_equal (void * src,
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

    ** (uint8_t **) dest = strcmp (src, args[0]) == 0;

    return dest;
} /* end of : void **
              pt_data_text_op_equal (void * src,
                                     void ** args,
                                     void ** dest) */

void **
pt_data_text_op_inequal (void * src,
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

    ** (uint8_t **) dest = strcmp (src, args[0]) != 0;

    return dest;
} /* end of  void **
             pt_data_text_op_inequal (void * src,
                                      void ** args,
                                      void ** dest) */

void **
pt_data_text_op_greater (void * src,
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

    ** (uint8_t **) dest = strcmp (src, args[0]) > 0;

    return dest;
} /* end of : void **
              pt_data_text_op_greater (void * src,
                                       void ** args,
                                       void ** dest) */

void **
pt_data_text_op_greater_or_equal (void * src,
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

    ** (uint8_t **) dest = strcmp (src, args[0]) >= 0;

    return dest;
} /* end of : void **
              pt_data_text_op_greater_or_equal (void * src,
                                                void ** args,
                                                void ** dest) */

void **
pt_data_text_op_lesser (void * src,
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

    ** (uint8_t **) dest = strcmp (src, args[0]) < 0;

    return dest;
} /* end of : void **
              pt_data_text_op_lesser (void * src,
                                      void ** args,
                                      void ** dest) */

void **
pt_data_text_op_lesser_or_equal (void * src,
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

    ** (uint8_t **) dest = strcmp (src, args[0]) <= 0;

    return dest;
} /* end of : void **
              pt_data_text_op_lesser_or_equal (void * src,
                                               void ** args,
                                               void ** dest) */

void **
pt_data_text_op_and (void * src,
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

    // check if there is a text and is not the language false default text
    int srcval = 0;
    if (   * (char *) src != 0
        && strcmp ((char *) src, PT_LANG_FALSE) != 0)
        srcval = 1;

    int argval = 0;
    if (   * (char *) src != 0
        && strcmp ((char *) src, PT_LANG_FALSE) != 0)
        argval = 1;

    // compare the source and argument values
    ** (uint8_t **) dest = srcval && argval;

    return dest;
} /* end of : void **
              pt_data_text_op_and (void * src,
                                   void ** args,
                                   void ** dest) */

void **
pt_data_text_op_or (void * src,
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

    // check if there is a text and is not the language false default text
    int srcval = 0;
    if (   * (char *) src != 0
        && strcmp ((char *) src, PT_LANG_FALSE) != 0)
        srcval = 1;

    int argval = 0;
    if (   * (char *) src != 0
        && strcmp ((char *) src, PT_LANG_FALSE) != 0)
        argval = 1;

    // compare the source and argument values
    ** (uint8_t **) dest = srcval || argval;

    return dest;
} /* end of : void **
              pt_data_text_op_or (void * src,
                                  void ** args,
                                  void ** dest) */

void **
pt_data_text_op_xor (void * src,
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

    // check if there is a text and is not the language false default text
    int srcval = 0;
    if (   * (char *) src != 0
        && strcmp ((char *) src, PT_LANG_FALSE) != 0)
        srcval = 1;

    int argval = 0;
    if (   * (char *) src != 0
        && strcmp ((char *) src, PT_LANG_FALSE) != 0)
        argval = 1;

    // compare the source and argument values
    ** (uint8_t **) dest =    ( srcval &&  argval)
                           || (!srcval && !argval);

    return dest;
} /* end of : void **
              pt_data_text_op_xor (void * src,
                                   void ** args,
                                   void ** dest) */
