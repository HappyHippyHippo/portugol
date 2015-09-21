#include <portugol/code/environment.hpp>
#include <portugol/code/tree/function.hpp>

namespace portugol
{
    namespace code
    {
        namespace tree
        {
            Function::Function(const std::string name,
                               const Value::Type return_type,
                               Node* parent)
                : Scope{ Node::Type::FUNCTION,
                         return_type,
                         parent }
            {
                m_name = name;
            } /* end of : Function::Function(const std::string name,
                                             const Value::Type return_type,
                                             Node* parent) */

            Function::~Function(void)
            {
            } /* end of : Function::~Function(void) */

            std::string
            Function::getName(void) const
            {
                return m_name;
            } /* end of : std::string
                          Function::getName(void) const(void) const */

            Value
            Function::execute(void)
            {
                Environment::stackPush("/return", this);

                for (auto it = m_code.begin(), it_end = m_code.end();
                        it != it_end
                     && !Environment::stackIsReturning();
                     ++it)
                {
                    if (it->get()->getType() == Node::Type::RETURN)
                        it->get()->execute();
                }

                auto result = Environment::get("/return");
                Environment::stackPop();

                return result.m_value;
            } /* end of : Value
                          Function::execute(void) */
        } // end of : namespace tree
    } // end of : namespace code
} // end of : namespace portugol
