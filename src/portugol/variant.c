#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <internal/mem.h>
#include <internal/portugol/variant.h>

/*******************************************************************************
 * PUBLIC FUNCTIONS
 ******************************************************************************/

Variant*
variant_init(Variant* variant,
             const Variant* value)
{
    /* check if there is a variant to copy */
    if (value)
    {
        switch (value->type)
        {
            case VBOOLEAN:
                return variant_init_boolean(variant, value->value.vboolean);
            case VINT32:
                return variant_init_int32(variant, value->value.vint32);
            case VFLOAT32:
                return variant_init_float32(variant, value->value.vfloat32);
            case VTEXT:
                return variant_init_text(variant, value->value.vtext);
            case VPOINTER:
                return variant_init_pointer(variant, value->value.vpointer);
            case VFUNCTION:
                return variant_init_function(variant, value->value.vfunction);
            default:
                break;;
        }
    }

    return variant_init_int32(variant, 0);
} /* end of : Variant*
              variant_init(Variant* variant,
                           const Variant* value) */

Variant*
variant_init_type(Variant* variant,
                  const VType type)
{
    /* demux the type of initialization */
    switch (type)
    {
        case VBOOLEAN:
            return variant_init_boolean(variant, 0);
        case VFLOAT32:
            return variant_init_float32(variant, 0.0f);
        case VTEXT:
            return variant_init_text(variant, "");
        case VPOINTER:
            return variant_init_pointer(variant, NULL);
        case VFUNCTION:
            return variant_init_function(variant, NULL);
        default:
            break;
    }

    /* fallback to the default int32 value */
    return variant_init_int32(variant, 0);
} /* end of : Variant*
              variant_init_type(Variant* variant,
                                const VType type) */

Variant*
variant_init_boolean(Variant* variant,
                     const int8_t value)
{
    if (variant)
    {
        /* initialize a boolean variant */
        memset(variant, 0, sizeof(Variant));
        variant->type = VBOOLEAN;
        variant->value.vboolean = value;
    }

    return variant;
} /* end of : Variant*
              variant_init_boolean(Variant* variant,
                                   const int8_t value) */

Variant*
variant_init_boolean_ex(Variant* variant,
                        const char* value_str)
{
    int32_t value = 0;

    if (value_str)
    {
#ifdef _MSC_VER
        /* scan the source string for a numerical value */
        if (sscanf_s(value_str, "%d", &variant->value.vboolean) == 0)
        {
            /* scan the source string for a textual value */
            value = strcmp(value_str, "verdadeiro") == 0;
        }
#else
        /* scan the source string for a numerical value */
        if (sscanf(value_str, "%d", &value) == 0)
        {
            /* scan the source string for a textual value */
            value = strcmp(value_str, "verdadeiro") == 0;
        }
#endif /* _MSC_VER */

        /* normalize the value to 0 or 1 */
        value = value != 0;
    }

    return variant_init_boolean(variant, (int8_t) value);
} /* end of : Variant*
              variant_init_boolean_ex(Variant* variant,
                                      const char* value_str) */

Variant*
variant_init_int32(Variant* variant,
                   const int32_t value)
{
    if (variant)
    {
        /* initialize a int32 variant */
        memset(variant, 0, sizeof(Variant));
        variant->type = VINT32;
        variant->value.vint32 = value;
    }

    return variant;
} /* end of : Variant*
              variant_init_int32(Variant* variant,
                                 const int32_t value) */

Variant*
variant_init_int32_ex(Variant* variant,
                      const char* value_str)
{
    int32_t value = 0;

    /* check if there is a source string to be parsed */
    if (value_str)
    {
#ifdef _MSC_VER
        /* scan the source string for a numerical value */
        sscanf_s(value_str, "%d", &variant->value.vint32);
#else
        /* scan the source string for a numerical value */
        sscanf(value_str, "%d", &variant->value.vint32);
#endif /* _MSC_VER */
    }

    return variant_init_int32(variant, value);
} /* end of : Variant*
              variant_init_int32_ex(Variant* variant,
                                    const char* value_str) */

Variant*
variant_init_float32(Variant* variant,
                     const float value)
{
    if (variant)
    {
        /* initialize a float32 variant */
        memset(variant, 0, sizeof(Variant));
        variant->type = VFLOAT32;
        variant->value.vfloat32 = value;
    }

    return variant;
} /* end of : Variant*
              variant_init_float32(Variant* variant,
                                   const float value) */

Variant*
variant_init_float32_ex(Variant* variant,
                        const char* value_str)
{
    float value = 0;

    /* check if there is a source string to be parsed */
    if (value_str)
    {
#ifdef _MSC_VER
        /* scan the source string for a numerical value */
        sscanf_s(value_str, "%f", &variant->value.vfloat32);
#else
        /* scan the source string for a numerical value */
        sscanf(value_str, "%f", &variant->value.vfloat32);
#endif /* _MSC_VER */
    }

    return variant_init_float32(variant, value);
} /* end of : Variant*
              variant_init_float32_ex(Variant* variant,
                                      const char* value_str) */

Variant*
variant_init_text(Variant* variant,
                  const char* value)
{
    if (variant)
    {
        /* initialize a text variant */
        memset(variant, 0, sizeof(Variant));
        variant->type = VTEXT;
        variant->value.vtext = NULL;

        /* check if there is a source text to be stored */
        if (value)
        {
            size_t length = strlen(value);

            if ((variant->value.vtext = mem_malloc(length + 1)) != NULL)
            {
#ifdef _MSC_VER
                /* copy the source text to the allocated memory */
                strcpy_s(variant->value.vtext, length + 1, value);
#else
                /* copy the source text to the allocated memory */
                strcpy(variant->value.vtext, value);
#endif /* _MSC_VER */
            }
            else
            {
                // TODO : report no memory failure
            }
        }
        else
        {
            variant->value.vtext = NULL;
        }
    }

    return variant;
} /* end of : Variant*
              variant_init_text(Variant* variant,
                                const char* value) */

Variant*
variant_init_pointer(Variant* variant,
                     void* value)
{
    if (variant)
    {
        /* initialize a pointer variant */
        memset(variant, 0, sizeof(Variant));
        variant->type = VPOINTER;
        variant->value.vpointer = value;
    }

    return variant;
} /* end of : Variant*
              variant_init_pointer(Variant* variant,
                                   void* value) */

Variant*
variant_init_function(Variant* variant,
                      const void* value)
{
    if (variant)
    {
        /* initialize a function variant */
        memset(variant, 0, sizeof(Variant));
        variant->type = VFUNCTION;
        variant->value.vfunction = value;
    }

    return variant;
} /* end of : Variant*
              variant_init_function(Variant* variant,
                                    const void* value) */

Variant*
variant_uninit(Variant* variant)
{
    if (variant)
    {
        /* check if the variant stores a text */
        if (   variant->type == VTEXT
            && variant->value.vtext)
        {
            /* free the allocated memory for the text */
            mem_free(variant->value.vtext);
        }

        /* clear the variant data */
        memset(variant, 0, sizeof(Variant));
    }

    return variant;
} /* end of : Variant*
              variant_uninit(Variant* variant) */

Variant*
variant_assign(Variant* variant,
               const Variant* value)
{
    if (value)
    {
        /* demux the source value variant type */
        switch (value->type)
        {
            case VBOOLEAN:
                /* assign a boolean value */
                return variant_assign_boolean(variant, value->value.vboolean);
            case VINT32:
                /* assign a int32 value */
                return variant_assign_int32(variant, value->value.vint32);
            case VFLOAT32:
                /* assign a float32 value */
                return variant_assign_float32(variant, value->value.vfloat32);
            case VTEXT:
                /* assign a text value */
                return variant_assign_text(variant, value->value.vtext);
            case VPOINTER:
                /* assign a pointer value */
                return variant_assign_pointer(variant, value->value.vpointer);
            case VFUNCTION:
                /* assign a function value */
                return variant_assign_function(variant, value->value.vfunction);
            default:
                if (variant)
                {
                    /* check if the variant stores a text */
                    if (   variant->type == VTEXT
                        && variant->value.vtext)
                    {
                        /* free the allocated memory for the text */
                        mem_free(variant->value.vtext);
                    }

                    /* copy the variant data */
                    memcpy(variant, value, sizeof(Variant));
                }
                break;
        }
    }

    /* dont assign a value ... */
    return variant;
} /* end of : Variant*
              variant_assign(Variant* variant,
                             const Variant* value) */

Variant*
variant_assign_boolean(Variant* variant,
                       const int8_t value)
{
    if (variant)
    {
        /* check if the variant stores a text */
        if (   variant->type == VTEXT
            && variant->value.vtext)
        {
            /* free the allocated memory for the text */
            mem_free(variant->value.vtext);
        }

        /* store the requested boolean value */
        variant->type = VBOOLEAN;
        variant->value.vboolean = value;
    }

    return variant;
} /* end of : Variant*
              variant_assign_boolean(Variant* variant,
                                     const int8_t value) */

Variant*
variant_assign_int32(Variant* variant,
                     const int32_t value)
{
    if (variant)
    {
        /* check if the variant stores a text */
        if (   variant->type == VTEXT
            && variant->value.vtext)
        {
            /* free the allocated memory for the text */
            mem_free(variant->value.vtext);
        }

        /* store the requested int32 value */
        variant->type = VINT32;
        variant->value.vint32 = value;
    }

    return variant;
} /* end of : Variant*
              variant_assign_int32(Variant* variant,
                                   const int32_t value) */

Variant*
variant_assign_float32(Variant* variant,
                       const float value)
{
    if (variant)
    {
        /* check if the variant stores a text */
        if (   variant->type == VTEXT
            && variant->value.vtext)
        {
            /* free the allocated memory for the text */
            mem_free(variant->value.vtext);
        }

        /* store the requested float32 value */
        variant->type = VFLOAT32;
        variant->value.vfloat32 = value;
    }

    return variant;
} /* end of : Variant*
              variant_assign_float32(Variant* variant,
                                     const float value) */

Variant*
variant_assign_text(Variant* variant,
                    const char* value)
{
    if (variant)
    {
        /* check if the variant stores a text */
        if (   variant->type == VTEXT
            && variant->value.vtext)
        {
            /* free the allocated memory for the text */
            mem_free(variant->value.vtext);
            variant->value.vtext = NULL;
        }

        /* check if there is a source text to be stored */
        variant->type = VTEXT;
        if (value)
        {
            size_t length = strlen(value);

            if ((variant->value.vtext = mem_malloc(length + 1)) != NULL)
            {
#ifdef _MSC_VER
                /* copy the source text to the allocated memory */
                strcpy_s(variant->value.vtext, length + 1, value);
#else
                /* copy the source text to the allocated memory */
                strcpy(variant->value.vtext, value);
#endif /* _MSC_VER */
            }
            else
            {
                // TODO : report no memory failure
            }
        }
        else
        {
            variant->value.vtext = NULL;
        }
    }

    return variant;
} /* end of : Variant*
              variant_assign_text(Variant* variant,
                                  const char* value) */

Variant*
variant_assign_pointer(Variant* variant,
                       void* value)
{
    if (variant)
    {
        /* check if the variant stores a text */
        if (   variant->type == VTEXT
            && variant->value.vtext)
        {
            /* free the allocated memory for the text */
            mem_free(variant->value.vtext);
        }

        /* store the requested function value */
        variant->type = VPOINTER;
        variant->value.vpointer = value;
    }

    return variant;
} /* end of : Variant*
              variant_assign_pointer(Variant* variant,
                                     void* value) */

Variant*
variant_assign_function(Variant* variant,
                        const void* value)
{
    if (variant)
    {
        /* check if the variant stores a text */
        if (   variant->type == VTEXT
            && variant->value.vtext)
        {
            /* free the allocated memory for the text */
            mem_free(variant->value.vtext);
        }

        /* store the requested function value */
        variant->type = VFUNCTION;
        variant->value.vfunction = value;
    }

    return variant;
} /* end of : Variant*
              variant_assign_function(Variant* variant,
                                      const void* value) */

Variant*
variant_cast(Variant* variant,
              const VType type)
{
    /* check if the variant need to be promoted or demoted */
    if (   variant
        && type != variant->type
        && variant->type != VPOINTER
        && variant->type != VFUNCTION)
    {
        if (type < variant->type)
            return variant_demote(variant, type);
        else
            return variant_promote(variant, type);
    }

    return variant;
} /* end of : Variant*
              variant_cast(Variant* variant,
                            const VType type) */

Variant*
variant_promote(Variant* variant,
                const VType type)
{
    if (variant)
    {
        /* demux the requested promotion variant type */
        switch (type)
        {
            case VINT32:
                /* demux the current variant type */
                switch (variant->type)
                {
                    case VBOOLEAN:
                        /* cast the current variant value to a int32 value */
                        variant->value.vint32 = (int32_t) variant->value.vboolean;
                        variant->type = type;
                        break;
                    default:
                        break;
                }
                break;
            case VFLOAT32:
                /* demux the current variant type */
                switch (variant->type)
                {
                    case VBOOLEAN:
                        /* cast the current variant value to a float32 value */
                        variant->value.vfloat32 = (float) variant->value.vboolean;
                        variant->type = type;
                        break;
                    case VINT32:
                        /* cast the current variant value to a float32 value */
                        variant->value.vfloat32 = (float) variant->value.vint32;
                        variant->type = type;
                        break;
                    default:
                        break;
                }
                break;
            case VTEXT:
                /* demux the current variant type */
                switch (variant->type)
                {
                    case VBOOLEAN:
                    {
                        /* allocate memory to store the string representation of the boolean value */
                        char* buffer = NULL;
                        if ((buffer = mem_malloc(2)) != NULL)
                        {
                            /* copy the boolean value to the string */
                            buffer[0] = variant->value.vboolean;
                            buffer[1] = 0;

                            /* store the created string */
                            variant->value.vtext = buffer;
                            variant->type = type;
                        }
                        else
                        {
                            // TODO : report no memory failure
                        }
                        break;
                    }
                    case VINT32:
                    {
                        /* allocate memory to store the string representation of the int32 value */
                        char* buffer = NULL;
                        if ((buffer = mem_malloc(16)) != NULL)
                        {
#ifdef _MSC_VER
                            /* write the int32 value to the allocated string */
                            sprintf_s(buffer, 16, "%d", variant->value.vint32);
#else
                            /* write the int32 value to the allocated string */
                            sprintf(buffer, "%d", variant->value.vint32);
#endif

                            /* store the created string */
                            variant->value.vtext = buffer;
                            variant->type = type;
                        }
                        else
                        {
                            // TODO : report no memory failure
                        }
                        break;
                    }
                    case VFLOAT32:
                    {
                        /* allocate memory to store the string representation of the float32 value */
                        char* buffer = NULL;
                        if ((buffer = mem_malloc(16)) != NULL)
                        {
#ifdef _MSC_VER
                            /* write the float32 value to the allocated string */
                            sprintf_s(buffer, 16, "%f", variant->value.vfloat32);
#else
                            /* write the float32 value to the allocated string */
                            sprintf(buffer, "%f", variant->value.vfloat32);
#endif

                            /* store the created string */
                            variant->value.vtext = buffer;
                            variant->type = type;
                        }
                        else
                        {
                            // TODO : report no memory failure
                        }
                        break;
                    }
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }

    return variant;
} /* end of : Variant*
              variant_promote(Variant* variant,
                              const VType type) */

Variant*
variant_demote(Variant* variant,
               const VType type)
{
    if (variant)
    {
        /* demux the requested promotion variant type */
        switch (type)
        {
            case VBOOLEAN:
                /* demux the current variant type */
                switch (variant->type)
                {
                    case VINT32:
                        /* cast the current variant value to a boolean value */
                        variant->value.vboolean = variant->value.vint32 != 0;
                        variant->type = type;
                        break;
                    case VFLOAT32:
                        /* cast the current variant value to a boolean value */
                        variant->value.vboolean = variant->value.vfloat32 != 0.0f;
                        variant->type = type;
                        break;
                    case VTEXT:
                    {
                        int8_t aux = 1;

                        /* check if any text is currently stored */
                        if (   variant->value.vtext)
                        {
                            /* check if the stored text contains the zero numerical value or
                               the language textual representation of the false reserved word */
                            if (   strcmp(variant->value.vtext, "0") == 0
                                && strcmp(variant->value.vtext, "falso") == 0)
                            {
                                aux = 0;
                            }

                            /* release the allocated memory of the variant text */
                            mem_free(variant->value.vtext);

                            /* store the boolean value into the variant */
                            variant->value.vboolean = aux;
                            variant->type = type;
                        }
                        else
                        {
                            /* store the false value into the variant */
                            variant->value.vboolean = 0;
                            variant->type = type;
                        }
                        break;
                    }
                    default:
                        break;
                }
                break;
            case VINT32:
                /* demux the current variant type */
                switch (variant->type)
                {
                    case VFLOAT32:
                        /* cast the current variant value to a int32 value */
                        variant->value.vint32 = (int32_t) variant->value.vfloat32;
                        variant->type = type;
                        break;
                    case VTEXT:
                    {
                        int32_t aux = 0;

                        /* check if any text is currently stored */
                        if (variant->value.vtext)
                        {
#ifdef _MSC_VER
                            /* read a int32 value from the variant stored text */
                            sscanf_s(variant->value.vtext, "%d", &aux);
#else
                            /* read a int32 value from the variant stored text */
                            sscanf(variant->value.vtext, "%d", &aux);
#endif
                            /* release the allocated memory of the variant text */
                            mem_free(variant->value.vtext);

                            /* store the int32 value into the variant */
                            variant->value.vint32 = aux;
                            variant->type = type;
                        }
                        else
                        {
                            /* store the int32 zero value into the variant */
                            variant->value.vint32 = 0;
                            variant->type = type;
                        }
                        break;
                    }
                    default:
                        break;
                }
                break;
            case VFLOAT32:
                /* demux the current variant type */
                switch (variant->type)
                {
                    case VTEXT:
                    {
                        float aux = 0.0f;

                        /* check if any text is currently stored */
                        if (variant->value.vtext)
                        {
#ifdef _MSC_VER
                            /* read a float32 value from the variant stored text */
                            sscanf_s(variant->value.vtext, "%f", &aux);
#else
                            /* read a float32 value from the variant stored text */
                            sscanf(variant->value.vtext, "%f", &aux);
#endif
                            /* release the allocated memory of the variant text */
                            mem_free(variant->value.vtext);

                            /* store the float32 value into the variant */
                            variant->value.vfloat32 = aux;
                            variant->type = type;
                        }
                        else
                        {
                            /* store the float32 zero value into the variant */
                            variant->value.vfloat32 = 0.0f;
                            variant->type = type;
                        }
                        break;
                    }
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }

    return variant;
} /* end of : Variant*
              variant_demote(Variant* variant,
                             const VType type) */

Variant*
variant_negate(Variant* result,
               const Variant* op)
{
    if (   result
        && op)
    {
        /* demux the variant value type */
        switch (op->type)
        {
            case VBOOLEAN:
                /* negate the boolean value */
                variant_assign_boolean(result, !op->value.vboolean);
                break;
            case VINT32:
                /* negate the int32 value */
                variant_assign_int32(result, !op->value.vint32);
                break;
            case VFLOAT32:
                /* negate the float32 value */
                variant_assign_float32(result, !op->value.vfloat32);
                break;
            case VTEXT:
            case VPOINTER:
            case VFUNCTION:
                variant_assign(result, op);
                break;
            default:
                break;
        }
    }

    return result;
} /* end of : Variant*
              variant_negate(Variant* result,
                             const Variant* op) */

Variant*
variant_negative(Variant* result,
                 const Variant* op)
{
    if (   result
        && op)
    {
        /* demux the variant value type */
        switch (op->type)
        {
            case VBOOLEAN:
                /* negate the boolean value */
                variant_assign_boolean(result, !op->value.vboolean);
                break;
            case VINT32:
                /* invert the signal of the int32 value */
                variant_assign_int32(result, - op->value.vint32);
                break;
            case VFLOAT32:
                /* invert the signal of the float32 value */
                variant_assign_float32(result, - op->value.vfloat32);
                break;
            case VTEXT:
            case VPOINTER:
            case VFUNCTION:
                variant_assign(result, op);
                break;
            default:
                break;
        }
    }

    return result;
} /* end of : Variant*
              variant_negative(Variant* result,
                               const Variant* op) */

Variant*
variant_add(Variant* result,
            const Variant* op1,
            const Variant* op2)
{
    if (   result
        && op1
        && op2)
    {
        VType supra = op1->type > op2->type ? op1->type : op2->type;
        Variant _op1, _op2;

        variant_init(&_op1, op1);
        variant_init(&_op2, op2);

        variant_cast(&_op1, supra);
        variant_cast(&_op2, supra);

        /* demux the variant value type */
        switch (_op1.type)
        {
            case VBOOLEAN:
                variant_assign_boolean(result, _op1.value.vboolean + _op2.value.vboolean != 0);
                break;
            case VINT32:
                variant_assign_int32(result, _op1.value.vint32 + _op2.value.vint32);
                break;
            case VFLOAT32:
                variant_assign_float32(result, _op1.value.vfloat32 + _op2.value.vfloat32);
                break;
            case VTEXT:
            {
                size_t _op1_length = strlen(_op1.value.vtext);
                size_t _op2_length = strlen(_op2.value.vtext);
                char* buffer = NULL;
                
                if ((buffer = mem_malloc(_op1_length + _op2_length + 1)) != NULL)
                {
#ifdef _MSC_VER
                    strcpy_s(buffer, _op1_length + 1, _op1.value.vtext);
                    strcpy_s(&buffer[_op1_length], _op2_length + 1, _op2.value.vtext);
#else
                    strcpy(buffer, _op1.value.vtext);
                    strcpy(&buffer[_op1_length], _op2.value.vtext);
#endif /* _MSC_VER */

                    variant_assign_text(result, buffer);

                    mem_free(buffer);
                }
                else
                {
                    // TODO : report no memory failure
                }
                break;
            }
            case VPOINTER:
            case VFUNCTION:
                variant_assign(result, op1);
                break;
            default:
                break;
        }

        variant_uninit(&_op1);
        variant_uninit(&_op2);
    }

    return result;
} /* end of : Variant*
              variant_add(Variant* result,
                          const Variant* op1,
                          const Variant* op2) */

Variant*
variant_subtract(Variant* result,
                 const Variant* op1,
                 const Variant* op2)
{
    if (   result
        && op1
        && op2)
    {
        VType supra = op1->type > op2->type ? op1->type : op2->type;
        Variant _op1, _op2;

        variant_init(&_op1, op1);
        variant_init(&_op2, op2);

        variant_cast(&_op1, supra);
        variant_cast(&_op2, supra);

        /* demux the variant value type */
        switch (_op1.type)
        {
            case VBOOLEAN:
                variant_assign_boolean(result, _op1.value.vboolean - _op2.value.vboolean != 0);
                break;
            case VINT32:
                variant_assign_int32(result, _op1.value.vint32 - _op2.value.vint32);
                break;
            case VFLOAT32:
                variant_assign_float32(result, _op1.value.vfloat32 - _op2.value.vfloat32);
                break;
            case VTEXT:
            case VPOINTER:
            case VFUNCTION:
                variant_assign(result, op1);
                break;
            default:
                break;
        }

        variant_uninit(&_op1);
        variant_uninit(&_op2);
    }

    return result;
} /* end of : Variant*
              variant_subtract(Variant* result,
                               const Variant* op1,
                               const Variant* op2) */

Variant*
variant_multiply(Variant* result,
                 const Variant* op1,
                 const Variant* op2)
{
    if (   result
        && op1
        && op2)
    {
        VType supra = op1->type > op2->type ? op1->type : op2->type;
        Variant _op1, _op2;

        variant_init(&_op1, op1);
        variant_init(&_op2, op2);

        variant_cast(&_op1, supra);
        variant_cast(&_op2, supra);

        /* demux the variant value type */
        switch (_op1.type)
        {
            case VBOOLEAN:
                variant_assign_boolean(result, _op1.value.vboolean * _op2.value.vboolean != 0);
                break;
            case VINT32:
                variant_assign_int32(result, _op1.value.vint32 * _op2.value.vint32);
                break;
            case VFLOAT32:
                variant_assign_float32(result, _op1.value.vfloat32 * _op2.value.vfloat32);
                break;
            case VTEXT:
            case VPOINTER:
            case VFUNCTION:
                variant_assign(result, op1);
                break;
            default:
                break;
        }

        variant_uninit(&_op1);
        variant_uninit(&_op2);
    }

    return result;
} /* end of : Variant*
              variant_multiply(Variant* result,
                               const Variant* op1,
                               const Variant* op2) */

Variant*
variant_divide(Variant* result,
               const Variant* op1,
               const Variant* op2)
{
    if (   result
        && op1
        && op2)
    {
        VType supra = op1->type > op2->type ? op1->type : op2->type;
        Variant _op1, _op2;

        variant_init(&_op1, op1);
        variant_init(&_op2, op2);

        variant_cast(&_op1, supra);
        variant_cast(&_op2, supra);

        /* demux the variant value type */
        switch (_op1.type)
        {
            case VBOOLEAN:
                if (_op2.value.vboolean != 0)
                {
                    variant_assign_boolean(result, _op1.value.vboolean / _op2.value.vboolean != 0);
                }
                else
                {
                    // TODO : report divide by zero failure
                }
                break;
            case VINT32:
                if (_op2.value.vint32 != 0)
                {
                    variant_assign_int32(result, _op1.value.vint32 / _op2.value.vint32);
                }
                else
                {
                    // TODO : report divide by zero failure
                }
                break;
            case VFLOAT32:
                if (_op2.value.vfloat32 != 0)
                {
                    variant_assign_float32(result, _op1.value.vfloat32 / _op2.value.vfloat32);
                }
                else
                {
                    // TODO : report divide by zero failure
                }
                break;
            case VTEXT:
            case VPOINTER:
            case VFUNCTION:
                variant_assign(result, op1);
                break;
            default:
                break;
        }

        variant_uninit(&_op1);
        variant_uninit(&_op2);
    }

    return result;
} /* end of : Variant*
              variant_divide(Variant* result,
                             const Variant* op1,
                             const Variant* op2) */


Variant*
variant_remainder(Variant* result,
                  const Variant* op1,
                  const Variant* op2)
{
    if (   result
        && op1
        && op2)
    {
        VType supra = op1->type > op2->type ? op1->type : op2->type;
        Variant _op1, _op2;

        variant_init(&_op1, op1);
        variant_init(&_op2, op2);

        variant_cast(&_op1, supra);
        variant_cast(&_op2, supra);

        /* demux the variant value type */
        switch (_op1.type)
        {
            case VBOOLEAN:
                if (_op2.value.vboolean != 0)
                {
                    variant_assign_boolean(result, _op1.value.vboolean % _op2.value.vboolean != 0);
                }
                else
                {
                    // TODO : report divide by zero failure
                }
                break;
            case VINT32:
                if (_op2.value.vint32 != 0)
                {
                    variant_assign_int32(result, _op1.value.vint32 % _op2.value.vint32);
                }
                else
                {
                    // TODO : report divide by zero failure
                }
                break;
            case VFLOAT32:
                if (_op2.value.vfloat32 != 0)
                {
                    variant_assign_float32(result, (float) ((size_t) _op1.value.vfloat32 % (size_t) _op2.value.vfloat32));
                }
                else
                {
                    // TODO : report divide by zero failure
                }
                break;
            case VTEXT:
            case VPOINTER:
            case VFUNCTION:
                variant_assign(result, op1);
                break;
            default:
                break;
        }

        variant_uninit(&_op1);
        variant_uninit(&_op2);
    }

    return result;
} /* end of : Variant*
              variant_remainder(Variant* result,
                                const Variant* op1,
                                const Variant* op2) */

Variant*
variant_equal(Variant* result,
              const Variant* op1,
              const Variant* op2)
{
    if (   result
        && op1
        && op2)
    {
        VType supra = op1->type > op2->type ? op1->type : op2->type;
        Variant _op1, _op2;

        variant_init(&_op1, op1);
        variant_init(&_op2, op2);

        variant_cast(&_op1, supra);
        variant_cast(&_op2, supra);

        /* demux the variant value type */
        switch (_op1.type)
        {
            case VBOOLEAN:
                variant_assign_boolean(result, _op1.value.vboolean == _op2.value.vboolean);
                break;
            case VINT32:
                variant_assign_boolean(result, _op1.value.vint32 == _op2.value.vint32);
                break;
            case VFLOAT32:
                variant_assign_boolean(result, _op1.value.vfloat32 == _op2.value.vfloat32);
                break;
            case VTEXT:
                variant_assign_boolean(result, strcmp(_op1.value.vtext, _op2.value.vtext) == 0);
                break;
            case VPOINTER:
                variant_assign_boolean(result, _op1.value.vpointer == _op2.value.vpointer);
                break;
            case VFUNCTION:
                variant_assign_boolean(result, _op1.value.vfunction == _op2.value.vfunction);
                break;
            default:
                break;
        }

        variant_uninit(&_op1);
        variant_uninit(&_op2);
    }

    return result;
} /* end of : Variant*
              variant_equal(Variant* result,
                            const Variant* op1,
                            const Variant* op2) */

Variant*
variant_inequal(Variant* result,
                const Variant* op1,
                const Variant* op2)
{
    if (   result
        && op1
        && op2)
    {
        VType supra = op1->type > op2->type ? op1->type : op2->type;
        Variant _op1, _op2;

        variant_init(&_op1, op1);
        variant_init(&_op2, op2);

        variant_cast(&_op1, supra);
        variant_cast(&_op2, supra);

        /* demux the variant value type */
        switch (_op1.type)
        {
            case VBOOLEAN:
                variant_assign_boolean(result, _op1.value.vboolean != _op2.value.vboolean);
                break;
            case VINT32:
                variant_assign_boolean(result, _op1.value.vint32 != _op2.value.vint32);
                break;
            case VFLOAT32:
                variant_assign_boolean(result, _op1.value.vfloat32 != _op2.value.vfloat32);
                break;
            case VTEXT:
                variant_assign_boolean(result, strcmp(_op1.value.vtext, _op2.value.vtext) != 0);
                break;
            case VPOINTER:
                variant_assign_boolean(result, _op1.value.vpointer != _op2.value.vpointer);
                break;
            case VFUNCTION:
                variant_assign_boolean(result, _op1.value.vfunction != _op2.value.vfunction);
                break;
            default:
                break;
        }

        variant_uninit(&_op1);
        variant_uninit(&_op2);
    }

    return result;
} /* end of : Variant*
              variant_inequal(Variant* result,
                              const Variant* op1,
                              const Variant* op2) */

Variant*
variant_greater(Variant* result,
                const Variant* op1,
                const Variant* op2)
{
    if (   result
        && op1
        && op2)
    {
        VType supra = op1->type > op2->type ? op1->type : op2->type;
        Variant _op1, _op2;

        variant_init(&_op1, op1);
        variant_init(&_op2, op2);

        variant_cast(&_op1, supra);
        variant_cast(&_op2, supra);

        /* demux the variant value type */
        switch (_op1.type)
        {
            case VBOOLEAN:
                variant_assign_boolean(result, _op1.value.vboolean > _op2.value.vboolean);
                break;
            case VINT32:
                variant_assign_boolean(result, _op1.value.vint32 > _op2.value.vint32);
                break;
            case VFLOAT32:
                variant_assign_boolean(result, _op1.value.vfloat32 > _op2.value.vfloat32);
                break;
            case VTEXT:
                variant_assign_boolean(result, strcmp(_op1.value.vtext, _op2.value.vtext) > 0);
                break;
            case VPOINTER:
                variant_assign_boolean(result, _op1.value.vpointer > _op2.value.vpointer);
                break;
            case VFUNCTION:
                variant_assign_boolean(result, _op1.value.vfunction > _op2.value.vfunction);
                break;
            default:
                break;
        }

        variant_uninit(&_op1);
        variant_uninit(&_op2);
    }

    return result;
} /* end of : Variant*
              variant_greater(Variant* result,
                              const Variant* op1,
                              const Variant* op2) */

Variant*
variant_greater_or_equal(Variant* result,
                         const Variant* op1,
                         const Variant* op2)
{
    if (   result
        && op1
        && op2)
    {
        VType supra = op1->type > op2->type ? op1->type : op2->type;
        Variant _op1, _op2;

        variant_init(&_op1, op1);
        variant_init(&_op2, op2);

        variant_cast(&_op1, supra);
        variant_cast(&_op2, supra);

        /* demux the variant value type */
        switch (_op1.type)
        {
            case VBOOLEAN:
                variant_assign_boolean(result, _op1.value.vboolean >= _op2.value.vboolean);
                break;
            case VINT32:
                variant_assign_boolean(result, _op1.value.vint32 >= _op2.value.vint32);
                break;
            case VFLOAT32:
                variant_assign_boolean(result, _op1.value.vfloat32 >= _op2.value.vfloat32);
                break;
            case VTEXT:
                variant_assign_boolean(result, strcmp(_op1.value.vtext, _op2.value.vtext) >= 0);
                break;
            case VPOINTER:
                variant_assign_boolean(result, _op1.value.vpointer >= _op2.value.vpointer);
                break;
            case VFUNCTION:
                variant_assign_boolean(result, _op1.value.vfunction >= _op2.value.vfunction);
                break;
            default:
                break;
        }

        variant_uninit(&_op1);
        variant_uninit(&_op2);
    }

    return result;
} /* end of : Variant*
              variant_greater_or_equal(Variant* result,
                                       const Variant* op1,
                                       const Variant* op2) */

Variant*
variant_lesser(Variant* result,
               const Variant* op1,
               const Variant* op2)
{
    if (   result
        && op1
        && op2)
    {
        VType supra = op1->type > op2->type ? op1->type : op2->type;
        Variant _op1, _op2;

        variant_init(&_op1, op1);
        variant_init(&_op2, op2);

        variant_cast(&_op1, supra);
        variant_cast(&_op2, supra);

        /* demux the variant value type */
        switch (_op1.type)
        {
            case VBOOLEAN:
                variant_assign_boolean(result, _op1.value.vboolean < _op2.value.vboolean);
                break;
            case VINT32:
                variant_assign_boolean(result, _op1.value.vint32 < _op2.value.vint32);
                break;
            case VFLOAT32:
                variant_assign_boolean(result, _op1.value.vfloat32 < _op2.value.vfloat32);
                break;
            case VTEXT:
                variant_assign_boolean(result, strcmp(_op1.value.vtext, _op2.value.vtext) < 0);
                break;
            case VPOINTER:
                variant_assign_boolean(result, _op1.value.vpointer < _op2.value.vpointer);
                break;
            case VFUNCTION:
                variant_assign_boolean(result, _op1.value.vfunction < _op2.value.vfunction);
                break;
            default:
                break;
        }

        variant_uninit(&_op1);
        variant_uninit(&_op2);
    }

    return result;
} /* end of : Variant*
              variant_lesser(Variant* result,
                             const Variant* op1,
                             const Variant* op2) */

Variant*
variant_lesser_or_equal(Variant* result,
                        const Variant* op1,
                        const Variant* op2)
{
    if (   result
        && op1
        && op2)
    {
        VType supra = op1->type > op2->type ? op1->type : op2->type;
        Variant _op1, _op2;

        variant_init(&_op1, op1);
        variant_init(&_op2, op2);

        variant_cast(&_op1, supra);
        variant_cast(&_op2, supra);

        /* demux the variant value type */
        switch (_op1.type)
        {
            case VBOOLEAN:
                variant_assign_boolean(result, _op1.value.vboolean <= _op2.value.vboolean);
                break;
            case VINT32:
                variant_assign_boolean(result, _op1.value.vint32 <= _op2.value.vint32);
                break;
            case VFLOAT32:
                variant_assign_boolean(result, _op1.value.vfloat32 <= _op2.value.vfloat32);
                break;
            case VTEXT:
                variant_assign_boolean(result, strcmp(_op1.value.vtext, _op2.value.vtext) <= 0);
                break;
            case VPOINTER:
                variant_assign_boolean(result, _op1.value.vpointer <= _op2.value.vpointer);
                break;
            case VFUNCTION:
                variant_assign_boolean(result, _op1.value.vfunction <= _op2.value.vfunction);
                break;
            default:
                break;
        }

        variant_uninit(&_op1);
        variant_uninit(&_op2);
    }

    return result;
} /* end of : Variant*
              variant_lesser_or_equal(Variant* result,
                                      const Variant* op1,
                                      const Variant* op2) */

Variant*
variant_and(Variant* result,
            const Variant* op1,
            const Variant* op2)
{
    if (   result
        && op1
        && op2)
    {
        VType supra = op1->type > op2->type ? op1->type : op2->type;
        Variant _op1, _op2;

        variant_init(&_op1, op1);
        variant_init(&_op2, op2);

        variant_cast(&_op1, supra);
        variant_cast(&_op2, supra);

        /* demux the variant value type */
        switch (_op1.type)
        {
            case VBOOLEAN:
                variant_assign_boolean(result, _op1.value.vboolean && _op2.value.vboolean);
                break;
            case VINT32:
                variant_assign_boolean(result, _op1.value.vint32 && _op2.value.vint32);
                break;
            case VFLOAT32:
                variant_assign_boolean(result, _op1.value.vfloat32 && _op2.value.vfloat32);
                break;
            case VTEXT:
                variant_assign_boolean(result, strlen(_op1.value.vtext) && strlen(_op2.value.vtext));
                break;
            case VPOINTER:
                variant_assign_boolean(result, _op1.value.vpointer && _op2.value.vpointer);
                break;
            case VFUNCTION:
                variant_assign_boolean(result, _op1.value.vfunction && _op2.value.vfunction);
                break;
            default:
                break;
        }

        variant_uninit(&_op1);
        variant_uninit(&_op2);
    }

    return result;
} /* end of : Variant*
              variant_and(Variant* result,
                          const Variant* op1,
                          const Variant* op2) */

Variant*
variant_or(Variant* result,
           const Variant* op1,
           const Variant* op2)
{
    if (   result
        && op1
        && op2)
    {
        VType supra = op1->type > op2->type ? op1->type : op2->type;
        Variant _op1, _op2;

        variant_init(&_op1, op1);
        variant_init(&_op2, op2);

        variant_cast(&_op1, supra);
        variant_cast(&_op2, supra);

        /* demux the variant value type */
        switch (_op1.type)
        {
            case VBOOLEAN:
                variant_assign_boolean(result, _op1.value.vboolean || _op2.value.vboolean);
                break;
            case VINT32:
                variant_assign_boolean(result, _op1.value.vint32 || _op2.value.vint32);
                break;
            case VFLOAT32:
                variant_assign_boolean(result, _op1.value.vfloat32 || _op2.value.vfloat32);
                break;
            case VTEXT:
                variant_assign_boolean(result, strlen(_op1.value.vtext) || strlen(_op2.value.vtext));
                break;
            case VPOINTER:
                variant_assign_boolean(result, _op1.value.vpointer || _op2.value.vpointer);
                break;
            case VFUNCTION:
                variant_assign_boolean(result, _op1.value.vfunction || _op2.value.vfunction);
                break;
            default:
                break;
        }

        variant_uninit(&_op1);
        variant_uninit(&_op2);
    }

    return result;
} /* end of : Variant*
              variant_or(Variant* result,
                         const Variant* op1,
                         const Variant* op2) */

Variant*
variant_xor(Variant* result,
            const Variant* op1,
            const Variant* op2)
{
    if (   result
        && op1
        && op2)
    {
        VType supra = op1->type > op2->type ? op1->type : op2->type;
        Variant _op1, _op2;

        variant_init(&_op1, op1);
        variant_init(&_op2, op2);

        variant_cast(&_op1, supra);
        variant_cast(&_op2, supra);

        /* demux the variant value type */
        switch (_op1.type)
        {
            case VBOOLEAN:
                variant_assign_boolean(result,    ( _op1.value.vboolean &&  _op2.value.vboolean)
                                               || (!_op1.value.vboolean && !_op2.value.vboolean));
                break;
            case VINT32:
                variant_assign_boolean(result,    ( _op1.value.vint32 &&  _op2.value.vint32)
                                               || (!_op1.value.vint32 && !_op2.value.vint32));
                break;
            case VFLOAT32:
                variant_assign_boolean(result,    ( _op1.value.vfloat32 &&  _op2.value.vfloat32)
                                               || (!_op1.value.vfloat32 && !_op2.value.vfloat32));
                break;
            case VTEXT:
            {
                size_t _op1_length = strlen(_op1.value.vtext);
                size_t _op2_length = strlen(_op2.value.vtext);

                variant_assign_boolean(result,    ( _op1_length &&  _op2_length)
                                               || (!_op1_length && !_op2_length));
                break;
            }
            case VPOINTER:
                variant_assign_boolean(result,    ( _op1.value.vpointer &&  _op2.value.vpointer)
                                               || (!_op1.value.vpointer && !_op2.value.vpointer));
                break;
            case VFUNCTION:
                variant_assign_boolean(result,    ( _op1.value.vfunction &&  _op2.value.vfunction)
                                               || (!_op1.value.vfunction && !_op2.value.vfunction));
                break;
            default:
                break;
        }

        variant_uninit(&_op1);
        variant_uninit(&_op2);
    }

    return result;
} /* end of : Variant*
              variant_xor(Variant* result,
                          const Variant* op1,
                          const Variant* op2) */

void
variant_output(const Variant* variant)
{
    if (variant)
    {
        /* demux the variant value type */
        switch (variant->type)
        {
            case VUNKNOWN:
                printf("unknown");
                break;
            case VBOOLEAN:
                printf("boolean(%d)", variant->value.vboolean);
                break;
            case VINT32:
                printf("int32(%d)", variant->value.vint32);
                break;
            case VFLOAT32:
                printf("float32(%f)", variant->value.vfloat32);
                break;
            case VTEXT:
                printf("text(%s)", variant->value.vtext);
                break;
            case VPOINTER:
                printf("pointer(%p)", variant->value.vpointer);
                break;
            case VFUNCTION:
                printf("function(%p)", variant->value.vfunction);
                break;
        }
    }
} /* end of : void
              variant_output(const Variant* variant) */
