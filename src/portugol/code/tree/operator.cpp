#include <algorithm>

#include <portugol/code/tree/operator.hpp>

namespace portugol
{
    namespace code
    {
        namespace tree
        {
            Operator::Operator(const Value::Type return_type,
                               Node* parent)
                : Node{ Node::Type::OPERATOR,
                        return_type,
                        parent }
            {

            } /* end of : Operator::Operator(const Value::Type return_type,
                                             Node* parent) */

            Operator::~Operator(void)
            {

            } /* end of : Operator::~Operator(void) */


            BinaryOperator::BinaryOperator(Node* left_param,
                                           Node* right_param,
                                           Node* parent)
                : Operator{ Value::Type::INT32,
                            parent }
                , m_left_param{ left_param }
                , m_right_param{ right_param }
            {
                m_left_param->setParent(this);
                m_right_param->setParent(this);

                _calcResultType();
            } /* end of : BinaryOperator::BinaryOperator(Node* left_param,
                                                         Node* right_param,
                                                         Node* parent) */

            BinaryOperator::~BinaryOperator(void)
            {

            } /* end of : BinaryOperator::~BinaryOperator(void) */

            Node*
            BinaryOperator::getLeftParam(void)
            {
                return m_left_param.get();
            } /* end of : Node*
                          BinaryOperator::getLeftParam(void) */

            BinaryOperator&
            BinaryOperator::setLeftParam(Node* param)
            {
                m_left_param.reset(param);
                _calcResultType();

                return *this;
            } /* end of : BinaryOperator&
                          BinaryOperator::setLeftParam(Node* param) */

            Node*
            BinaryOperator::getRightParam(void)
            {
                return m_right_param.get();
            } /* end of : Node*
                          BinaryOperator::getRightParam(void) */

            BinaryOperator&
            BinaryOperator::setRightParam(Node* param)
            {
                m_right_param.reset(param);
                _calcResultType();

                return *this;
            } /* end of : BinaryOperator&
                          BinaryOperator::setRightParam(Node* param) */

            void
            BinaryOperator::_calcResultType(void)
            {
                m_return_type = static_cast<Value::Type>(std::max(static_cast<int>(m_left_param->getReturnType()), static_cast<int>(m_right_param->getReturnType())));
            } /* end of : void
                          BinaryOperator::_calcResultType(void) */

            AddOperator::AddOperator(Node* left_param,
                                     Node* right_param,
                                     Node* parent)
                : BinaryOperator{ left_param,
                                  right_param,
                                  parent }
            {

            } /* end of : AddOperator::AddOperator(Node* left_param,
                                                   Node* right_param,
                                                   Node* parent) */

            AddOperator::~AddOperator(void)
            {

            } /* end of : AddOperator::~AddOperator(void) */

            Value
            AddOperator::execute(void)
            {
                return m_left_param->execute().cast(m_return_type) + m_right_param->execute().cast(m_return_type);
            } /* end of : Value
                          AddOperator::execute(void) */

            SubtractOperator::SubtractOperator(Node* left_param,
                                               Node* right_param,
                                               Node* parent)
                : BinaryOperator{ left_param,
                                  right_param,
                                  parent }
            {

            } /* end of : SubtractOperator::SubtractOperator(Node* left_param,
                                                             Node* right_param,
                                                             Node* parent) */

            SubtractOperator::~SubtractOperator(void)
            {

            } /* end of : SubtractOperator::~SubtractOperator(void) */

            Value
            SubtractOperator::execute(void)
            {
                return m_left_param->execute().cast(m_return_type) - m_right_param->execute().cast(m_return_type);
            } /* end of : Value
                          SubtractOperator::execute(void) */

            MultiplyOperator::MultiplyOperator(Node* left_param,
                                               Node* right_param,
                                               Node* parent)
                : BinaryOperator{ left_param,
                                  right_param,
                                  parent }
            {

            } /* end of : MultiplyOperator::MultiplyOperator(Node* left_param,
                                                             Node* right_param,
                                                             Node* parent) */

            MultiplyOperator::~MultiplyOperator(void)
            {

            } /* end of : MultiplyOperator::~MultiplyOperator(void) */

            Value
            MultiplyOperator::execute(void)
            {
                return m_left_param->execute().cast(m_return_type) * m_right_param->execute().cast(m_return_type);
            } /* end of : Value
                          MultiplyOperator::execute(void) */

            DivideOperator::DivideOperator(Node* left_param,
                                           Node* right_param,
                                           Node* parent)
                : BinaryOperator{ left_param,
                                  right_param,
                                  parent }
            {

            } /* end of : DivideOperator::DivideOperator(Node* left_param,
                                                         Node* right_param,
                                                         Node* parent) */

            DivideOperator::~DivideOperator(void)
            {

            } /* end of : DivideOperator::~DivideOperator(void) */

            Value
            DivideOperator::execute(void)
            {
                return m_left_param->execute().cast(m_return_type) / m_right_param->execute().cast(m_return_type);
            } /* end of : Value
                          DivideOperator::execute(void) */

            RemainderOperator::RemainderOperator(Node* left_param,
                                                 Node* right_param,
                                                 Node* parent)
                : BinaryOperator{ left_param,
                                  right_param,
                                  parent }
            {

            } /* end of : RemainderOperator::RemainderOperator(Node* left_param,
                                                               Node* right_param,
                                                               Node* parent) */

            RemainderOperator::~RemainderOperator(void)
            {

            } /* end of : RemainderOperator::~RemainderOperator(void) */

            Value
            RemainderOperator::execute(void)
            {
                return m_left_param->execute().cast(m_return_type) % m_right_param->execute().cast(m_return_type);
            } /* end of : Value
                          RemainderOperator::execute(void) */
        } // end of : namespace tree
    } // end of : namespace code
} // end of : namespace portugol
