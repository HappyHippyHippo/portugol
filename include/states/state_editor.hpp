#pragma once

#include <states/istate.hpp>

/// @brief
class StateEditor : public IState
{
public:
    /// @brief
    StateEditor(App* app);

    /// @brief
    ///
    /// @param state
    StateEditor(const StateEditor& state) = delete;

    /// @brief
    virtual
    ~StateEditor(void);

    /// @brief
    ///
    /// @param state
    /// @return
    StateEditor&
    operator=(const StateEditor& state) = delete;

    /// @brief
    ///
    /// @param timestamp
    /// @param delta
    void
    logicStep(const std::size_t timestamp,
              const std::size_t delta);

    /// @brief
    ///
    /// @param timestamp
    /// @param delta
    void
    renderStep(const std::size_t timestamp,
               const std::size_t delta);

    /// @brief
    ///
    /// @param timestamp
    /// @param window
    /// @param size
    void
    windowResized(const std::size_t timestamp,
                  Window* window,
                  const Vector2D<std::size_t> size);

protected:
    /// @brief
    Window* m_window{ false };

    /// @brief
    Renderer* m_renderer{ false };
}; /* end of : class StateEditor */
