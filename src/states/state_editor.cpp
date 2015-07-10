#include <globals.hpp>
#include <app/config.hpp>
#include <states/state_editor.hpp>

#include <iostream>

StateEditor::StateEditor(App* app)
    : IState{ app }
    , m_window{ WindowFactory::get(ID_WINDOW) }
    , m_renderer{ RendererFactory::get(ID_RENDERER) }
{

} /* end of : StateEditor::StateEditor(App* app) */

StateEditor::~StateEditor(void)
{

} /* end of : StateEditor::~StateEditor(void) */

void
StateEditor::logicStep(const std::size_t timestamp,
                       const std::size_t delta)
{

} /* end of : void
              StateEditor::logicStep(const std::size_t timestamp,
                                     const std::size_t delta) */

void
StateEditor::renderStep(const std::size_t timestamp,
                        const std::size_t delta)
{
    if (   !m_window->isResizing()
        && m_window->isInputFocussed())
    {
        m_renderer->paintClear({ (uint8_t) Config::getInt(CONFIG_ENTRY_WINDOW_BACKGROUND_COLOR_RED),
                                 (uint8_t) Config::getInt(CONFIG_ENTRY_WINDOW_BACKGROUND_COLOR_GREEN),
                                 (uint8_t) Config::getInt(CONFIG_ENTRY_WINDOW_BACKGROUND_COLOR_BLUE),
                                 (uint8_t) Config::getInt(CONFIG_ENTRY_WINDOW_BACKGROUND_COLOR_ALPHA) });
        m_renderer->present();
    }
} /* end of : void
              StateEditor::renderStep(const std::size_t timestamp,
                                      const std::size_t delta) */

void
StateEditor::windowResized(const std::size_t timestamp,
                           Window* window,
                           const Vector2D<std::size_t> size)
{
    IState::windowResized(timestamp, window, size);
} /* end of : void
              StateEditor::windowResized(const std::size_t timestamp,
                                         Window* window,
                                         const Vector2D<std::size_t> size) */
