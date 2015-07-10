#pragma once

#include <states/istate.hpp>

/// @brief
class StateLoad : public IState
{
public:
    /// @brief
    ///
    /// @param app
    StateLoad(App* app);

    /// @brief
    ///
    /// @param state
    StateLoad(const StateLoad& state) = delete;

    /// @brief
    virtual
    ~StateLoad(void);

    /// @brief
    ///
    /// @param state
    /// @return
    StateLoad&
    operator=(const StateLoad& state) = delete;

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

protected:
    /// @brief
    void
    _loadConfig(void);

    /// @brief
    void
    _loadGUI(void);

protected:
    /// @brief
    Window* m_window{ false };
    
    /// @brief
    Renderer* m_renderer{ false };

    /// @brief
    bool m_logic_ready{ false };

    /// @brief
    bool m_video_ready{ false };
}; /* end of : class StateLoad */
