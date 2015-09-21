#pragma once

#include <portugol/code/value.hpp>

namespace portugol
{
    namespace code
    {
        namespace tree
        {
            /// @brief
            class Node
            {
            public:
                /// @brief
                enum class Type
                {
                    /// @brief
                    UNKNOWN,

                    /// @brief
                    CONSTANT,

                    /// @brief
                    OPERATOR,

                    /// @brief
                    FUNCTION,

                    /// @brief
                    RETURN
                }; /* end of : enum class Type */

            public:
                /// @brief
                virtual
                ~Node(void);

                /// @brief
                ///
                /// @return
                Node::Type
                getType(void) const;

                /// @brief
                ///
                /// @return
                Value::Type
                getReturnType(void) const;

                /// @brief
                ///
                /// @return
                Node*
                getParent(void) const;

                /// @brief
                ///
                /// @param parent
                /// @return
                Node&
                setParent(Node* parent);

                /// @brief
                ///
                /// @return
                virtual Value
                execute(void) = 0;

            protected:
                /// @brief
                ///
                /// @param type
                /// @param return_type
                /// @param parent
                Node(const Node::Type type = Node::Type::UNKNOWN,
                     const Value::Type return_type = Value::Type::INT32,
                     Node* parent = nullptr);

            protected:
                /// @brief
                Node::Type m_type;

                /// @brief
                Value::Type m_return_type;

                /// @brief
                Node* m_parent;
            }; /* end of : class Node */
        } // end of : namespace tree
    } // end of : namespace code
} // end of : namespace portugol
