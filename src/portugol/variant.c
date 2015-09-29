#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <internal/portugol/variant.h>

Variant
variant_init_boolean(int value)
{
    Variant var;
    memset(&var, 0, sizeof(Variant));

    var.type = VBOOLEAN;
    var.value.boolean = value != 0;

    return var;
}

Variant
variant_init_int32(int32_t value)
{
    Variant var;
    memset(&var, 0, sizeof(Variant));

    var.type = VINT32;
    var.value.int32 = value;

    return var;
}

Variant
variant_init_float32(float value)
{
    Variant var;
    memset(&var, 0, sizeof(Variant));

    var.type = VFLOAT32;
    var.value.float32 = value;

    return var;
}

Variant
variant_init_text(char* value)
{
    Variant var;
    memset(&var, 0, sizeof(Variant));

    var.type = VTEXT;
    if (value != NULL)
    {
        var.value.text = malloc(strlen(value) + 1);
        strcpy(var.value.text, value);
    }
    else
    {
        var.value.text = malloc(1);
        var.value.text[0] = '\0';
    }

    return var;
}

Variant
variant_init_function(void* value)
{
    Variant var;
    memset(&var, 0, sizeof(Variant));

    var.type = VFUNCTION;
    var.value.function = value;

    return var;
}

Variant
variant_copy(Variant var)
{
    Variant copy;
    memset(&copy, 0, sizeof(Variant));

    switch (var.type)
    {
        case VBOOLEAN:
            variant_set_boolean(&copy, var.value.boolean);          break;
        case VINT32:
            variant_set_int32(&copy, var.value.int32);              break;
        case VFLOAT32:
            variant_set_float32(&copy, var.value.float32);          break;
        case VTEXT:
            variant_set_text(&copy, var.value.text);                break;
        case VFUNCTION:
            variant_set_function(&copy, var.value.function);        break;
        default:
            printf("unknown variant type\n");                       break;
    }

    return copy;
}

Variant*
variant_uninit(Variant* var)
{
    if (var == NULL)
        return NULL;

    if (var->type == VTEXT)
        free(var->value.text);

    memset(var, 0, sizeof(Variant));
    var->type = VINT32;

    return var;
}

Variant*
variant_set_boolean(Variant* var,
                    int value)
{
    if (var == NULL)
        return var;

    if (var->type == VTEXT)
    {
        free(var->value.text);
        var->value.text = NULL;
    }

    var->type = VBOOLEAN;
    var->value.boolean = value != 0;

    return var;
}

Variant*
variant_set_int32(Variant* var,
                  int32_t value)
{
    if (var == NULL)
        return var;

    if (var->type == VTEXT)
    {
        free(var->value.text);
        var->value.text = NULL;
    }

    var->type = VINT32;
    var->value.int32 = value;

    return var;
}

Variant*
variant_set_float32(Variant* var,
                    float value)
{
    if (var == NULL)
        return var;

    if (var->type == VTEXT)
    {
        free(var->value.text);
        var->value.text = NULL;
    }

    var->type = VFLOAT32;
    var->value.float32 = value;

    return var;
}

Variant*
variant_set_text(Variant* var,
                 char* value)
{
    if (var == NULL)
        return var;

    if (var->type == VTEXT)
    {
        free(var->value.text);
        var->value.text = NULL;
    }

    var->type = VTEXT;
    if (value != NULL)
    {
        var->value.text = malloc(strlen(value) + 1);
        strcpy(var->value.text, value);
    }
    else
    {
        var->value.text = malloc(1);
        var->value.text[0] = '\0';
    }

    return var;
}

Variant*
variant_set_function(Variant* var,
                     void* value)
{
    if (var == NULL)
        return var;

    if (var->type == VTEXT)
    {
        free(var->value.text);
        var->value.text = NULL;
    }

    var->type = VFUNCTION;
    var->value.function = value;

    return var;
}

Variant*
variant_set(Variant* var1,
            Variant var2)
{
    switch (var2.type)
    {
        case VBOOLEAN:
            return variant_set_boolean(var1, var2.value.boolean);
        case VINT32:
            return variant_set_int32(var1, var2.value.int32);
        case VFLOAT32:
            return variant_set_float32(var1, var2.value.float32);
        case VTEXT:
            return variant_set_text(var1, var2.value.text);
        case VFUNCTION:
            return variant_set_function(var1, var2.value.function);
        default:
            break;
    }

    return var1;
}

Variant*
variant_promote(Variant* var,
                VariantType type)
{
    if (var == NULL || type <= var->type)
        return var;

    switch (type)
    {
        case VINT32:
            var->type = type;
            var->value.int32 = (int32_t) var->value.boolean != 0;
            return var;
        case VFLOAT32:
            switch (var->type)
            {
                case VBOOLEAN:
                    var->type = type;
                    var->value.float32 = (float) var->value.boolean != 0;
                    return var;
                case VINT32:
                    var->type = type;
                    var->value.float32 = (float) var->value.int32;
                    return var;
                default:
                    break;
            }
            break;
        case VTEXT:
            switch (var->type)
            {
                case VBOOLEAN:
                {
                    int8_t value = var->value.boolean != 0;

                    var->type = type;
                    var->value.text = malloc(32);
                    snprintf(var->value.text, 32, "%d", value);
                    return var;
                }
                case VINT32:
                {
                    int32_t value = var->value.int32;

                    var->type = type;
                    var->value.text = malloc(32);
                    snprintf(var->value.text, 32, "%d", value);
                    return var;
                }
                case VFLOAT32:
                {
                    float value = var->value.float32;

                    var->type = type;
                    var->value.text = malloc(32);
                    snprintf(var->value.text, 32, "%f", value);
                    return var;
                }
                default:
                    break;
            }
            break;
        default:
            break;
    }

    return var;
}

Variant*
variant_demote(Variant* var,
               VariantType type)
{
    if (var == NULL || type >= var->type)
        return var;

    switch (type)
    {
        case VBOOLEAN:
            switch (var->type)
            {
                case VINT32:
                    var->type = type;
                    var->value.boolean = var->value.int32 != 0;
                    break;
                case VFLOAT32:
                    var->type = type;
                    var->value.boolean = var->value.float32 != 0;
                    break;
                case VTEXT:
                    var->type = type;
                    var->value.boolean = strlen(var->value.text) != 0;
                    break;
                default:
                    break;
            }
            break;
        case VINT32:
            switch (var->type)
            {
                case VFLOAT32:
                    var->type = type;
                    var->value.int32 = (int32_t) var->value.float32;
                    break;
                case VTEXT:
                    var->type = type;
                    var->value.int32 = 0;
                    sscanf(var->value.text, "%d", &var->value.int32);
                    free(var->value.text);
                    break;
                default:
                    break;
            }
            break;
        case VFLOAT32:
            var->type = type;
            var->value.float32 = 0;
            sscanf(var->value.text, "%f", &var->value.float32);
            free(var->value.text);
            break;
        default:
            break;
    }

    return var;
}

Variant*
variant_cast(Variant* var,
             VariantType type)
{
    if (var == NULL)
        return var;

    if (type > var->type)
        return variant_promote(var, type);
    if (type < var->type)
        return variant_demote(var, type);

    return var;
}

Variant
variant_op_add(Variant var1,
               Variant var2)
{
    Variant var;

    int supra = var1.type > var2.type ? var1.type : var2.type;
    switch (supra)
    {
        case VBOOLEAN:
            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = supra;
            var.value.boolean = var1.value.boolean + var2.value.boolean != 0;
            break;
        case VINT32:
            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = supra;
            var.value.int32 = var1.value.int32 + var2.value.int32;
            break;
        case VFLOAT32:
            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = supra;
            var.value.float32 = var1.value.float32 + var2.value.float32;
            break;
        case VTEXT:
        {
            int var1_free = var1.type != supra;
            int var2_free = var2.type != supra;

            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            int var1_length = strlen(var1.value.text);
            int var2_length = strlen(var2.value.text);

            var.type = supra;
            var.value.text = malloc(var1_length + var2_length + 1);
            strcpy(var.value.text, var1.value.text);
            strcpy(&var.value.text[var1_length], var2.value.text);

            if (var1_free)
                free(var1.value.text);
            if (var2_free)
                free(var2.value.text);

            break;
        }
        default:
            break;
    }

    return var;
}

Variant
variant_op_subtract(Variant var1,
                    Variant var2)
{
    Variant var;

    int supra = var1.type > var2.type ? var1.type : var2.type;
    switch (supra)
    {
        case VBOOLEAN:
            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = supra;
            var.value.boolean = var1.value.boolean - var2.value.boolean != 0;
            break;
        case VINT32:
            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = supra;
            var.value.int32 = var1.value.int32 - var2.value.int32;
            break;
        case VFLOAT32:
            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = supra;
            var.value.float32 = var1.value.float32 - var2.value.float32;
            break;
        case VTEXT:
            var = variant_copy(var1);
            break;
        default:
            break;
    }

    return var;
}

Variant
variant_op_multiply(Variant var1,
                    Variant var2)
{
    Variant var;

    int supra = var1.type > var2.type ? var1.type : var2.type;
    switch (supra)
    {
        case VBOOLEAN:
            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = supra;
            var.value.boolean = var1.value.boolean * var2.value.boolean != 0;
            break;
        case VINT32:
            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = supra;
            var.value.int32 = var1.value.int32 * var2.value.int32;
            break;
        case VFLOAT32:
            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = supra;
            var.value.float32 = var1.value.float32 * var2.value.float32;
            break;
        case VTEXT:
            var = variant_copy(var1);
            break;
        default:
            break;
    }

    return var;
}

Variant
variant_op_divide(Variant var1,
                  Variant var2)
{
    Variant var;

    int supra = var1.type > var2.type ? var1.type : var2.type;
    switch (supra)
    {
        case VBOOLEAN:
            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = supra;
            var.value.boolean = var1.value.boolean / var2.value.boolean != 0;
            break;
        case VINT32:
            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = supra;
            var.value.int32 = var1.value.int32 / var2.value.int32;
            break;
        case VFLOAT32:
            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = supra;
            var.value.float32 = var1.value.float32 / var2.value.float32;
            break;
        case VTEXT:
            var = variant_copy(var1);
            break;
        default:
            break;
    }

    return var;
}

Variant
variant_op_remainder(Variant var1,
                     Variant var2)
{
    Variant var;

    int supra = var1.type > var2.type ? var1.type : var2.type;
    switch (supra)
    {
        case VBOOLEAN:
            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = supra;
            var.value.boolean = var1.value.boolean % var2.value.boolean != 0;
            break;
        case VINT32:
            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = supra;
            var.value.int32 = var1.value.int32 % var2.value.int32;
            break;
        case VFLOAT32:
            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = supra;
            var.value.float32 = (float) ((int) var1.value.float32 % (int) var2.value.float32);
            break;
        case VTEXT:
            var = variant_copy(var1);
            break;
        default:
            break;
    }

    return var;
}

Variant
variant_op_equal(Variant var1,
                 Variant var2)
{
    Variant var;

    int supra = var1.type > var2.type ? var1.type : var2.type;
    switch (supra)
    {
        case VBOOLEAN:
            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = VBOOLEAN;
            var.value.boolean = var1.value.boolean == var2.value.boolean;
            break;
        case VINT32:
            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = VBOOLEAN;
            var.value.boolean = var1.value.int32 == var2.value.int32;
            break;
        case VFLOAT32:
            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = VBOOLEAN;
            var.value.boolean = var1.value.float32 == var2.value.float32;
            break;
        case VTEXT:
        {
            int var1_free = var1.type != supra;
            int var2_free = var2.type != supra;

            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = VBOOLEAN;
            var.value.boolean = strcmp(var1.value.text, var2.value.text) == 0;

            if (var1_free)
                free(var1.value.text);
            if (var2_free)
                free(var2.value.text);
            break;
        }
        default:
            break;
    }

    return var;
}

Variant
variant_op_inequal(Variant var1,
                   Variant var2)
{
    Variant var;

    int supra = var1.type > var2.type ? var1.type : var2.type;
    switch (supra)
    {
        case VBOOLEAN:
            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = VBOOLEAN;
            var.value.boolean = var1.value.boolean != var2.value.boolean;
            break;
        case VINT32:
            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = VBOOLEAN;
            var.value.boolean = var1.value.int32 != var2.value.int32;
            break;
        case VFLOAT32:
            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = VBOOLEAN;
            var.value.boolean = var1.value.float32 != var2.value.float32;
            break;
        case VTEXT:
        {
            int var1_free = var1.type != supra;
            int var2_free = var2.type != supra;

            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = VBOOLEAN;
            var.value.boolean = strcmp(var1.value.text, var2.value.text) != 0;

            if (var1_free)
                free(var1.value.text);
            if (var2_free)
                free(var2.value.text);
            break;
        }
        default:
            break;
    }

    return var;
}

Variant
variant_op_greater(Variant var1,
                   Variant var2)
{
    Variant var;

    int supra = var1.type > var2.type ? var1.type : var2.type;
    switch (supra)
    {
        case VBOOLEAN:
            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = VBOOLEAN;
            var.value.boolean = var1.value.boolean > var2.value.boolean;
            break;
        case VINT32:
            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = VBOOLEAN;
            var.value.boolean = var1.value.int32 > var2.value.int32;
            break;
        case VFLOAT32:
            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = VBOOLEAN;
            var.value.boolean = var1.value.float32 > var2.value.float32;
            break;
        case VTEXT:
        {
            int var1_free = var1.type != supra;
            int var2_free = var2.type != supra;

            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = VBOOLEAN;
            var.value.boolean = strcmp(var1.value.text, var2.value.text) > 0;

            if (var1_free)
                free(var1.value.text);
            if (var2_free)
                free(var2.value.text);
            break;
        }
        default:
            break;
    }

    return var;
}

Variant
variant_op_greater_or_equal(Variant var1,
                            Variant var2)
{
    Variant var;

    int supra = var1.type > var2.type ? var1.type : var2.type;
    switch (supra)
    {
        case VBOOLEAN:
            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = VBOOLEAN;
            var.value.boolean = var1.value.boolean >= var2.value.boolean;
            break;
        case VINT32:
            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = VBOOLEAN;
            var.value.boolean = var1.value.int32 >= var2.value.int32;
            break;
        case VFLOAT32:
            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = VBOOLEAN;
            var.value.boolean = var1.value.float32 >= var2.value.float32;
            break;
        case VTEXT:
        {
            int var1_free = var1.type != supra;
            int var2_free = var2.type != supra;

            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = VBOOLEAN;
            var.value.boolean = strcmp(var1.value.text, var2.value.text) >= 0;

            if (var1_free)
                free(var1.value.text);
            if (var2_free)
                free(var2.value.text);
            break;
        }
        default:
            break;
    }

    return var;
}

Variant
variant_op_lesser(Variant var1,
                  Variant var2)
{
    Variant var;

    int supra = var1.type > var2.type ? var1.type : var2.type;
    switch (supra)
    {
        case VBOOLEAN:
            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = VBOOLEAN;
            var.value.boolean = var1.value.boolean < var2.value.boolean;
            break;
        case VINT32:
            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = VBOOLEAN;
            var.value.boolean = var1.value.int32 < var2.value.int32;
            break;
        case VFLOAT32:
            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = VBOOLEAN;
            var.value.boolean = var1.value.float32 < var2.value.float32;
            break;
        case VTEXT:
        {
            int var1_free = var1.type != supra;
            int var2_free = var2.type != supra;

            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = VBOOLEAN;
            var.value.boolean = strcmp(var1.value.text, var2.value.text) < 0;

            if (var1_free)
                free(var1.value.text);
            if (var2_free)
                free(var2.value.text);
            break;
        }
        default:
            break;
    }

    return var;
}

Variant
variant_op_lesser_or_equal(Variant var1,
                           Variant var2)
{
    Variant var;

    int supra = var1.type > var2.type ? var1.type : var2.type;
    switch (supra)
    {
        case VBOOLEAN:
            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = VBOOLEAN;
            var.value.boolean = var1.value.boolean <= var2.value.boolean;
            break;
        case VINT32:
            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = VBOOLEAN;
            var.value.boolean = var1.value.int32 <= var2.value.int32;
            break;
        case VFLOAT32:
            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = VBOOLEAN;
            var.value.boolean = var1.value.float32 <= var2.value.float32;
            break;
        case VTEXT:
        {
            int var1_free = var1.type != supra;
            int var2_free = var2.type != supra;

            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = VBOOLEAN;
            var.value.boolean = strcmp(var1.value.text, var2.value.text) <= 0;

            if (var1_free)
                free(var1.value.text);
            if (var2_free)
                free(var2.value.text);
            break;
        }
        default:
            break;
    }

    return var;
}

Variant
variant_op_and(Variant var1,
               Variant var2)
{
    Variant var;

    int supra = var1.type > var2.type ? var1.type : var2.type;
    switch (supra)
    {
        case VBOOLEAN:
            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = VBOOLEAN;
            var.value.boolean = var1.value.boolean && var2.value.boolean;
            break;
        case VINT32:
            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = VBOOLEAN;
            var.value.boolean = var1.value.int32 && var2.value.int32;
            break;
        case VFLOAT32:
            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = VBOOLEAN;
            var.value.boolean = var1.value.float32 && var2.value.float32;
            break;
        case VTEXT:
        {
            int var1_free = var1.type != supra;
            int var2_free = var2.type != supra;

            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = VBOOLEAN;
            var.value.boolean = var1.value.text[0] != 0 && var2.value.text[0] != 0;

            if (var1_free)
                free(var1.value.text);
            if (var2_free)
                free(var2.value.text);
            break;
        }
        default:
            break;
    }

    return var;
}

Variant
variant_op_or(Variant var1,
              Variant var2)
{
    Variant var;

    int supra = var1.type > var2.type ? var1.type : var2.type;
    switch (supra)
    {
        case VBOOLEAN:
            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = VBOOLEAN;
            var.value.boolean = var1.value.boolean || var2.value.boolean;
            break;
        case VINT32:
            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = VBOOLEAN;
            var.value.boolean = var1.value.int32 || var2.value.int32;
            break;
        case VFLOAT32:
            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = VBOOLEAN;
            var.value.boolean = var1.value.float32 || var2.value.float32;
            break;
        case VTEXT:
        {
            int var1_free = var1.type != supra;
            int var2_free = var2.type != supra;

            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = VBOOLEAN;
            var.value.boolean = var1.value.text[0] != 0 || var2.value.text[0] != 0;

            if (var1_free)
                free(var1.value.text);
            if (var2_free)
                free(var2.value.text);
            break;
        }
        default:
            break;
    }

    return var;
}

Variant
variant_op_xor(Variant var1,
               Variant var2)
{
    Variant var;

    int supra = var1.type > var2.type ? var1.type : var2.type;
    switch (supra)
    {
        case VBOOLEAN:
            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = VBOOLEAN;
            var.value.boolean =    (var1.value.boolean && var2.value.boolean)
                                || (!var1.value.boolean && !var2.value.boolean);
            break;
        case VINT32:
            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = VBOOLEAN;
            var.value.boolean =    (var1.value.int32 && var2.value.int32)
                                || (!var1.value.int32 && !var2.value.int32);
            break;
        case VFLOAT32:
            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = VBOOLEAN;
            var.value.boolean =    (var1.value.float32 && var2.value.float32)
                                || (!var1.value.float32 && !var2.value.float32);
            break;
        case VTEXT:
        {
            int var1_free = var1.type != supra;
            int var2_free = var2.type != supra;

            variant_promote(&var1, supra);
            variant_promote(&var2, supra);

            var.type = VBOOLEAN;
            var.value.boolean =    (var1.value.text[0] != 0 && var2.value.text[0] != 0)
                                || (var1.value.text[0] == 0 && var2.value.text[0] == 0);

            if (var1_free)
                free(var1.value.text);
            if (var2_free)
                free(var2.value.text);
            break;
        }
        default:
            break;
    }

    return var;
}

Variant
variant_op_positive(Variant var)
{
    return variant_copy(var);
}

Variant
variant_op_negative(Variant var)
{
    switch (var.type)
    {
        case VINT32:
            var.value.int32 *= -1;
            break;
        case VFLOAT32:
            var.value.float32 *= -1;
            break;
        default:
            break;
    }

    return variant_copy(var);
}

Variant
variant_op_not(Variant var)
{
    switch (var.type)
    {
        case VBOOLEAN:
            var.value.boolean = !var.value.boolean;
            break;
        case VINT32:
            var.value.int32 = !var.value.int32;
            break;
        case VFLOAT32:
            var.value.float32 = !var.value.float32;
            break;
        default:
            break;
    }

    return variant_copy(var);
}

void
variant_print(Variant var)
{
    switch (var.type)
    {
        case VBOOLEAN:  printf("boolean(%d)",  var.value.boolean);    break;
        case VINT32:    printf("int32(%d)",    var.value.int32);      break;
        case VFLOAT32:  printf("float32(%f)",  var.value.float32);    break;
        case VTEXT:     printf("text(%s)",     var.value.text);       break;
        case VFUNCTION: printf("function(%p)", var.value.function);   break;
    }
}
