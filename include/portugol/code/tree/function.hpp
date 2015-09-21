#pragma once

#include <portugol/code/tree/scope.hpp>

namespace portugol
{
    namespace code
    {
        namespace tree
        {
            /// @brief
            class Function : public Scope
            {
            public:
                /// @brief
                ///
                /// @param name
                /// @param return_type
                /// @param parent
                Function(const std::string name,
                         const Value::Type return_type = Value::Type::INT32,
                         Node* parent = nullptr);

                /// @brief
                ~Function(void);

                /// @brief
                ///
                /// @return
                std::string
                getName(void) const;

                /// @brief
                ///
                /// @return
                Value
                execute(void);

            protected:
                /// @brief
                std::string m_name;
            }; /* end of : class Function */
        } // end of : namespace tree
    } // end of : namespace code
} // end of : namespace portugol
