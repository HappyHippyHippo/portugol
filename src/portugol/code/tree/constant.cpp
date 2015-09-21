#include <portugol/code/tree/constant.hpp>

namespace portugol
{
    namespace code
    {
        namespace tree
        {
            Constant::Constant(Value::Type type,
                               Node* parent)
                : Node{ Node::Type::CONSTANT,
                        type,
                        parent }
                , m_value{ type }
            {

            } /* end of : Constant::Constant(Value::Type type,
                                             Node* parent) */

            Constant::~Constant(void)
            {

            } /* end of : Constant::~Constant(void) */

            Value&
            Constant::getValue(void)
            {
                return m_value;
            } /* end of : Value&
                          Constant::getValue(void) */

            Value
            Constant::execute(void)
            {
                return m_value;
            } /* end of : Value
                          Constant::execute(void) */
        } // end of : namespace tree
    } // end of : namespace code
} // end of : namespace portugol
