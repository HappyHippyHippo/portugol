#include <algorithm>

#include <portugol/code/value.hpp>

namespace portugol
{
    namespace code
    {
        Value::Value(const Value::Type type)
            : m_type{ type }
        {
            switch (m_type)
            {
                case Value::Type::BOOLEAN:
                    m_value = new bool;
                    *(bool*)m_value = 0;
                    break;
                case Value::Type::INT32:
                    m_value = new std::int32_t;
                    *(std::int32_t*)m_value = 0;
                    break;
                case Value::Type::FLOAT32:
                    m_value = new float;
                    *(float*)m_value = 0;
                    break;
                case Value::Type::TEXT:
                     m_value = new std::string;
                   break;
            }
        } /* Value::Value(const Value::Type type) */
        
        Value::Value(const Value& value)
            : m_type{ value.m_type }
        {
            switch (m_type)
            {
                case Value::Type::BOOLEAN:
                    m_value = new bool;
                    *(bool*)m_value = *(bool*)value.m_value;
                    break;
                case Value::Type::INT32:
                    m_value = new std::int32_t;
                    *(std::int32_t*)m_value = *(std::int32_t*)value.m_value;
                    break;
                case Value::Type::FLOAT32:
                    m_value = new float;
                    *(float*)m_value = *(float*)value.m_value;
                    break;
                case Value::Type::TEXT:
                     m_value = new std::string;
                    *(std::string*)m_value = *(std::string*)value.m_value;
                   break;
            }
        } /* end of : Value::Value(const Value& value) */

        Value::Value(Value&& value)
        {
            std::swap(m_type, value.m_type);
            std::swap(m_value, value.m_value);
        } /* end of : Value::Value(Value&& value) */

        Value::~Value(void)
        {
            switch (m_type)
            {
                case Value::Type::BOOLEAN:
                    delete (bool*) m_value;
                    break;
                case Value::Type::INT32:
                    delete (std::int32_t*) m_value;
                    break;
                case Value::Type::FLOAT32:
                    delete (float*) m_value;
                    break;
                case Value::Type::TEXT:
                     delete (std::string*) m_value;
                   break;
            }
        } /* end of : Value::~Value(void) */

        Value&
        Value::operator=(const Value& value)
        {
            switch (m_type)
            {
                case Value::Type::BOOLEAN:
                    delete (bool*) m_value;
                    break;
                case Value::Type::INT32:
                    delete (std::int32_t*) m_value;
                    break;
                case Value::Type::FLOAT32:
                    delete (float*) m_value;
                    break;
                case Value::Type::TEXT:
                     delete (std::string*) m_value;
                   break;
            }

            m_type = value.m_type;
            switch (m_type)
            {
                case Value::Type::BOOLEAN:
                    m_value = new bool;
                    *(bool*)m_value = *(bool*)value.m_value;
                    break;
                case Value::Type::INT32:
                    m_value = new std::int32_t;
                    *(std::int32_t*)m_value = *(std::int32_t*)value.m_value;
                    break;
                case Value::Type::FLOAT32:
                    m_value = new float;
                    *(float*)m_value = *(float*)value.m_value;
                    break;
                case Value::Type::TEXT:
                     m_value = new std::string;
                    *(std::string*)m_value = *(std::string*)value.m_value;
                   break;
            }

            return *this;
        } /* end of : Value&
                      Value::operator=(const Value& value) */

        Value&
        Value::operator=(Value&& value)
        {
            std::swap(m_type, value.m_type);
            std::swap(m_value, value.m_value);

            return *this;
        } /* end of : Value&
                      Value::operator=(Value&& value) */

        Value
        Value::operator+(const Value& value) const
        {
            Value::Type supra = static_cast<Value::Type>(std::max(static_cast<int>(m_type), static_cast<int>(value.m_type)));
            Value result{ supra };

            switch (supra)
            {
                case Value::Type::BOOLEAN:
                {
                    result.setBoolean((this->cast(supra).getBoolean() + value.cast(supra).getBoolean()) != 0);
                    break;
                }
                case Value::Type::INT32:
                {
                    result.setInt32(this->cast(supra).getInt32() + value.cast(supra).getInt32());
                    break;
                }
                case Value::Type::FLOAT32:
                {
                    result.setFloat32(this->cast(supra).getFloat32() + value.cast(supra).getFloat32());
                    break;
                }
                case Value::Type::TEXT:
                {
                    result.setText(this->cast(supra).getText() + value.cast(supra).getText());
                    break;
                }
            }

            return result;
        } /* end of : Value
                      Value::operator+(const Value& value) const */

        Value
        Value::operator-(const Value& value) const
        {
            Value::Type supra = static_cast<Value::Type>(std::max(static_cast<int>(m_type), static_cast<int>(value.m_type)));
            Value result{ supra };

            switch (supra)
            {
                case Value::Type::BOOLEAN:
                {
                    result.setBoolean((this->cast(supra).getBoolean() - value.cast(supra).getBoolean()) != 0);
                    break;
                }
                case Value::Type::INT32:
                {
                    result.setInt32(this->cast(supra).getInt32() - value.cast(supra).getInt32());
                    break;
                }
                case Value::Type::FLOAT32:
                {
                    result.setFloat32(this->cast(supra).getFloat32() - value.cast(supra).getFloat32());
                    break;
                }
                case Value::Type::TEXT:
                {
                    throw std::string{ "Invalid subtraction operation on a text value" };
                }
            }

            return result;
        } /* end of : Value
                      Value::operator-(const Value& value) const */

        Value
        Value::operator*(const Value& value) const
        {
            Value::Type supra = static_cast<Value::Type>(std::max(static_cast<int>(m_type), static_cast<int>(value.m_type)));
            Value result{ supra };

            switch (supra)
            {
                case Value::Type::BOOLEAN:
                {
                    result.setBoolean((this->cast(supra).getBoolean() * value.cast(supra).getBoolean()) != 0);
                    break;
                }
                case Value::Type::INT32:
                {
                    result.setInt32(this->cast(supra).getInt32() * value.cast(supra).getInt32());
                    break;
                }
                case Value::Type::FLOAT32:
                {
                    result.setFloat32(this->cast(supra).getFloat32() * value.cast(supra).getFloat32());
                    break;
                }
                case Value::Type::TEXT:
                {
                    throw std::string{ "Invalid multiplication operation on a text value" };
                }
            }

            return result;
        } /* end of : Value
                      Value::operator*(const Value& value) const */

        Value
        Value::operator/(const Value& value) const
        {
            Value::Type supra = static_cast<Value::Type>(std::max(static_cast<int>(m_type), static_cast<int>(value.m_type)));
            Value result{ supra };

            switch (supra)
            {
                case Value::Type::BOOLEAN:
                {
                    result.setBoolean(this->cast(supra).getBoolean());
                    break;
                }
                case Value::Type::INT32:
                {
                    result.setInt32(this->cast(supra).getInt32() / value.cast(supra).getInt32());
                    break;
                }
                case Value::Type::FLOAT32:
                {
                    result.setFloat32(this->cast(supra).getFloat32() / value.cast(supra).getFloat32());
                    break;
                }
                case Value::Type::TEXT:
                {
                    throw std::string{ "Invalid division operation on a text value" };
                }
            }

            return result;
        } /* end of : Value
                      Value::operator/(const Value& value) const */

        Value
        Value::operator%(const Value& value) const
        {
            Value::Type supra = static_cast<Value::Type>(std::max(static_cast<int>(m_type), static_cast<int>(value.m_type)));
            Value result{ supra };

            switch (supra)
            {
                case Value::Type::BOOLEAN:
                {
                    result.setBoolean(0);
                    break;
                }
                case Value::Type::INT32:
                {
                    result.setInt32(this->cast(supra).getInt32() % value.cast(supra).getInt32());
                    break;
                }
                case Value::Type::FLOAT32:
                {
                    result.setFloat32((float) ((int) this->cast(supra).getFloat32() % (int) value.cast(supra).getFloat32()));
                    break;
                }
                case Value::Type::TEXT:
                {
                    throw std::string{ "Invalid remainder operation on a text value" };
                }
            }

            return result;
        } /* end of : Value
                      Value::operator%(const Value& value) const */

        Value&
        Value::operator+=(const Value& value)
        {
            switch (m_type)
            {
                case Value::Type::BOOLEAN:
                {
                    *(bool*)m_value = (*(bool*)m_value + value.cast(m_type).getBoolean()) != 0;
                    break;
                }
                case Value::Type::INT32:
                {
                    *(std::int32_t*)m_value += value.cast(m_type).getInt32();
                    break;
                }
                case Value::Type::FLOAT32:
                {
                    *(float*)m_value += value.cast(m_type).getFloat32();
                    break;
                }
                case Value::Type::TEXT:
                {
                    *(std::string*)m_value += value.cast(m_type).getText();
                    break;
                }
            }

            return *this;
        } /* end of : Value&
                      Value::operator+=(const Value& value) */

        Value&
        Value::operator-=(const Value& value)
        {
            switch (m_type)
            {
                case Value::Type::BOOLEAN:
                {
                    *(bool*)m_value = (*(bool*)m_value - value.cast(m_type).getBoolean()) != 0;
                    break;
                }
                case Value::Type::INT32:
                {
                    *(std::int32_t*)m_value -= value.cast(m_type).getInt32();
                    break;
                }
                case Value::Type::FLOAT32:
                {
                    *(float*)m_value -= value.cast(m_type).getFloat32();
                    break;
                }
                case Value::Type::TEXT:
                {
                    throw std::string{ "Invalid subtraction operation on a text value" };
                }
            }

            return *this;
        } /* end of : Value&
                      Value::operator-=(const Value& value) */

        Value&
        Value::operator*=(const Value& value)
        {
            switch (m_type)
            {
                case Value::Type::BOOLEAN:
                {
                    *(bool*)m_value = (*(bool*)m_value * value.cast(m_type).getBoolean()) != 0;
                    break;
                }
                case Value::Type::INT32:
                {
                    *(std::int32_t*)m_value *= value.cast(m_type).getInt32();
                    break;
                }
                case Value::Type::FLOAT32:
                {
                    *(float*)m_value *= value.cast(m_type).getFloat32();
                    break;
                }
                case Value::Type::TEXT:
                {
                    throw std::string{ "Invalid multiplication operation on a text value" };
                }
            }

            return *this;
        } /* end of : Value&
                      Value::operator*=(const Value& value) */

        Value&
        Value::operator/=(const Value& value)
        {
            switch (m_type)
            {
                case Value::Type::BOOLEAN:
                {
                    *(bool*)m_value = *(bool*)m_value;
                    break;
                }
                case Value::Type::INT32:
                {
                    *(std::int32_t*)m_value /= value.cast(m_type).getInt32();
                    break;
                }
                case Value::Type::FLOAT32:
                {
                    *(float*)m_value /= value.cast(m_type).getFloat32();
                    break;
                }
                case Value::Type::TEXT:
                {
                    throw std::string{ "Invalid division operation on a text value" };
                }
            }

            return *this;
        } /* end of : Value&
                      Value::operator/=(const Value& value) */

        Value&
        Value::operator%=(const Value& value)
        {
            switch (m_type)
            {
                case Value::Type::BOOLEAN:
                {
                    *(bool*)m_value = 0;
                    break;
                }
                case Value::Type::INT32:
                {
                    *(std::int32_t*)m_value %= value.cast(m_type).getInt32();
                    break;
                }
                case Value::Type::FLOAT32:
                {
                    *(float*)m_value = (float)((int) *(float*)m_value % (int) value.cast(m_type).getFloat32());
                    break;
                }
                case Value::Type::TEXT:
                {
                    throw std::string{ "Invalid remainder operation on a text value" };
                }
            }

            return *this;
        } /* end of : Value&
                      Value::operator%=(const Value& value) */

        Value::Type
        Value::getType(void) const
        {
            return m_type;
        } /* end of : Value::Type
                      Value::getType(void) const */

        void*
        Value::getValue(void) const
        {
            return m_value;
        } /* end of : void*
                      Value::getValue(void) const */

        bool
        Value::getBoolean(void) const
        {
            if (m_type != Value::Type::BOOLEAN)
                throw std::string{ "Trying to retrieve a bool ean value from a not boolean value object" };

            return *(bool*) m_value;
        } /* end of : bool
                      Value::getBoolean(void) const */

        bool&
        Value::getBoolean(void)
        {
            if (m_type != Value::Type::BOOLEAN)
                throw std::string{ "Trying to retrieve a boolean value from a not boolean value object" };

            return *(bool*) m_value;
        } /* end of : bool&
                      Value::getBoolean(void) */

        std::int32_t
        Value::getInt32(void) const
        {
            if (m_type != Value::Type::INT32)
                throw std::string{ "Trying to retrieve a int32 value from a not int32 value object" };

            return *(std::int32_t*) m_value;
        } /* end of : std::int32_t
                      Value::getInt32(void) const */

        std::int32_t&
        Value::getInt32(void)
        {
            if (m_type != Value::Type::INT32)
                throw std::string{ "Trying to retrieve a int32 value from a not int32 value object" };

            return *(std::int32_t*) m_value;
        } /* end of : std::int32_t&
                      Value::getInt32(void) */

        float
        Value::getFloat32(void) const
        {
            if (m_type != Value::Type::FLOAT32)
                throw std::string{ "Trying to retrieve a float value from a not float value object" };

            return *(float*) m_value;
        } /* end of : float
                      Value::getFloat32(void) const */

        float&
        Value::getFloat32(void)
        {
            if (m_type != Value::Type::FLOAT32)
                throw std::string{ "Trying to retrieve a float value from a not float value object" };

            return *(float*) m_value;
        } /* end of : float&
                      Value::getFloat32(void) */

        std::string
        Value::getText(void) const
        {
            if (m_type != Value::Type::TEXT)
                throw std::string{ "Trying to retrieve a text value from a not text value object" };

            return *(std::string*) m_value;
        } /* end of : std::string
                      Value::getText(void) const */

        std::string&
        Value::getText(void)
        {
            if (m_type != Value::Type::TEXT)
                throw std::string{ "Trying to retrieve a text value from a not text value object" };

            return *(std::string*) m_value;
        } /* end of : std::string&
                      Value::getText(void) */

        Value&
        Value::setBoolean(const bool value)
        {
            if (m_type != Value::Type::BOOLEAN)
                throw std::string{ "Trying to assign a boolean value to a not boolean value object" };

            *(bool*) m_value = value;
            return *this;
        } /* end of : Value&
                      Value::setBoolean(const bool value) */

        Value&
        Value::setInt32(const std::int32_t value)
        {
            if (m_type != Value::Type::INT32)
                throw std::string{ "Trying to assign a int32 value to a not int32 value object" };

            *(std::int32_t*) m_value = value;
            return *this;
        } /* end of : Value&
                      Value::setInt32(const std::int32_t value) */

        Value&
        Value::setFloat32(const float value)
        {
            if (m_type != Value::Type::FLOAT32)
                throw std::string{ "Trying to assign a float32 value to a not float32 value object" };

            *(float*) m_value = value;
            return *this;
        } /* end of : Value&
                      Value::setFloat32(const float value) */

        Value&
        Value::setText(const std::string value)
        {
            if (m_type != Value::Type::TEXT)
                throw std::string{ "Trying to assign a text value to a not text value object" };

            *(std::string*) m_value = value;
            return *this;
        } /* end of : Value&
                      Value::setText(const std::string value) */

        Value&
        Value::promote(const Value::Type type)
        {
            if (   m_type == Value::Type::TEXT
                || type == Value::Type::TEXT)
                throw std::string{ "Can only promote from and to a natural numerical type" };

            switch (m_type)
            {
                case Value::Type::BOOLEAN:
                {
                    switch (type)
                    {
                        case Value::Type::INT32:
                        {
                            std::int32_t* pnew = new std::int32_t;
                            *pnew = *(bool*) m_value;

                            delete (bool*) m_value;
                            m_value = pnew;

                            break;
                        }
                        case Value::Type::FLOAT32:
                        {
                            float* pnew = new float;
                            *pnew = *(bool*) m_value;

                            delete (bool*) m_value;
                            m_value = pnew;

                            break;
                        }
                    }
                    break;
                }
                case Value::Type::INT32:
                {
                    switch (type)
                    {
                        case Value::Type::FLOAT32:
                        {
                            float* pnew = new float;
                            *pnew = (float) *(std::int32_t*) m_value;

                            delete (std::int32_t*) m_value;
                            m_value = pnew;

                            break;
                        }
                    }
                    break;
                }
            }

            return *this;
        } /* end of : Value&
                      Value::promote(const Value::Type type) */

        Value
        Value::promote(const Value::Type type) const
        {
            Value result = *this;
            return result.promote(type);
        } /* end of : Value
                      Value::promote(const Value::Type type) const */

        Value&
        Value::demote(const Value::Type type)
        {
            if (   m_type == Value::Type::TEXT
                || type == Value::Type::TEXT)
                throw std::string{ "Can only demote from and to a natural numerical type" };

            switch (m_type)
            {
                case Value::Type::INT32:
                {
                    switch (type)
                    {
                        case Value::Type::BOOLEAN:
                        {
                            bool* pnew = new bool;
                            *pnew = *(std::int32_t*) m_value != 0;

                            delete (std::int32_t*) m_value;
                            m_value = pnew;

                            break;
                        }
                    }
                    break;
                }
                case Value::Type::FLOAT32:
                {
                    switch (type)
                    {
                        case Value::Type::BOOLEAN:
                        {
                            bool* pnew = new bool;
                            *pnew = *(float*) m_value != 0;

                            delete (float*) m_value;
                            m_value = pnew;

                            break;
                        }
                        case Value::Type::INT32:
                        {
                            std::int32_t* pnew = new std::int32_t;
                            *pnew = *(float*) m_value != 0;

                            delete (float*) m_value;
                            m_value = pnew;

                            break;
                        }
                    }
                    break;
                }
            }

            return *this;
        } /* end of : Value&
                      Value::demote(const Value::Type type) */

        Value
        Value::demote(const Value::Type type) const
        {
            Value result = *this;
            return result.demote(type);
        } /* end of : Value
                      Value::demote(const Value::Type type) const */

        Value&
        Value::cast(const Value::Type type)
        {
            if (static_cast<int>(type) > static_cast<int>(m_type))
                return promote(type);
            return demote(type);
        } /* end of : Value&
                      Value::cast(const Value::Type type) */

        Value
        Value::cast(const Value::Type type) const
        {
            if (static_cast<int>(type) > static_cast<int>(m_type))
                return promote(type);
            return demote(type);
        } /* end of : Value
                      Value::cast(const Value::Type type) const */
    } // end of : namespace code
} // end of : namespace portugol
