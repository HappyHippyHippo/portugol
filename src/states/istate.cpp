#include <globals.hpp>
#include <app/config.hpp>
#include <states/istate.hpp>

IState::IState(App* app)
    : m_app{ app }
{

} /* end of : IState::IState(App* app) */

IState::~IState(void)
{

} /* end of : IState::~IState(void) */

void
IState::eventQuit(const std::size_t timestamp)
{
    m_app->stop();
} /* end of : void
              IState::eventQuit(const std::size_t timestamp) */

void
IState::osQuit(const std::size_t timestamp)
{
    m_app->stop();
} /* end of : void
              IState::osQuit(const std::size_t timestamp) */

void
IState::windowResized(const std::size_t timestamp,
                      Window* window,
                      const Vector2D<std::size_t> size)
{
    if (!window->isMaximized())
    {
        Config::set(CONFIG_ENTRY_WINDOW_WIDTH,  (int) size[0]);
        Config::set(CONFIG_ENTRY_WINDOW_HEIGHT, (int)size[1]);
    }
} /* end of : void
              IState::windowResized(const std::size_t timestamp,
                                    Window* window,
                                    const Vector2D<std::size_t> size) */

void
IState::windowMaximized(const std::size_t timestamp,
                        Window* window)
{
    Config::set(CONFIG_ENTRY_WINDOW_IS_MAXIMIZED, true);
} /* end of : void
              IState::windowMaximized(const std::size_t timestamp,
                                      Window* window) */

void
IState::windowRestored(const std::size_t timestamp,
                       Window* window)
{
    Config::set(CONFIG_ENTRY_WINDOW_IS_MAXIMIZED, false);
} /* end of : void
              IState::windowRestored(const std::size_t timestamp,
                                     Window* window) */
