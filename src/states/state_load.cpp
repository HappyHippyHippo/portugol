#include <globals.hpp>
#include <app/config.hpp>
#include <app/i18n.hpp>
#include <states/state_editor.hpp>
#include <states/state_load.hpp>

#include <hypnos/hypnos.hpp>
using namespace hyp;

StateLoad::StateLoad(App* app)
    : IState{ app }
{
    try
    {
        _loadConfig();

        m_window = WindowFactory::create(ID_WINDOW,
                                         max(Config::getInt(CONFIG_ENTRY_WINDOW_MIN_WIDTH), Config::getInt(CONFIG_ENTRY_WINDOW_WIDTH)),
                                         max(Config::getInt(CONFIG_ENTRY_WINDOW_MIN_HEIGHT), Config::getInt(CONFIG_ENTRY_WINDOW_HEIGHT)),
                                         Window::CENTERED,
                                         Window::CENTERED,
                                           Window::Flag::RESIZABLE
                                         | (Config::getBool(CONFIG_ENTRY_WINDOW_IS_MAXIMIZED)
                                                ?  Window::Flag::MAXIMIZED
                                                : 0),
                                         Config::getString(CONFIG_ENTRY_WINDOW_TITLE));

        m_window->setMinSize({ Config::getInt(CONFIG_ENTRY_WINDOW_MIN_WIDTH),
                               Config::getInt(CONFIG_ENTRY_WINDOW_MIN_HEIGHT) });

        Surface surface{ Config::getString(CONFIG_ENTRY_WINDOW_ICON_TITLE) };
        m_window->setIcon(&surface);
    }
    catch (exception::SDLFont e)
    {
        Log::critical(0, "[%s] Erro na abertura do ficheiro de fonte de texto : %s\n", timestring().c_str(), e.what());
        throw e;
    }
    catch (exception::SDLImage e)
    {
        Log::warning(0, "[%s] Erro na abertura do icon da aplicação : %s\n", timestring().c_str(), e.what());
    }
    catch (exception::SDL e)
    {
        Log::critical(0, "[%s] Erro na abertura da janela : %s\n", timestring().c_str(), e.what());
        throw e;
    }
} /* end of : StateLoad::StateLoad(App* app) */

StateLoad::~StateLoad(void)
{
    Config::store(CONFIG_CURRENT_FILE);
} /* end of : StateLoad::~StateLoad(void) */

void
StateLoad::logicStep(const std::size_t timestamp,
                     const std::size_t delta)
{
    if (!m_logic_ready)
    {
        FontFactory::createTTF(ID_FONT_GUI,
                               Config::getString(CONFIG_ENTRY_FONT_GUI_FILE),
                               Config::getInt(CONFIG_ENTRY_FONT_GUI_SIZE),
                               Config::getInt(CONFIG_ENTRY_FONT_GUI_INDEX));
        FontFactory::createTTF(ID_FONT_CODE,
                               Config::getString(CONFIG_ENTRY_FONT_CODE_FILE),
                               Config::getInt(CONFIG_ENTRY_FONT_CODE_SIZE),
                               Config::getInt(CONFIG_ENTRY_FONT_CODE_INDEX));

        m_logic_ready = true;
    }

    if (m_logic_ready && m_video_ready)
        StateStack::push(new StateEditor(m_app));
} /* end of : void
              StateLoad::logicStep(const std::size_t timestamp,
                                   const std::size_t delta) */

void
StateLoad::renderStep(const std::size_t timestamp,
                      const std::size_t delta)
{
    if (!m_renderer)
    {
        m_renderer = RendererFactory::create(ID_RENDERER, m_window, -1, 0);
        _loadGUI();

        m_video_ready = true;
    }

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
              StateLoad::renderStep(const std::size_t timestamp,
                                    const std::size_t delta) */
void
StateLoad::_loadConfig(void)
{
    Config::load(CONFIG_DEFAULT_FILE);

    auto logger = Log::addStream(ID_LOG,
                                 StreamFactory::createFile(ID_LOG,
                                                           Config::getString(CONFIG_ENTRY_LOG_FILE),
                                                           Config::getString(CONFIG_ENTRY_LOG_MODE)));
    logger->setPriorityAll(Log::Priority::WARNING);

    Config::load(Config::getString(CONFIG_ENTRY_THEME_FILE));
    I18n::load(Config::getString(CONFIG_ENTRY_I18N_FILE));

    Config::load(CONFIG_CURRENT_FILE);
} /* end of : void
              StateLoad::_loadConfig(void) */

void
StateLoad::_loadGUI(void)
{

} /* end of: void
             StateLoad::_loadGUI(void) */
