#pragma once

#include <memory>
#include <vector>

#include <portugol/code/tree/node.hpp>

namespace portugol
{
    namespace code
    {
        namespace tree
        {
            /// @brief
            class Scope : public Node
            {
            public:
                /// @brief
                virtual
                ~Scope(void);

                /// @brief
                ///
                /// @param node
                /// @return
                Scope&
                pushInstruction(Node* node);

            protected:
                /// @brief
                ///
                /// @param type
                /// @param return_type
                /// @param parent
                Scope(const Node::Type type = Node::Type::UNKNOWN,
                      const Value::Type return_type = Value::Type::INT32,
                      Node* parent = nullptr);

            protected:
                /// @brief
                std::vector<std::unique_ptr<Node>> m_code;
            }; /* end of : class Scope */
        } // end of : namespace tree
    } // end of : namespace code
} // end of : namespace portugol
