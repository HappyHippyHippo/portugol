#pragma once

#include <hypnos/hypnos.hpp>
using namespace hyp;

/// @brief
class IState : public State
{
public:
    /// @brief
    ///
    /// @param app
    IState(App* app);

    /// @brief
    ///
    /// @param state
    IState(const IState& state) = delete;

    /// @brief
    virtual
    ~IState(void);

    /// @brief
    ///
    /// @param state
    /// @return
    IState&
    operator=(const IState& state) = delete;

    /// @brief
    ///
    /// @param timestamp
    virtual void
    eventQuit(const std::size_t timestamp);

    /// @brief
    ///
    /// @param timestamp
    virtual void
    osQuit(const std::size_t timestamp);

    /// @brief
    ///
    /// @param timestamp
    /// @param window
    /// @param size
    virtual void
    windowResized(const std::size_t timestamp,
                  Window* window,
                  const Vector2D<std::size_t> size);

    /// @brief
    ///
    /// @param timestamp
    /// @param window
    virtual void
    windowMaximized(const std::size_t timestamp,
                    Window* window);

    /// @brief
    ///
    /// @param timestamp
    /// @param window
    virtual void
    windowRestored(const std::size_t timestamp,
                   Window* window);

protected:
    App* m_app{ nullptr };
}; /* end of : class IState */
