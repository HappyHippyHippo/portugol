#include <portugol/code/environment.hpp>
#include <portugol/code/tree/return.hpp>

namespace portugol
{
    namespace code
    {
        namespace tree
        {
                Return::Return(Node* result,
                               const Value::Type return_type,
                               Node* parent)
                    : Node{ Node::Type::RETURN,
                            return_type,
                            parent }
                    , m_result{ result }
                {

                } /* end of : Return::Return(Node* result,
                                             const Value::Type return_type,
                                             Node* parent) */

                Return::~Return(void)
                {

                } /* end of : Return::~Return(void) */

                Node*
                Return::getResult(void) const
                {
                    return m_result.get();
                } /* end of : Node*
                              Return::getResult(void) const */

                Return&
                Return::setResult(Node* result)
                {
                    m_result.reset(result);
                    return *this;
                } /* end of : Return&
                              Return::setResult(Node* result) */

                Value
                Return::execute(void)
                {
                    auto result = m_result->execute().cast(m_return_type);
                    Environment::stackSetReturn(result);
                    return result;
                } /* end of : Value
                              Return::execute(void) */
        } // end of : namespace tree
    } // end of : namespace code
} // end of : namespace portugol
