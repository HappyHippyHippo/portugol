#include <portugol/code/code_file.hpp>
#include <portugol/code/code_string.hpp>
#include <portugol/code/environment.hpp>
#include <portugol/code/tree/function.hpp>

namespace portugol
{
    namespace code
    {
        std::unique_ptr<Environment> Environment::m_singleton{ nullptr };

        Environment::Register::Register(const std::string name,
                                        tree::Node* node,
                                        const Value value)
        {
            m_name = name;
            m_node = node;
            m_value = value;
        } /* end of : Environment::Register::Register(const std::string name,
                                                      tree::Node* node,
                                                      const Value value) */

        Environment::StackRegister::StackRegister(const std::string name,
                                                  tree::Node* node,
                                                  const Value value,
                                                  const std::size_t level,
                                                  const bool is_function,
                                                  const bool is_returning)
            : Register{ name,
                        node,
                        value }
        {
            m_level = level;
            m_is_function = is_function;
            m_is_returning = is_returning;
        } /* end of : Environment::Register::Register(const std::string name,
                                                      tree::Node* node,
                                                      const Value value,
                                                      const std::size_t level,
                                                      const bool is_function,
                                                      const bool is_returning) */

        Environment::Environment(void)
        {
            atexit(Environment::_destroySingleton);
        } /* end of : Environment::Environment(void) */

        Environment::~Environment(void)
        {

        } /* end of : Environment::~Environment(void) */

        CodeChunk*
        Environment::loadString(const std::string source,
                                const std::string code)
        {
            if (m_singleton.get() == nullptr)
                m_singleton.reset(new Environment());

            auto find = m_singleton->m_chunks.find(source);
            if (find != m_singleton->m_chunks.end())
                return find->second.get();

            auto chunk = new CodeString(source, code);
            m_singleton->m_chunks.insert(std::pair<std::string, std::unique_ptr<CodeChunk>>(source, std::unique_ptr<CodeChunk>(chunk)));

            for (auto it = chunk->m_instructions.begin(), end = chunk->m_instructions.end();
                 it != end;
                 ++it)
            {
                switch (it->get()->getType())
                {
                    case tree::Node::Type::FUNCTION:
                        Environment::heapInsert(((tree::Function*) it->get())->getName(), it->get());
                        break;
                }
            }

            return chunk;
        } /* end of : CodeChunk*
                      Environment::loadString(const std::string source,
                                              const std::string code) */

        CodeChunk*
        Environment::loadFile(const std::string path)
        {
            if (m_singleton.get() == nullptr)
                m_singleton.reset(new Environment());

            auto find = m_singleton->m_chunks.find(path);
            if (find != m_singleton->m_chunks.end())
                return find->second.get();

            auto chunk = new CodeFile(path);
            m_singleton->m_chunks.insert(std::pair<std::string, std::unique_ptr<CodeChunk>>(path, std::unique_ptr<CodeChunk>(chunk)));

            for (auto it = chunk->m_instructions.begin(), end = chunk->m_instructions.end();
                 it != end;
                 ++it)
            {
                switch (it->get()->getType())
                {
                    case tree::Node::Type::FUNCTION:
                        Environment::heapInsert(((tree::Function*) it->get())->getName(), it->get());
                        break;
                }
            }

            return chunk;
        } /* end of : CodeChunk*
                      Environment::loadFile(const std::string path) */

        void
        Environment::clear(void)
        {
            if (m_singleton.get() == nullptr)
                m_singleton.reset(new Environment());

            m_singleton->m_chunks.clear();
            m_singleton->m_heap.clear();
            m_singleton->m_stack.clear();

            m_singleton->m_stack_level = 0;
        } /* end of : void
                      Environment::clear(void) */

        Environment::Register
        Environment::get(const std::string name)
        {
            if (m_singleton.get() == nullptr)
                m_singleton.reset(new Environment());

            try
            {
                return m_singleton->_stackGet(name);
            }
            catch (...)
            {
            }

            return m_singleton->_heapGet(name);
        } /* end of : Environment::Register
                      Environment::get(const std::string name) */

        tree::Node*
        Environment::heapInsert(const std::string name,
                                tree::Node* node)
        {
            if (m_singleton.get() == nullptr)
                m_singleton.reset(new Environment());

            m_singleton->m_heap.push_back({ name, node, { node->getReturnType() } });

            return node;
        } /* end of : tree::Node*
                      Environment::heapInsert(const std::string name,
                                              tree::Node* node) */

        tree::Node*
        Environment::stackInsert(const std::string name,
                                 tree::Node* node)
        {
            if (m_singleton.get() == nullptr)
                m_singleton.reset(new Environment());

            m_singleton->m_stack.push_back({ name, node, { node->getReturnType() }, m_singleton->m_stack_level, false, false });

            return node;
        } /* end of : void
                      Environment::stackInsert(const std::string name,
                                               tree::Node* node) */

        tree::Node*
        Environment::stackPush(const std::string name,
                               tree::Node* scope)
        {
            if (m_singleton.get() == nullptr)
                m_singleton.reset(new Environment());

            m_singleton->m_stack.push_back({ name, scope, { scope->getReturnType() }, ++m_singleton->m_stack_level, scope->getType() == tree::Node::Type::FUNCTION, false });

            return scope;
        } /* end of : void
                      Environment::stackPush(const std::string name,
                                             tree::Node* scope) */

        void
        Environment::stackPop(void)
        {
            if (m_singleton.get() == nullptr)
                m_singleton.reset(new Environment());

            while (   m_singleton->m_stack.size()
                   && m_singleton->m_stack.back().m_level == m_singleton->m_stack_level)
                m_singleton->m_stack.pop_back();

            --m_singleton->m_stack_level;
        } /* end of : void
                      Environment::stackPop(void) */

        bool
        Environment::stackIsReturning(void)
        {
            if (m_singleton.get() == nullptr)
                m_singleton.reset(new Environment());

            for (auto it = m_singleton->m_stack.rbegin(), it_end = m_singleton->m_stack.rend();
                 it != it_end;
                 ++it)
            {
                if (it->m_is_function)
                    return it->m_is_returning;
            }

            return false;
        } /* end of : bool
                      Environment::stackIsReturning(void) */

        Value
        Environment::stackSetReturn(const Value value)
        {
            if (m_singleton.get() == nullptr)
                m_singleton.reset(new Environment());

            for (auto it = m_singleton->m_stack.rbegin(), it_end = m_singleton->m_stack.rend();
                 it != it_end;
                 ++it)
            {
                if (it->m_is_function)
                {
                    it->m_is_returning = true;
                    it->m_value = value;
                    return value;
                }
            }

            throw std::string{ "Trying to assign a return value on not a function context" };
        } /* end of : void
                      Environment::stackSetReturn(const Value value) */

        Environment::Register
        Environment::_heapGet(const std::string name)
        {
            for (auto it = m_singleton->m_heap.rbegin(), it_end = m_singleton->m_heap.rend();
                 it != it_end;
                 ++it)
            {
                if (it->m_name == name)
                    return *it;
            }

            throw std::string{ "Element not found in the environment heap" };
        } /* end of : Environment::Register
                      Environment::_heapGet(const std::string name) */

        Environment::Register
        Environment::_stackGet(const std::string name)
        {
            for (auto it = m_singleton->m_stack.rbegin(), it_end = m_singleton->m_stack.rend();
                 it != it_end;
                 ++it)
            {
                if (it->m_name == name)
                    return *it;
            }

            throw std::string{ "Element not found in the environment stack" };
        } /* end of : Environment::Register
                      Environment::_stackGet(const std::string name) */

        void
        Environment::_destroySingleton(void)
        {
            if (m_singleton.get() != nullptr)
                m_singleton.reset(nullptr);
        } /* end of : void
                      Environment::_destroySingleton(void) */
    } // end of : namespace code
} // end of : namespace portugol
