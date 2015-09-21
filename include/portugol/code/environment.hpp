#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

#include <portugol/code/code_chunk.hpp>
#include <portugol/code/tree/node.hpp>

namespace portugol
{
    namespace code
    {
        /// @brief
        class Environment
        {
        public:
            /// @brief
            class Register
            {
            public:
                /// @brief
                ///
                /// @param name
                /// @param node
                /// @param value
                Register(const std::string name,
                         tree::Node* node,
                         const Value value);

            public:
                /// @brief
                std::string m_name;

                /// @brief
                tree::Node* m_node;

                /// @brief
                Value m_value;
            }; /* end of : class Register */

            /// @brief
            class StackRegister : public Register
            {
            public:
                /// @brief
                ///
                /// @param name
                /// @param node
                /// @param value
                StackRegister(const std::string name,
                              tree::Node* node,
                              const Value value,
                              const std::size_t level,
                              const bool is_function,
                              const bool is_returning);

            public:
                /// @brief
                std::size_t m_level;

                /// @brief
                bool m_is_function;

                /// @brief
                bool m_is_returning;
            }; /* end of : class StackRegister : public Register */

        public:
            /// @brief
            ~Environment(void);

            /// @brief
            ///
            /// @param source
            /// @param code
            /// @return
            static CodeChunk*
            loadString(const std::string source,
                       const std::string code);

            /// @brief
            ///
            /// @param code
            /// @return
            static CodeChunk*
            loadFile(const std::string path);

            /// @brief
            static void
            clear(void);

            /// @brief
            ///
            /// @param name
            /// @return
            static Environment::Register
            get(const std::string name);

            /// @brief
            ///
            /// @param name
            /// @param node
            /// @return
            static tree::Node*
            heapInsert(const std::string name,
                       tree::Node* node);

            /// @brief
            ///
            /// @param name
            /// @param node
            /// @return
            static tree::Node*
            stackInsert(const std::string name,
                        tree::Node* node);

            /// @brief
            ///
            /// @param name
            /// @param scope
            /// @return
            static tree::Node*
            stackPush(const std::string name,
                      tree::Node* scope);

            /// @brief
            static void
            stackPop(void);

            /// @brief
            static bool
            stackIsReturning(void);

            /// @brief
            ///
            /// @param value
            static Value
            stackSetReturn(const Value value);

        protected:
            /// @brief
            Environment(void);

            /// @brief
            ///
            /// @param name
            /// @return
            Environment::Register
            _heapGet(const std::string name);

            /// @brief
            ///
            /// @param name
            /// @return
            Environment::Register
            _stackGet(const std::string name);

            /// @brief
            static void
            _destroySingleton(void);

        protected:
            /// @brief
            std::map<std::string, std::unique_ptr<CodeChunk>> m_chunks;

            /// @brief
            std::vector<Register> m_heap;

            /// @brief
            std::vector<StackRegister> m_stack;

            /// @brief
            std::size_t m_stack_level{ 0 };

            /// @brief
            static std::unique_ptr<Environment> m_singleton;
        }; /* end of : class Environment */
    } // end of : namespace code
} // end of : namespace portugol
