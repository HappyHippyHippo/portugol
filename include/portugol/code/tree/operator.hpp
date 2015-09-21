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
            class Operator : public Node
            {
            public:
                /// @brief
                virtual
                ~Operator(void);

            protected:
                /// @brief
                ///
                /// @param return_type
                /// @param parent
                Operator(const Value::Type return_type = Value::Type::INT32,
                         Node* parent = nullptr);
            }; /* end of : class Operator : public Node */

            class BinaryOperator : public Operator
            {
            public:
                /// @brief
                virtual
                ~BinaryOperator(void);

                /// @brief
                ///
                /// @return
                Node*
                getLeftParam(void);

                /// @brief
                ///
                /// @param param
                /// @return
                BinaryOperator&
                setLeftParam(Node* param);

                /// @brief
                ///
                /// @return
                Node*
                getRightParam(void);

                /// @brief
                ///
                /// @param param
                /// @return
                BinaryOperator&
                setRightParam(Node* param);

            protected:
                /// @brief
                ///
                /// @param left_param
                /// @param right_param
                /// @param parent
                BinaryOperator(Node* left_param,
                               Node* right_param,
                               Node* parent = nullptr);

                /// @brief
                void
                _calcResultType(void);

            protected:
                /// @param
                std::unique_ptr<Node> m_left_param{ nullptr };

                /// @param
                std::unique_ptr<Node> m_right_param{ nullptr };
            }; /* end of : class BinaryOperator : public Operator */

            /// @brief
            class AddOperator : public BinaryOperator
            {
            public:
                /// @brief
                ///
                /// @param left_param
                /// @param right_param
                /// @param parent
                AddOperator(Node* left_param,
                            Node* right_param,
                            Node* parent = nullptr);

                /// @brief
                ~AddOperator(void);

                /// @brief
                ///
                /// @return
                Value
                execute(void);
            }; /* end of : class AddOperator : public BinaryOperator */

            /// @brief
            class SubtractOperator : public BinaryOperator
            {
            public:
                /// @brief
                ///
                /// @param left_param
                /// @param right_param
                /// @param parent
                SubtractOperator(Node* left_param,
                                 Node* right_param,
                                 Node* parent = nullptr);

                /// @brief
                ~SubtractOperator(void);

                /// @brief
                ///
                /// @return
                Value
                execute(void);
            }; /* end of : class SubtractOperator : public BinaryOperator */

            /// @brief
            class MultiplyOperator : public BinaryOperator
            {
            public:
                /// @brief
                ///
                /// @param left_param
                /// @param right_param
                /// @param parent
                MultiplyOperator(Node* left_param,
                                 Node* right_param,
                                 Node* parent = nullptr);

                /// @brief
                ~MultiplyOperator(void);

                /// @brief
                ///
                /// @return
                Value
                execute(void);
            }; /* end of : class MultiplyOperator : public BinaryOperator */

            /// @brief
            class DivideOperator : public BinaryOperator
            {
            public:
                /// @brief
                ///
                /// @param left_param
                /// @param right_param
                /// @param parent
                DivideOperator(Node* left_param,
                               Node* right_param,
                               Node* parent = nullptr);

                /// @brief
                ~DivideOperator(void);

                /// @brief
                ///
                /// @return
                Value
                execute(void);
            }; /* end of : class DivideOperator : public BinaryOperator */

            /// @brief
            class RemainderOperator : public BinaryOperator
            {
            public:
                /// @brief
                ///
                /// @param left_param
                /// @param right_param
                /// @param parent
                RemainderOperator(Node* left_param,
                                  Node* right_param,
                                  Node* parent = nullptr);

                /// @brief
                ~RemainderOperator(void);

                /// @brief
                ///
                /// @return
                Value
                execute(void);
            }; /* end of : class RemainderOperator : public BinaryOperator */
        } // end of : namespace tree
    } // end of : namespace code
} // end of : namespace portugol
