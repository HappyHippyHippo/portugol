#pragma once

#include <stdint.h>

#include <portugol/vartype.h>

/// @brief
typedef struct
{
    /// @brief
    VType type;

    /// @brief
    union
    {
        /// @brief
        int8_t vboolean;

        /// @brief
        int32_t vint32;

        /// @brief
        float vfloat32;

        /// @brief
        char* vtext;

        /// @brief
        void* vpointer;

        /// @brief
        const void* vfunction;
    } value;
} Variant;

/// @brief
///
/// @param variant
/// @param value
/// @return
Variant*
variant_init(Variant* variant,
             const Variant* value);

/// @brief
///
/// @param variant
/// @param type
/// @return
Variant*
variant_init_type(Variant* variant,
                  const VType type);

/// @brief
///
/// @param variant
/// @param value
/// @return
Variant*
variant_init_boolean(Variant* variant,
                     const int8_t value);

/// @brief
///
/// @param variant
/// @param value_str
/// @return
Variant*
variant_init_boolean_ex(Variant* variant,
                        const char* value_str);

/// @brief
///
/// @param variant
/// @param value
/// @return
Variant*
variant_init_int32(Variant* variant,
                   const int32_t value);

/// @brief
///
/// @param variant
/// @param value_str
/// @return
Variant*
variant_init_int32_ex(Variant* variant,
                      const char* value_str);

/// @brief
///
/// @param variant
/// @param value
/// @return
Variant*
variant_init_float32(Variant* variant,
                   const float value);

/// @brief
///
/// @param variant
/// @param value_str
/// @return
Variant*
variant_init_float32_ex(Variant* variant,
                        const char* value_str);

/// @brief
///
/// @param variant
/// @param value
/// @return
Variant*
variant_init_text(Variant* variant,
                  const char* value);

/// @brief
///
/// @param variant
/// @param value
/// @return
Variant*
variant_init_pointer(Variant* variant,
                     void* value);

/// @brief
///
/// @param variant
/// @param value
/// @return
Variant*
variant_init_function(Variant* variant,
                      const void* value);

/// @brief
///
/// @param variant
/// @return
Variant*
variant_uninit(Variant* variant);

/// @brief
///
/// @param variant
/// @param value
/// @return
Variant*
variant_assign(Variant* variant,
               const Variant* value);

/// @brief
///
/// @param variant
/// @param value
/// @return
Variant*
variant_assign_boolean(Variant* variant,
                       const int8_t value);

/// @brief
///
/// @param variant
/// @param value
/// @return
Variant*
variant_assign_int32(Variant* variant,
                     const int32_t value);

/// @brief
///
/// @param variant
/// @param value
/// @return
Variant*
variant_assign_float32(Variant* variant,
                       const float value);

/// @brief
///
/// @param variant
/// @param value
/// @return
Variant*
variant_assign_text(Variant* variant,
                    const char* value);

/// @brief
///
/// @param variant
/// @param value
/// @return
Variant*
variant_assign_pointer(Variant* variant,
                       void* value);

/// @brief
///
/// @param variant
/// @param value
/// @return
Variant*
variant_assign_function(Variant* variant,
                        const void* value);

/// @brief
///
/// @param variant
/// @param type
/// @return
Variant*
variant_cast(Variant* variant,
             const VType type);

/// @brief
///
/// @param variant
/// @param type
/// @return
Variant*
variant_promote(Variant* variant,
                const VType type);

/// @brief
///
/// @param variant
/// @param type
/// @return
Variant*
variant_demote(Variant* variant,
               const VType type);

/// @brief
///
/// @param result
/// @param op
/// @return
Variant*
variant_negate(Variant* result,
               const Variant* op);

/// @brief
///
/// @param result
/// @param op
/// @return
Variant*
variant_negative(Variant* result,
                 const Variant* op);

/// @brief
///
/// @param result
/// @param op1
/// @param op2
/// @return
Variant*
variant_add(Variant* result,
            const Variant* op1,
            const Variant* op2);

/// @brief
///
/// @param result
/// @param op1
/// @param op2
/// @return
Variant*
variant_subtract(Variant* result,
                 const Variant* op1,
                 const Variant* op2);

/// @brief
///
/// @param result
/// @param op1
/// @param op2
/// @return
Variant*
variant_multiply(Variant* result,
                 const Variant* op1,
                 const Variant* op2);

/// @brief
///
/// @param result
/// @param op1
/// @param op2
/// @return
Variant*
variant_divide(Variant* result,
               const Variant* op1,
               const Variant* op2);

/// @brief
///
/// @param result
/// @param op1
/// @param op2
/// @return
Variant*
variant_remainder(Variant* result,
                  const Variant* op1,
                  const Variant* op2);

/// @brief
///
/// @param result
/// @param op1
/// @param op2
/// @return
Variant*
variant_equal(Variant* result,
              const Variant* op1,
              const Variant* op2);

/// @brief
///
/// @param result
/// @param op1
/// @param op2
/// @return
Variant*
variant_inequal(Variant* result,
                const Variant* op1,
                const Variant* op2);

/// @brief
///
/// @param result
/// @param op1
/// @param op2
/// @return
Variant*
variant_greater(Variant* result,
                const Variant* op1,
                const Variant* op2);

/// @brief
///
/// @param result
/// @param op1
/// @param op2
/// @return
Variant*
variant_greater_or_equal(Variant* result,
                         const Variant* op1,
                         const Variant* op2);

/// @brief
///
/// @param result
/// @param op1
/// @param op2
/// @return
Variant*
variant_lesser(Variant* result,
               const Variant* op1,
               const Variant* op2);

/// @brief
///
/// @param result
/// @param op1
/// @param op2
/// @return
Variant*
variant_lesser_or_equal(Variant* result,
                        const Variant* op1,
                        const Variant* op2);

/// @brief
///
/// @param result
/// @param op1
/// @param op2
/// @return
Variant*
variant_and(Variant* result,
            const Variant* op1,
            const Variant* op2);

/// @brief
///
/// @param result
/// @param op1
/// @param op2
/// @return
Variant*
variant_or(Variant* result,
           const Variant* op1,
           const Variant* op2);

/// @brief
///
/// @param result
/// @param op1
/// @param op2
/// @return
Variant*
variant_xor(Variant* result,
            const Variant* op1,
            const Variant* op2);

/// @brief
///
/// @param variant
/// @return
void
variant_output(const Variant* variant);
