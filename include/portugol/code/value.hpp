#pragma once

#include <cstdint>
#include <string>

namespace portugol
{
    namespace code
    {
        /// @brief
        class Value
        {
        public:
            /// @brief
            enum class Type
            {
                /// @brief
                BOOLEAN,

                /// @brief
                INT32,

                /// @brief
                FLOAT32,
 
                /// @brief
                TEXT
            }; /* end of : enum class Type */

        public:
            /// @brief
            ///
            /// @param type
            Value(const Value::Type type = Value::Type::INT32);

            /// @brief
            ///
            /// @param value
            Value(const Value& value);

            /// @brief
            ///
            /// @param value
            Value(Value&& value);

            /// @brief
            ~Value(void);

            /// @brief
            ///
            /// @param value
            /// @return
            Value&
            operator=(const Value& value);

            /// @brief
            ///
            /// @param value
            /// @return
            Value&
            operator=(Value&& value);

            /// @brief
            ///
            /// @param value
            /// @return
            Value
            operator+(const Value& value) const;

            /// @brief
            ///
            /// @param value
            /// @return
            Value
            operator-(const Value& value) const;

            /// @brief
            ///
            /// @param value
            /// @return
            Value
            operator*(const Value& value) const;

            /// @brief
            ///
            /// @param value
            /// @return
            Value
            operator/(const Value& value) const;

            /// @brief
            ///
            /// @param value
            /// @return
            Value
            operator%(const Value& value) const;

            /// @brief
            ///
            /// @param value
            /// @return
            Value&
            operator+=(const Value& value);

            /// @brief
            ///
            /// @param value
            /// @return
            Value&
            operator-=(const Value& value);

            /// @brief
            ///
            /// @param value
            /// @return
            Value&
            operator*=(const Value& value);

            /// @brief
            ///
            /// @param value
            /// @return
            Value&
            operator/=(const Value& value);

            /// @brief
            ///
            /// @param value
            /// @return
            Value&
            operator%=(const Value& value);

            /// @brief
            ///
            /// @return
            Value::Type
            getType(void) const;

            /// @brief
            ///
            /// @return
            void*
            getValue(void) const;

            /// @brief
            ///
            /// @return
            bool
            getBoolean(void) const;

            /// @brief
            ///
            /// @return
            bool&
            getBoolean(void);

            /// @brief
            ///
            /// @return
            std::int32_t
            getInt32(void) const;

            /// @brief
            ///
            /// @return
            std::int32_t&
            getInt32(void);

            /// @brief
            ///
            /// @return
            float
            getFloat32(void) const;

            /// @brief
            ///
            /// @return
            float&
            getFloat32(void);

            /// @brief
            ///
            /// @return
            std::string
            getText(void) const;

            /// @brief
            ///
            /// @return
            std::string&
            getText(void);

            /// @brief
            ///
            /// @param value
            /// @return
            Value&
            setBoolean(const bool value);

            /// @brief
            ///
            /// @param value
            /// @return
            Value&
            setInt32(const std::int32_t value);

            /// @brief
            ///
            /// @param value
            /// @return
            Value&
            setFloat32(const float value);

            /// @brief
            ///
            /// @param value
            /// @return
            Value&
            setText(const std::string value);

            /// @brief
            ///
            /// @param value
            /// @return
            Value&
            promote(const Value::Type type);

            /// @brief
            ///
            /// @param value
            /// @return
            Value
            promote(const Value::Type type) const;

            /// @brief
            ///
            /// @param value
            /// @return
            Value&
            demote(const Value::Type type);

            /// @brief
            ///
            /// @param value
            /// @return
            Value
            demote(const Value::Type type) const;

            /// @brief
            ///
            /// @param value
            /// @return
            Value&
            cast(const Value::Type type);

            /// @brief
            ///
            /// @param value
            /// @return
            Value
            cast(const Value::Type type) const;

        protected:
            /// @brief
            Value::Type m_type;

            /// @brief
            void* m_value;
        }; /* end of : class Value */
    } // end of : namespace code
} // end of : namespace portugol
