#pragma once

#include <stdint.h>

typedef enum
{
    VUNKNOWN   = 0,
    VBOOLEAN,
    VINT32,
    VFLOAT32,
    VTEXT
} VariantType;

typedef struct Variant
{
    int type;

    union
    {
        uint8_t boolean;
        int32_t int32;
        float float32;
        char* text;
    } value;
} Variant;

Variant
variant_init_boolean(int value);

Variant
variant_init_int32(int32_t value);

Variant
variant_init_float32(float value);

Variant
variant_init_text(char* value);

Variant
variant_copy(Variant var);

Variant*
variant_uninit(Variant* var);

Variant*
variant_set_boolean(Variant* var,
                    int value);

Variant*
variant_set_int32(Variant* var,
                  int32_t value);

Variant*
variant_set_float32(Variant* var,
                    float value);

Variant*
variant_set_text(Variant* var,
                 char* value);

Variant*
variant_set(Variant* var1,
            Variant var2);

Variant*
variant_promote(Variant* var,
                VariantType type);

Variant*
variant_demote(Variant* var,
               VariantType type);

Variant*
variant_cast(Variant* var,
             VariantType type);

Variant
variant_op_add(Variant var1,
               Variant var2);

Variant
variant_op_subtract(Variant var1,
                    Variant var2);

Variant
variant_op_multiply(Variant var1,
                    Variant var2);

Variant
variant_op_divide(Variant var1,
                  Variant var2);

Variant
variant_op_remainder(Variant var1,
                     Variant var2);

Variant
variant_op_equal(Variant var1,
                 Variant var2);

Variant
variant_op_inequal(Variant var1,
                   Variant var2);

Variant
variant_op_greater(Variant var1,
                   Variant var2);

Variant
variant_op_greater_or_equal(Variant var1,
                            Variant var2);

Variant
variant_op_lesser(Variant var1,
                   Variant var2);

Variant
variant_op_lesser_or_equal(Variant var1,
                           Variant var2);

Variant
variant_op_and(Variant var1,
               Variant var2);

Variant
variant_op_or(Variant var1,
              Variant var2);

Variant
variant_op_xor(Variant var1,
               Variant var2);

Variant
variant_op_positive(Variant var);

Variant
variant_op_negative(Variant var);

Variant
variant_op_not(Variant var);
