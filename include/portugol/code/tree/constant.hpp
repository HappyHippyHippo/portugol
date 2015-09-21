#pragma once

#include <portugol/code/tree/node.hpp>

namespace portugol
{
    namespace code
    {
        namespace tree
        {
            /// @brief
            class Constant : public Node
            {
            public:
                /// @brief
                ///
                /// @param type
                /// @param parent
                Constant(Value::Type type,
                         Node* parent = nullptr);

                /// @brief
                ~Constant(void);

                /// @brief
                ///
                /// @return
                Value&
                getValue(void);

                /// @brief
                ///
                /// @return
                Value
                execute(void);

            protected:
                /// @brief
                Value m_value;
            }; /* end of : class Constant */
        } // end of : namespace tree
    } // end of : namespace code
} // end of : namespace portugol
