#include <string>

#include <portugol/code/tree/node.hpp>

namespace portugol
{
    namespace code
    {
        namespace tree
        {
            Node::Node(const Node::Type type,
                       const Value::Type return_type,
                       Node* parent)
                : m_type{ type }
                , m_return_type{ return_type }
                , m_parent{ parent }
            {

            } /* end of : Node::Node(const Node::Type type,
                                     const Value::Type return_type,
                                     Node* parent) */

            Node::~Node(void)
            {

            } /* end of : Node::~Node(void) */

            Node::Type
            Node::getType(void) const
            {
                return m_type;
            } /* end of : Node::Type
                          Node::getType(void) const */

            Value::Type
            Node::getReturnType(void) const
            {
                return m_return_type;
            } /* end of : Value::Type
                          Node::getReturnType(void) const */

            Node*
            Node::getParent(void) const
            {
                return m_parent;
            } /* end of : Node*
                          Node::getParent(void) const */

            Node&
            Node::setParent(Node* parent)
            {
                m_parent = parent;
                return *this;
            } /* end of : Node&
                          Node::setParent(Node* parent) */
        } // end of : namespace tree
    } // end of : namespace code
} // end of : namespace portugol
