#include <portugol/code/tree/scope.hpp>

namespace portugol
{
    namespace code
    {
        namespace tree
        {
            Scope::Scope(const Node::Type type,
                         const Value::Type return_type,
                         Node* parent)
                : Node{ type,
                        return_type,
                        parent }
            {

            } /* end of : Scope::Scope(const Node::Type type,
                                       const Value::Type return_type,
                                       Node* parent) */

            Scope::~Scope(void)
            {

            } /* end of : Scope::~Scope(void) */

            Scope&
            Scope::pushInstruction(Node* node)
            {
                m_code.push_back(std::unique_ptr<Node>(node));
                return *this;
            } /* end of : Scope&
                          Scope::pushInstruction(Node* node) */
        } // end of : namespace tree
    } // end of : namespace code
} // end of : namespace portugol
