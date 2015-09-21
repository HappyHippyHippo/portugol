#pragma once

#include <memory>

#include <portugol/code/tree/node.hpp>

namespace portugol
{
    namespace code
    {
        namespace tree
        {
            /// @brief
            class Return : public Node
            {
            public:
                /// @brief
                ///
                /// @param result
                /// @param parent
                Return(Node* result = nullptr,
                       const Value::Type return_type = Value::Type::INT32,
                       Node* parent = nullptr);

                /// @brief
                ~Return(void);

                /// @brief
                ///
                /// @return
                Node*
                getResult(void) const;

                /// @brief
                ///
                /// @param result
                /// @return
                Return&
                setResult(Node* result);

                /// @brief
                ///
                /// @return
                Value
                execute(void);

            protected:
                /// @brief
                std::unique_ptr<Node> m_result;
            }; /* end of : class Return */
        } // end of : namespace tree
    } // end of : namespace code
} // end of : namespace portugol
